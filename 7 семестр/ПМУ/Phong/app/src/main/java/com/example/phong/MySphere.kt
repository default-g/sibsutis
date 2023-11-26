package com.example.phong

import android.hardware.lights.Light
import android.opengl.GLES20
import com.example.phong.ShaderHelper
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer

class MySphere(LATITUDES: Int, LONGITUDES: Int) {
    private val VertexBuffer: FloatBuffer
    private val ColorBuffer: FloatBuffer
    private val NormalsBuffer: FloatBuffer
    private val MyApplication: Int
    private lateinit var Vertices: FloatArray
    private lateinit var Normals: FloatArray
    private lateinit var Colors: FloatArray
    private var VERTEX_COUNT = 0

    var LightDirection = floatArrayOf(5f, 10f, 35.0f)

    private fun CreateSphere(LATITUDES: Int, LONGITUDES: Int) {
        Vertices = FloatArray(LATITUDES * LONGITUDES * 6 * 3)
        Normals = FloatArray(LATITUDES * LONGITUDES * 6 * 3)
        Colors = FloatArray(LATITUDES * LONGITUDES * 6 * 3)
        var TriangleIndex = 0
        VERTEX_COUNT = Vertices.size / COORDS_COUNT_PER_VERTEX
        for (i in 0 until LATITUDES) {
            val LatitudeFirst = Math.PI * (-0.5 + i.toDouble() / LATITUDES)
            val Z_SizeFirst = Math.sin(LatitudeFirst)
            val Zr_SizeFirst = Math.cos(LatitudeFirst)
            val LatitudeSecond = Math.PI * (-0.5 + (i + 1).toDouble() / LATITUDES)
            val Z_SizeSecond = Math.sin(LatitudeSecond)
            val Zr_SizeSecond = Math.cos(LatitudeSecond)
            for (j in 0 until LONGITUDES) {
                var Longitude = 2 * Math.PI * (j - 1).toDouble() / LONGITUDES
                val X_SizeFirst = Math.cos(Longitude)
                val Y_SizeFirst = Math.sin(Longitude)
                Longitude = 2 * Math.PI * j.toDouble() / LONGITUDES
                val X_SizeSecond = Math.cos(Longitude)
                val Y_SizeSecond = Math.sin(Longitude)
                Vertices[TriangleIndex * 9] = (X_SizeFirst * Zr_SizeFirst).toFloat()
                Vertices[TriangleIndex * 9 + 1] = (Y_SizeFirst * Zr_SizeFirst).toFloat()
                Vertices[TriangleIndex * 9 + 2] = Z_SizeFirst.toFloat()
                Vertices[TriangleIndex * 9 + 3] = (X_SizeFirst * Zr_SizeSecond).toFloat()
                Vertices[TriangleIndex * 9 + 4] = (Y_SizeFirst * Zr_SizeSecond).toFloat()
                Vertices[TriangleIndex * 9 + 5] = Z_SizeSecond.toFloat()
                Vertices[TriangleIndex * 9 + 6] = (X_SizeSecond * Zr_SizeFirst).toFloat()
                Vertices[TriangleIndex * 9 + 7] = (Y_SizeSecond * Zr_SizeFirst).toFloat()
                Vertices[TriangleIndex * 9 + 8] = Z_SizeFirst.toFloat()
                TriangleIndex++
                Vertices[TriangleIndex * 9] = (X_SizeSecond * Zr_SizeFirst).toFloat()
                Vertices[TriangleIndex * 9 + 1] = (Y_SizeSecond * Zr_SizeFirst).toFloat()
                Vertices[TriangleIndex * 9 + 2] = Z_SizeFirst.toFloat()
                Vertices[TriangleIndex * 9 + 3] = (X_SizeFirst * Zr_SizeSecond).toFloat()
                Vertices[TriangleIndex * 9 + 4] = (Y_SizeFirst * Zr_SizeSecond).toFloat()
                Vertices[TriangleIndex * 9 + 5] = Z_SizeSecond.toFloat()
                Vertices[TriangleIndex * 9 + 6] = (X_SizeSecond * Zr_SizeSecond).toFloat()
                Vertices[TriangleIndex * 9 + 7] = (Y_SizeSecond * Zr_SizeSecond).toFloat()
                Vertices[TriangleIndex * 9 + 8] = Z_SizeSecond.toFloat()
                for (counter in -9..8) {
                    Normals[TriangleIndex * 9 + counter] = Vertices[TriangleIndex * 9 + counter]
                    if ((TriangleIndex * 9 + counter) % 3 == 1) {
                        Colors[TriangleIndex * 9 + counter] = 1f
                    } else {
                        Colors[TriangleIndex * 9 + counter] = 0f
                    }
                }
                TriangleIndex++
            }
        }
    }

