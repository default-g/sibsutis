#include "tex_sh.cpp"
#include "text_gen.cpp"

const unsigned int window_width = 512;
const unsigned int window_height = 512;

void initGL() {
  glfwInit(); // добавлен вызов инициализации GLFW
  GLFWwindow *window;
  glfwWindowHint(GLFW_VISIBLE, 0);
  window = glfwCreateWindow(window_width, window_height, "Template window",
                            NULL, NULL);
  glfwMakeContextCurrent(window);
  glewInit();
}

void initTexture();
GLuint genRenderProg();
void display();
int main() {
  initGL();
  initTexture();
  glfwTerminate();
  return 0;
}

  void display() {
    GLuint progHandle;
    progHandle = genRenderProg();
    glUseProgram(progHandle);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,
                          (GLvoid *)(8 * sizeof(float)));
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  }