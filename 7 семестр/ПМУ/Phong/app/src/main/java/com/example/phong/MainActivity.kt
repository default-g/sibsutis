package com.example.phong

import android.opengl.GLSurfaceView
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val GLView = GLSurfaceView(this)
        GLView.setEGLContextClientVersion(2)
        GLView.setRenderer(MyRenderEngine())
        setContentView(GLView)
    }
}