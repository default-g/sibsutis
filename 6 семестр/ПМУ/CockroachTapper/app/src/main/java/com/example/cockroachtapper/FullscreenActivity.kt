package com.example.cockroachtapper

import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.view.MotionEvent
import androidx.appcompat.app.AppCompatActivity
import java.util.*


class FullscreenActivity : AppCompatActivity() {

    lateinit var gameView: GameView

    companion object {
        const val updateFrequency: Long = 1000 / 120
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        gameView = GameView(this)
        setContentView(gameView)
        supportActionBar?.hide()

        val handler: Handler = Handler()
        val timer = Timer()
        timer.schedule(object : TimerTask() {
            override fun run() {
                handler.post {
                    gameView.invalidate()
                }
            }
        }, 0, updateFrequency)
    }

}