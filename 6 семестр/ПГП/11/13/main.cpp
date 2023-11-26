#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <cstring> // добавлен заголовочный файл для memcpy и calloc
#include "csh_common.cpp"
#include "csh_template.cpp"

const unsigned int window_width = 512;
const unsigned int window_height = 512;
GLuint *bufferID; // объявлен массив идентификаторов буферов

void initGL() {
  glfwInit(); // добавлен вызов инициализации GLFW
  GLFWwindow *window;
  glfwWindowHint(GLFW_VISIBLE, 0);
  window = glfwCreateWindow(window_width, window_height, "Template window",
                            NULL, NULL);
  glfwMakeContextCurrent(window);
  glewInit();
}

void outputBuffers(GLuint *bufferID) {
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferID[1]);
  float *data = (float *)glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY);
  float *hdata = (float *)calloc(N, sizeof(float));
  memcpy(&hdata[0], data, sizeof(float) * N);
  glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++)
      fprintf(stdout, "%g\t", hdata[j + i * 10]);
    printf("\n");
  }
  free(hdata); // освобождение выделенной памяти
}

int main() {
  initGL();
  initBuffers(bufferID); // передача размера буферов в функцию
  transformBuffers(bufferID); // передача размера буферов в функцию
  outputBuffers(bufferID);
  glDeleteBuffers(2, bufferID);
  glfwTerminate();
  return 0;
}