    init {
        CreateSphere(LATITUDES, LONGITUDES)
        val bb = ByteBuffer.allocateDirect(Vertices.size * 4)
        bb.order(ByteOrder.nativeOrder())
        VertexBuffer = bb.asFloatBuffer()
        VertexBuffer.put(Vertices)
        VertexBuffer.position(0)
        val bb2 = ByteBuffer.allocateDirect(Colors.size * 4)

        bb2.order(ByteOrder.nativeOrder())

        ColorBuffer = bb2.asFloatBuffer()
        ColorBuffer.put(Colors)
        ColorBuffer.position(0)
        val bb3 = ByteBuffer.allocateDirect(Normals.size * 4)
        bb3.order(ByteOrder.nativeOrder())
        NormalsBuffer = bb3.asFloatBuffer()
        NormalsBuffer.put(Normals)
        NormalsBuffer.position(0)
        val drawOrder = shortArrayOf(0, 1, 2, 0, 2, 3)
        val dlb = ByteBuffer.allocateDirect(drawOrder.size * 2)
        dlb.order(ByteOrder.nativeOrder())
        val drawListBuffer = dlb.asShortBuffer()
        drawListBuffer.put(drawOrder)
        drawListBuffer.position(0)
        MyApplication = ShaderHelper.createShaders()
    }

    var lightMoveDirection = 1f
    fun draw(mvpMatrix: FloatArray?, normalMat: FloatArray?, mvMat: FloatArray?) {
        if (LightDirection[0] > 50f || LightDirection[0] < -50f) {
            lightMoveDirection *= -1
        }
        LightDirection[0] += lightMoveDirection
        GLES20.glUseProgram(MyApplication)
        val mPositionHandle = GLES20.glGetAttribLocation(MyApplication, "vPosition")
        GLES20.glEnableVertexAttribArray(mPositionHandle)
        val vertexStride = COORDS_COUNT_PER_VERTEX * 4
        GLES20.glVertexAttribPointer(
            mPositionHandle, COORDS_COUNT_PER_VERTEX, GLES20.GL_FLOAT,
            false, vertexStride, VertexBuffer
        )
        val light = GLES20.glGetUniformLocation(MyApplication, "lightDir")
        GLES20.glUniform3fv(light, 1, LightDirection, 0)
        val mColorHandle = GLES20.glGetAttribLocation(MyApplication, "vColor")
        GLES20.glEnableVertexAttribArray(mColorHandle)
        GLES20.glVertexAttribPointer(
            mColorHandle, COORDS_COUNT_PER_VERTEX, GLES20.GL_FLOAT,
            false, vertexStride, ColorBuffer
        )
        val mNormalHandle = GLES20.glGetAttribLocation(MyApplication, "vNormal")
        GLES20.glEnableVertexAttribArray(mNormalHandle)
        GLES20.glVertexAttribPointer(
            mNormalHandle, COORDS_COUNT_PER_VERTEX, GLES20.GL_FLOAT,
            false, vertexStride, NormalsBuffer
        )
        val mMVPMatrixHandle = GLES20.glGetUniformLocation(MyApplication, "uMVPMatrix")
        val mNormalMatHandle = GLES20.glGetUniformLocation(MyApplication, "uNormalMat")
        val MVMatHandle = GLES20.glGetUniformLocation(MyApplication, "uMVMatrix")
        GLES20.glUniformMatrix4fv(mMVPMatrixHandle, 1, false, mvpMatrix, 0)
        GLES20.glUniformMatrix4fv(mNormalMatHandle, 1, false, normalMat, 0)
        GLES20.glUniformMatrix4fv(MVMatHandle, 1, false, mvMat, 0)
        GLES20.glDrawArrays(GLES20.GL_TRIANGLES, 0, VERTEX_COUNT)
        GLES20.glDisableVertexAttribArray(mPositionHandle)
        GLES20.glDisableVertexAttribArray(mColorHandle)
        GLES20.glDisableVertexAttribArray(mNormalHandle)
    }

    companion object {
        const val COORDS_COUNT_PER_VERTEX = 3
    }
}