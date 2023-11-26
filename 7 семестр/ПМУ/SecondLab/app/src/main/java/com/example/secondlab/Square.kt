package com.example.secondlab

import android.opengl.GLSurfaceView
import android.opengl.GLU
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10


class Square: GLSurfaceView.Renderer {
    private var rotation: Float = 0f

    private var vertexBuffer: FloatBuffer
    private var colorBuffer: FloatBuffer
    private var indexBuffer: ByteBuffer


    private val vertices: FloatArray = floatArrayOf(
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    )

    private val colors: FloatArray = floatArrayOf(
        0.5f, 0.0f, 0.5f, 1.0f,  // Purple (R, G, B, A)
        0.5f, 0.0f, 0.5f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f,
        0.5f, 0.0f, 0.5f, 1.0f,
    )

    private val indexes: ByteArray = byteArrayOf(
        0, 1, 2, 1, 3, 2
    )

    init {
        var byteBuf = ByteBuffer.allocateDirect(vertices.size * 4)
        byteBuf.order(ByteOrder.nativeOrder())
        vertexBuffer = byteBuf.asFloatBuffer()
        vertexBuffer.put(vertices)
        vertexBuffer.position(0)

        byteBuf = ByteBuffer.allocateDirect(colors.size * 4)
        byteBuf.order(ByteOrder.nativeOrder())
        colorBuffer = byteBuf.asFloatBuffer()
        colorBuffer.put(colors)
        colorBuffer.position(0)

        indexBuffer = ByteBuffer.allocateDirect(indexes.size)
        indexBuffer.put(indexes)
        indexBuffer.position(0)
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        gl?.glClearDepthf(1.0f)
        gl?.glEnable(GL10.GL_DEPTH_TEST)
        gl?.glDepthFunc(GL10.GL_LEQUAL)

        gl?.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT, GL10.GL_NICEST)
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        gl?.glViewport(0, 0, width, height)

        gl?.glMatrixMode(GL10.GL_PROJECTION)
        gl?.glLoadIdentity()

        GLU.gluPerspective(
            gl,
            45.0f,
            width.toFloat() / height.toFloat(),
            0.1f, 100.0f)

        gl?.glMatrixMode(GL10.GL_MODELVIEW)
        gl?.glLoadIdentity()
    }

    override fun onDrawFrame(gl: GL10?) {
        gl?.glClear(GL10.GL_COLOR_BUFFER_BIT or GL10.GL_DEPTH_BUFFER_BIT)
        gl?.glLoadIdentity()

        gl?.glTranslatef(0.0f, 0f, -10.0f)
        gl?.glRotatef(40f, 0.1f, 0f, 0f);
        gl?.glRotatef(rotation, 0f, 0.1f, 0f)

        gl?.glEnableClientState(GL10.GL_VERTEX_ARRAY)
        gl?.glEnableClientState(GL10.GL_COLOR_ARRAY)
        gl?.glEnableClientState(GL10.GL_ALIASED_LINE_WIDTH_RANGE)

        gl?.glVertexPointer(3, GL10.GL_FLOAT, 0, vertexBuffer)
        gl?.glColorPointer(4, GL10.GL_FLOAT, 0, colorBuffer)

        gl?.glDrawElements(
            GL10.GL_TRIANGLES,
            indexBuffer.remaining(),
            GL10.GL_UNSIGNED_BYTE,
            indexBuffer
        )

        gl?.glDisableClientState(GL10.GL_VERTEX_ARRAY)
        gl?.glDisableClientState(GL10.GL_COLOR_ARRAY)

        rotation -= 1.15f
    }
}