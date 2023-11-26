package com.example.phong

import android.opengl.GLES20

class ShaderHelper {
    companion object {
        fun initializeProgram(vertexShader: Int, fragmentShader: Int): Int {
            val programId = GLES20.glCreateProgram()
            GLES20.glAttachShader(programId, vertexShader)
            GLES20.glAttachShader(programId, fragmentShader)
            GLES20.glLinkProgram(programId)
            val linkStatus = IntArray(1)
            GLES20.glGetProgramiv(programId, GLES20.GL_LINK_STATUS, linkStatus, 0)
            if (linkStatus[0] == 0) {
                GLES20.glDeleteProgram(programId)
                return -1
            }
            return programId
        }

        fun compileShader(shaderType: Int, shaderCode: String?): Int {
            val shaderId = GLES20.glCreateShader(shaderType)
            if (shaderId == 0) {
                return -1
            }
            GLES20.glShaderSource(shaderId, shaderCode)
            GLES20.glCompileShader(shaderId)
            val compileStatus = IntArray(1)
            GLES20.glGetShaderiv(shaderId, GLES20.GL_COMPILE_STATUS, compileStatus, 0)
            if (compileStatus[0] == 0) {
                GLES20.glDeleteShader(shaderId)
                return -1
            }
            return shaderId
        }

        fun createShaders(): Int {
            val vertexShaderCode = """
                uniform mat4 uMVPMatrix, uMVMatrix, uNormalMat;
                attribute vec4 vPosition;
                attribute vec4 vColor;
                attribute vec3 vNormal;
                varying vec4 varyingColor;
                varying vec3 varyingNormal;
                varying vec3 varyingPos;
                void main() {
                    varyingColor = vColor;
                    varyingNormal = vec3(uNormalMat * vec4(vNormal, 0.0));
                    varyingPos = vec3(uMVMatrix * vPosition);
                    gl_Position = uMVPMatrix * vPosition;
                }
            """.trimIndent()

            val fragmentShaderCode = """
                precision mediump float;
                varying vec4 varyingColor;
                varying vec3 varyingNormal;
                varying vec3 varyingPos;
                uniform vec3 lightDir;
                void main() {
                    float Ns = 15.0;
                    float kd = 0.7, ks = 1.0;
                    vec4 light = vec4(1.0, 1.0, 1.0, 1.0);
                    vec4 lightS = vec4(1.0, 1.0, 0.2, 1.0);
                    vec3 Nn = normalize(varyingNormal);
                    vec3 Ln = normalize(lightDir);
                    vec4 diffuse = kd * light * max(dot(Nn, Ln), 0.0);
                    vec3 Ref = reflect(Nn, Ln);
                    float spec = pow(max(dot(Ref, normalize(varyingPos)), 0.0), Ns);
                    vec4 specular = lightS * ks * spec;
                    gl_FragColor = varyingColor * diffuse + specular;
                }
            """.trimIndent()

            val vertexShader = compileShader(GLES20.GL_VERTEX_SHADER, vertexShaderCode)
            val fragmentShader = compileShader(GLES20.GL_FRAGMENT_SHADER, fragmentShaderCode)

            return initializeProgram(vertexShader, fragmentShader)
        }
    }
}
