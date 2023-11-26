#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <string>

GLuint genRenderProg() {
  GLuint progHandle = glCreateProgram();
  GLuint vp = glCreateShader(GL_VERTEX_SHADER);
  GLuint fp = glCreateShader(GL_FRAGMENT_SHADER);

  const char *vpSrc[] = {"#version 430\n",
                         "layout (location = 0) in vec2 in_position;\
layout (location = 1) in vec2 in_tex_coord;\
out vec2 tex_coord;\
void main(void){\
gl_Position = vec4(in_position, 0.5, 1.0);\
tex_coord = in_tex_coord;\
}"};

  const char *fpSrc[] = {"#version 430\n", "in vec2 tex_coord;\
layout (location = 0) out vec4 color;\
uniform sampler2D tex;\
void main(void){\
color = texture(tex, tex_coord);\
}"};

  glShaderSource(vp, 2, vpSrc, NULL);
  glShaderSource(fp, 2, fpSrc, NULL);
  glCompileShader(vp);
  int rvalue;
  glGetShaderiv(vp, GL_COMPILE_STATUS, &rvalue);
  if (!rvalue) {
    fprintf(stderr, "Error in compiling vp\n");
    exit(30);
  }
  glAttachShader(progHandle, vp);
  glCompileShader(fp);
  glGetShaderiv(fp, GL_COMPILE_STATUS, &rvalue);
  if (!rvalue) {
    fprintf(stderr, "Error in compiling fp\n");
    exit(31);
  }
  glAttachShader(progHandle, fp);
  glLinkProgram(progHandle);
  glGetProgramiv(progHandle, GL_LINK_STATUS, &rvalue);
  if (!rvalue) {
    fprintf(stderr, "Error in linking sp\n");
    exit(32);
  }
  return progHandle;
}