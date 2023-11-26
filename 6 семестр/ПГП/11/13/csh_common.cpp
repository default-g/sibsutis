#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>

const int N = 256;

GLuint genInitProg();
GLuint genTransformProg();

int initBuffers(GLuint *&bufferID) {
  glGenBuffers(2, bufferID);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferID[0]);
  glBufferData(GL_SHADER_STORAGE_BUFFER, N * sizeof(float), 0, GL_DYNAMIC_DRAW);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, bufferID[1]);
  glBufferData(GL_SHADER_STORAGE_BUFFER, N * sizeof(float), 0, GL_DYNAMIC_DRAW);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, bufferID[0]);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bufferID[1]);
  GLuint csInitID = genInitProg();
  glUseProgram(csInitID);
  glDispatchCompute(N / 128, 1, 1);
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);
  glDeleteProgram(csInitID);
  return 0;
}

int transformBuffers(GLuint *bufferID) {
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, bufferID[0]);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, bufferID[1]);
  GLuint csTransformID = genTransformProg();
  glUseProgram(csTransformID);
  glDispatchCompute(N / 128, 1, 1);
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);
  glDeleteProgram(csTransformID);
  return 0;
}

GLuint genInitProg() {
  GLuint progHandle = glCreateProgram();
  GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
  const char *cpSrc[] = {
      "#version 430\n",
      "layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in; \
      layout(std430, binding = 0) buffer BufferA{float A[];};\
      layout(std430, binding = 1) buffer BufferB{float B[];};\
      void main() {\
        uint index = gl_GlobalInvocationID.x;\
        A[index]=0.1*float(index);\
        B[index]=0.2*float(index);\
      }"};
  glShaderSource(cs, 2, cpSrc, NULL);
  glCompileShader(cs);
  glAttachShader(progHandle, cs);
  glLinkProgram(progHandle);
  return progHandle;
}

GLuint genTransformProg() {
  GLuint progHandle = glCreateProgram();
  GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
  const char *cpSrc[] = {
      "#version 430\n",
      "layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in; \
      layout(std430, binding = 0) buffer BufferA{float A[];};\
      layout(std430, binding = 1) buffer BufferB{float B[];};\
      void main() {\
        uint index = gl_GlobalInvocationID.x;\
        A[index]=A[index]+B[index];\
      }"};
  glShaderSource(cs, 2, cpSrc, NULL);
  glCompileShader(cs);
  glAttachShader(progHandle, cs);
  glLinkProgram(progHandle);
  return progHandle;
}