#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
int L = 4, M = 2;

GLuint genTexBuffer() {
  GLuint tex_buf;
  glGenBuffers(1, &tex_buf);
  static const GLfloat tex_color_data[] = {
      1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f,
      0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0f, 0.5f, 0.5f, 0.0f, 1.0f,
  };
  glBufferData(GL_PIXEL_UNPACK_BUFFER, sizeof(tex_color_data), tex_color_data,
               GL_STATIC_DRAW);
  return tex_buf;
}

GLuint genMapBuffer() {
  GLuint map_buf;
  glGenBuffers(1, &map_buf);
  static const GLfloat map_data[] = {
      0.75f, -0.75f, -0.75f, -0.75f, -0.75f, 0.75f, 0.75f, 0.75f,
      0.0f,  1.0f,   1.0f,   0.0f,   0.0f,   0.0f,  1.0f,  1.0f};
  glBindBuffer(GL_ARRAY_BUFFER, map_buf);
  glBufferData(GL_ARRAY_BUFFER, sizeof(map_data), map_data, GL_STATIC_DRAW);
  return map_buf;
}

GLuint genTexture() {
  GLuint texHandle;
  glGenTextures(1, &texHandle);
  glBindTexture(GL_TEXTURE_2D, texHandle);
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, L, M);
  glTexSubImage2D(GL_TEXTURE_2D, // тип текстуры
                  0, // уровень детализации (mipmap)
                  0,
                  0, // смещения текселя в x и y направлениях в массиве текстуры
                  L, M, // ширина и высота текстурного subimage
                  GL_RGBA, // формат пикселя, GL_RGB, GL_RGBA и т.д.
                  GL_FLOAT, // тип данных пикселя
                  NULL);    // указатель на image в памяти
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_NEAREST); // GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_NEAREST); // GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  return texHandle;
}

void initTexture() {
  genMapBuffer();
  genTexBuffer();
  genTexture();
}