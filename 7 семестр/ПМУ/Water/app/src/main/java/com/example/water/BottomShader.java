package com.example.water;

import android.opengl.GLES20;

import java.nio.FloatBuffer;

public class BottomShader {

    private int program_handle;

    public BottomShader(String vertex_shader, String fragment_shader) {
        create_program(vertex_shader, fragment_shader);
    }

    private void create_program(String vertex_shader, String fragment_shader) {
        int vertex_shader_handle = GLES20.glCreateShader(GLES20.GL_VERTEX_SHADER);
        GLES20.glShaderSource(vertex_shader_handle, vertex_shader);
        GLES20.glCompileShader(vertex_shader_handle);
        int fragment_shader_handle = GLES20.glCreateShader(GLES20.GL_FRAGMENT_SHADER);
        GLES20.glShaderSource(fragment_shader_handle, fragment_shader);
        GLES20.glCompileShader(fragment_shader_handle);
        program_handle = GLES20.glCreateProgram();
        GLES20.glAttachShader(program_handle, vertex_shader_handle);
        GLES20.glAttachShader(program_handle, fragment_shader_handle);
        GLES20.glLinkProgram(program_handle);
    }

    public void use_program() {
        GLES20.glUseProgram(program_handle);
    }

    public void link_vertex_buffer(FloatBuffer vertex_buffer) {
        GLES20.glUseProgram(program_handle);
        int a_vertex_handle = GLES20.glGetAttribLocation(program_handle, "a_vertex");
        GLES20.glEnableVertexAttribArray(a_vertex_handle);
        GLES20.glVertexAttribPointer(a_vertex_handle, 3, GLES20.GL_FLOAT, false, 0, vertex_buffer);
    }

    public void link_texture(int[] texture) {
        GLES20.glUseProgram(program_handle);
        int u_texture_Handle = GLES20.glGetUniformLocation(program_handle, "u_texture0");
        GLES20.glActiveTexture(GLES20.GL_TEXTURE1);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, texture[0]);
        GLES20.glUniform1i(u_texture_Handle, 0);
    }
}