package com.example.secondlab
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.widget.FrameLayout
import java.util.Random

class MainActivity : AppCompatActivity() {

    private val renderers = arrayOf(Square(), Cube(), Sphere())

    private var currentItem = 0
    private fun changeCurrentRenderer(): Int {
        currentItem++
        if (currentItem >= renderers.size) {
            currentItem = 0
        }
        return currentItem
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var glSurfaceView = GLSurfaceView(this)
        val glRendererLayout = findViewById<FrameLayout>(R.id.glRenderer)

        glRendererLayout.addView(glSurfaceView)

        // Set a click listener to change the renderer (you can customize this logic)
        glRendererLayout.setOnClickListener {

            glSurfaceView = GLSurfaceView(this)
            glSurfaceView.setRenderer(renderers[changeCurrentRenderer()]) // Change to the desired renderer
            glRendererLayout.removeAllViews()
            glRendererLayout.addView(glSurfaceView)
        }
    }
}
