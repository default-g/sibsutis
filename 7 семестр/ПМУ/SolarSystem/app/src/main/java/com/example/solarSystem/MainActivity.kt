package com.example.solarSystem

import com.example.solarSystem.entity.*
import android.opengl.GLSurfaceView
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.example.solarSystem.entity.SolarSystem

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        val view = GLSurfaceView(this)
        view.setRenderer(SolarSystem(this))
        setContentView(view)
    }
}