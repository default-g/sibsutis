package com.example.solarSystem.entity

import android.content.Context
import android.opengl.GLSurfaceView
import com.example.solarSystem.Globe
import com.example.solarSystem.R
import java.nio.ByteBuffer
import java.nio.ByteOrder
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10
import kotlin.math.tan


class SolarSystem(private var context: Context) :
    GLSurfaceView.Renderer {
    private var earth: Globe? = null
    private var sun: Globe? = null
    private var moon: Globe? = null
    private val eyePosition = floatArrayOf(0.0f, 0.0f, 0.0f)

    private fun initGeometry(gl: GL10) {
        eyePosition[X_VALUE] = 0.0f
        eyePosition[Y_VALUE] = 0.0f
        eyePosition[Z_VALUE] = 10.0f
        val resId: Int = R.drawable.earth
        val resIdMoon: Int = R.drawable.moon
        moon = Globe(50, 50, .1f, 1.0f, gl, context, true, resIdMoon)
        moon?.setPosition(0.0f, 0.0f, -1f)
        earth = Globe(50, 50, .3f, 1.0f, gl, context, true, resId)
        earth?.setPosition(0.0f, 0.0f, -2.0f)
        sun = Globe(50, 50, 1.0f, 1.0f, gl, context, false, 0)
        sun?.setPosition(0.0f, 0.0f, 0.0f)
    }

    private fun initSunTexture(gl: GL10) {
        with(gl) {
            glEnable(GL10.GL_LIGHTING)
            glEnable(SS_SUNLIGHT)
        }
    }

    private fun executePlanet(globe: Globe?, gl: GL10) {
        globe?.let {
            with(gl) {
                glTranslatef(it.pos[0], it.pos[1], it.pos[2])
                glRotatef(angle, it.pos[1], 2f , it.pos[2])
                it.draw(gl)
            }
        }
    }

    private var angle = 0.0f
    private var moonAngle = 0.0f;
    private var orbitalIncrement = 1f;
    override fun onDrawFrame(gl: GL10) {
        val paleYellow = floatArrayOf(1.0f, 1.0f, 0.3f, 1.0f)
        val black = floatArrayOf(0.0f, 0.0f, 0.0f, 0.0f)

        with(gl) {
            glEnable(GL10.GL_DEPTH_TEST)
            glClear(GL10.GL_COLOR_BUFFER_BIT or GL10.GL_DEPTH_BUFFER_BIT)
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f)
            glMatrixMode(GL10.GL_MODELVIEW)
            glLoadIdentity()
            glPushMatrix()
            glTranslatef(-eyePosition[X_VALUE], -eyePosition[Y_VALUE], -eyePosition[Z_VALUE])
            glPushMatrix()
            angle += orbitalIncrement
            glRotatef(angle, 0.0f, 1.0f, 0.0f)
            glPushMatrix()
            earth?.let {
                glTranslatef(it.pos[0], it.pos[1], it.pos[2])
                //glRotatef(angle, it.pos[0], it.pos[1] , it.pos[2])
                it.draw(gl)
            }

            glPushMatrix()
            moon?.let {
                moonAngle += orbitalIncrement
                glRotatef(moonAngle, 0f, 0.01f, 0f)
                glTranslatef(it.pos[0], it.pos[1], it.pos[2])
                it.draw(gl)
            }
            glPopMatrix()
            glPopMatrix()
            glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_EMISSION, makeFloatBuffer(paleYellow))
            glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SPECULAR, makeFloatBuffer(black))
            sun?.let {
                glTranslatef(it.pos[0], it.pos[1], it.pos[2])
           //     glRotatef(angle, it.pos[1], 2f , it.pos[2])
                it.draw(gl)
            }
            glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_EMISSION, makeFloatBuffer(black))
            glPopMatrix()
        }
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        with(gl) {
            val zNear = .1f
            val zFar = 1000f
            val fieldOfView = 0.6f
            val aspectRatio: Float = width.toFloat() / height.toFloat()
            glMatrixMode(GL10.GL_PROJECTION)
            val size: Float = zNear * tan((fieldOfView / 2.0f).toDouble()).toFloat()
            glFrustumf(
                -size, size, -size / aspectRatio,
                size / aspectRatio, zNear, zFar
            )
        }
    }

    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        with(gl) {
            initGeometry(this)
            initSunTexture(this)
        }
    }

    companion object {
        const val SS_SUNLIGHT = GL10.GL_LIGHT0
        const val X_VALUE = 0
        const val Y_VALUE = 1
        const val Z_VALUE = 2
        private fun makeFloatBuffer(arr: FloatArray) =
            ByteBuffer.allocateDirect(arr.size * 4).apply {
                order(ByteOrder.nativeOrder())
            }.asFloatBuffer().apply {
                put(arr)
                position(0)
            }
    }
}