#include <iostream>
#include <vector>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

using namespace std;

const char* matrixMulShaderSource = R"(
#version 430
layout (local_size_x = 16, local_size_y = 16) in;
layout (std430, binding = 0) buffer A {
    float a[];
};
layout (std430, binding = 1) buffer B {
    float b[];
};
layout (std430, binding = 2) buffer C {
    float c[];
};
uniform int size;
void main() {
    ivec2 gid = ivec2(gl_GlobalInvocationID.xy);
    if (gid.x < size && gid.y < size) {
        float sum = 0.0;
        for (int k = 0; k < size; k++) {
            sum += a[gid.y * size + k] * b[k * size + gid.x];
        }
        c[gid.y * size + gid.x] = sum;
    }
}
)";


const char* matrixTransposeShaderSource = R"(
#version 430
layout (local_size_x = 16, local_size_y = 16) in;
layout (std430, binding = 0) buffer A {
    float a[];
};
layout (std430, binding = 1) buffer B {
    float b[]; 
};
uniform int size;
void main() {
    ivec2 gid = ivec2(gl_GlobalInvocationID.xy);
    if (gid.x < size && gid.y < size) {
        b[gid.y * size + gid.x] = a[gid.x * size + gid.y];
    }
}
)";


const char* matrixScalarMulShaderSource = R"(
#version 430 
layout (local_size_x = 16, local_size_y = 16) in;
layout (std430, binding = 0) buffer A {
    float a[];
};
layout (std430, binding = 1) buffer B {
    float b[]; 
};
uniform float scalar;
uniform int size;
void main() {
    ivec2 gid = ivec2(gl_GlobalInvocationID.xy);
    if (gid.x < size && gid.y < size) {
        b[gid.y * size + gid.x] = a[gid.y * size + gid.x] * scalar;
    }
}
)";

void checkShaderError(GLuint shader) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
    }
}

void checkProgramError(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
    }
}

int main(int argc, char** argv) {

    if (argc < 2) {
        return -1;
    }

    int matrixSize = atoi(argv[1]);

    // Инициализация GLFW и GLEW
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(1, 1, "", nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW window creation failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW initialization failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Создание шейдерной программы
    GLuint shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shader, 1, &matrixMulShaderSource, nullptr);
    glCompileShader(shader);
    checkShaderError(shader);
    GLuint program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);
    checkProgramError(program);
    glUseProgram(program);
    glDeleteShader(shader);

    // Размер матрицы и количество экспериментов

    // Инициализация матриц A и B с случайными значениями
    std::vector<float> a(matrixSize * matrixSize), b(matrixSize * matrixSize);
    for (int i = 0; i < matrixSize * matrixSize; i++) {
        a[i] = static_cast<float>(rand()) / RAND_MAX;
        b[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    // Создание и заполнение буферов
    GLuint buffers[3];
    glGenBuffers(3, buffers);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffers[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, matrixSize * matrixSize * sizeof(float), a.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, buffers[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, matrixSize * matrixSize * sizeof(float), b.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, buffers[2]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, matrixSize * matrixSize * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    // Запуск вычислительного шейдера и измерение времени выполнения
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "size"), matrixSize);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    glDispatchCompute((matrixSize + 15) / 16, (matrixSize + 15) / 16, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glFinish();
    
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_matrix_multiplication = end - start;

    glDeleteProgram(program);
    glDeleteBuffers(3, buffers);

    shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shader, 1, &matrixTransposeShaderSource, nullptr);
    glCompileShader(shader);
    checkShaderError(shader);
    program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);
    checkProgramError(program);
    glUseProgram(program);
    glDeleteShader(shader);

    glGenBuffers(2, buffers);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffers[0]); 
    glBufferData(GL_SHADER_STORAGE_BUFFER, matrixSize * matrixSize * sizeof(float), a.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, buffers[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, matrixSize * matrixSize * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    
    
    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "size"), matrixSize);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    start = std::chrono::high_resolution_clock::now();
    glDispatchCompute((matrixSize + 15) / 16, (matrixSize + 15) / 16, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glFinish();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_matrix_tanspose = end - start;

    glDeleteProgram(program);
    glDeleteBuffers(3, buffers);

    shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(shader, 1, &matrixScalarMulShaderSource, nullptr);
    glCompileShader(shader);
    checkShaderError(shader);
    program = glCreateProgram();
    glAttachShader(program, shader);
    glLinkProgram(program);
    checkProgramError(program);
    glUseProgram(program);
    glDeleteShader(shader);

    glGenBuffers(2, buffers);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffers[0]); 
    glBufferData(GL_SHADER_STORAGE_BUFFER, matrixSize * matrixSize * sizeof(float), a.data(), GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, buffers[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, matrixSize * matrixSize * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    
    const float scalar = 2.0f;

    glUseProgram(program);
    glUniform1f(glGetUniformLocation(program, "scalar"), scalar);
    glUniform1i(glGetUniformLocation(program, "size"), matrixSize);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


    start = std::chrono::high_resolution_clock::now();
    glDispatchCompute((matrixSize + 15) / 16, (matrixSize + 15) / 16, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glFinish();
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_matrix_scalar = end - start;
    ofstream file;
    file.open("results.csv", ios::app);
    if (file.tellp() == streampos(0))
    {
            file << "Matrix size (n^2); MT (OPENGL); MM (OPENGL); SM (OPENGL);" << "\n";
    }
    file 
        << matrixSize << ";" 
        << elapsed_matrix_tanspose.count() << ";" 
        << elapsed_matrix_multiplication.count() << ";" 
        << elapsed_matrix_scalar.count() << ";"
        << "\n";
    file.close();
    // Освобождение ресурсов и завершение работы
    glDeleteProgram(program);
    glDeleteBuffers(3, buffers);
    glfwTerminate();

    return 0;
}