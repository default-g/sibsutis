package com.example.phong

import android.opengl.GLES20
import android.opengl.GLSurfaceView
import android.opengl.Matrix
import com.example.phong.MySphere
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyRenderEngine : GLSurfaceView.Renderer {
    private var sphere: MySphere? = null
    var vm_matrix = FloatArray(16)
    var mvp_matrix = FloatArray(16)
    var pvm_matrix = FloatArray(16)
    var invert_matrix = FloatArray(16)
    var normal_matrix = FloatArray(16)
    var rotation_x_matrix = FloatArray(16)
    var rotation_y_matrix = FloatArray(16)
    private val projection_matrix = FloatArray(16)
    override fun onSurfaceCreated(unused: GL10, cfg: EGLConfig) {
        sphere = MySphere(90, 600)
        GLES20.glClearColor(0f, 100f, 90f, 1.0f)
        GLES20.glEnable(GL10.GL_DEPTH_TEST)
        GLES20.glDepthFunc(GL10.GL_LEQUAL)
    }

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int) {
        GLES20.glViewport(0, 0, width, height)
        Matrix.frustumM(
            projection_matrix,
            0,
            -width.toFloat() / height,
            width.toFloat() / height,
            -1f,
            1f,
            1f,
            20f
        )
    }

    var angle = -1.2f
    override fun onDrawFrame(unused: GL10) {
        val scale_matrix = FloatArray(16)
        val final_matrix = FloatArray(16)
        val temporary_matrix = FloatArray(16)

//        float angle = (float) (Math.cos((float)(SystemClock.uptimeMillis() % TIME) / TIME  *  2 * Math.PI) * 4f);
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT or GLES20.GL_DEPTH_BUFFER_BIT)
        GLES20.glClearColor(0f, 0f, 0f, 1.0f)
        Matrix.setLookAtM(vm_matrix, 0, -1f, 0f, -1f, -1f, 0f, 0f, 25.0f, 5.0f, 25.0f)
        //Matrix.setRotateM(vm_matrix, 0, 0.0f, 0f, 0f, 0f)

        Matrix.multiplyMM(pvm_matrix, 0, projection_matrix, 0, vm_matrix, 0)
        Matrix.setRotateM(rotation_x_matrix, 0, 0f, 5.0f, 5.0f, 0f)
        Matrix.setRotateM(rotation_y_matrix, 0, 0f, 5.0f, 5.0f, 0f)
        Matrix.multiplyMM(temporary_matrix, 0, pvm_matrix, 0, rotation_x_matrix, 0)
        Matrix.multiplyMM(mvp_matrix, 0, temporary_matrix, 0, rotation_y_matrix, 0)
        Matrix.multiplyMM(temporary_matrix, 0, vm_matrix, 0, rotation_x_matrix, 0)
        Matrix.multiplyMM(invert_matrix, 0, temporary_matrix, 0, rotation_y_matrix, 0)
        Matrix.invertM(temporary_matrix, 0, invert_matrix, 0)
        Matrix.transposeM(normal_matrix, 0, temporary_matrix, 0)
        Matrix.setLookAtM(vm_matrix, 0, angle, 1f, angle, 0f, 0f, 0f, 1f, 1f, 1f)
        Matrix.setIdentityM(scale_matrix, 0)
        Matrix.scaleM(scale_matrix, 0,  2f, 2f, 1f)
        //Matrix.scaleM(scale_matrix, 0, 2f, 2f, 2f)
        Matrix.multiplyMM(temporary_matrix, 0, mvp_matrix, 0, scale_matrix, 0)
        Matrix.translateM(final_matrix, 0, temporary_matrix, 0, -1.7f, 0f, 5f)
        sphere!!.draw(final_matrix, normal_matrix, vm_matrix)
    }

    companion object {
        private const val TIME: Long = 5000
    }
}