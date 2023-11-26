#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>

GLuint genComputeProg() {
  GLuint progHandle = glCreateProgram();
  GLuint cs = glCreateShader(GL_COMPUTE_SHADER);
  const char *cpSrc[] = {
      "#version 430\n",
      "layout (local_size_x = 128, local_size_y = 1, local_size_z = 1) in; \
      layout(std430, binding = 0) buffer PositionBuffer{float Pos[];};\
      layout(std430, binding = 1) buffer VelocityBuffer{float Vel[];};\
      float lmap(in uint i){\
        uint count;\
        float x=0.78;\
        for(count=0;count<i;count++)\
          x=3.99*x*(1-x);\
        return x;\
      }\
      void main() {\
        uint index = gl_GlobalInvocationID.x;\
        Pos[index*6]=-0.5+1.0*lmap(index);\
        Pos[index*6+1]=-0.5+1.0*lmap(index*10);\
        Pos[index*6+2]=0.0;\
        Pos[index*6+3]=1.0;\
        Pos[index*6+4]=1.0;\
        Pos[index*6+5]=0.0;\
        Vel[3*index]=-0.5+1.0*lmap(index);\
        Vel[3*index+1]=-0.5+1.0*lmap(index*10);\
        Vel[3*index+2]=0.0;\
      }"};
  glShaderSource(cs, 2, cpSrc, NULL);
  glCompileShader(cs);
  glAttachShader(progHandle, cs);
  glLinkProgram(progHandle);
  return progHandle;
}

void csDataInit(GLuint *inBuf, int N) {
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, inBuf[0]);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, inBuf[1]);
  GLuint computeShaderID = genComputeProg();
  glUseProgram(computeShaderID);
  glDispatchCompute(N / 128, 1, 1);
  glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
  glDeleteProgram(computeShaderID);
}