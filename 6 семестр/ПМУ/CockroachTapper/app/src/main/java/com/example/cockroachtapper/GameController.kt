package com.example.cockroachtapper


import android.graphics.Canvas
import android.media.MediaPlayer
import android.os.CountDownTimer
import kotlin.math.abs
import kotlin.streams.toList


class GameController {
    private var bugs: ArrayList<Bug>
    private val amountOfBugs: UInt
    private val parentGameView: GameView
    var gameRunning: Boolean = false
    var score: Int = 0
    val hitSound: MediaPlayer
    val missSound: MediaPlayer
    var remainingTimeString: String = "30s"
    val gameTimer: CountDownTimer = object : CountDownTimer(30 * 1000, 1 * 1000) {
        override fun onTick(p0: Long) {
            remainingTimeString = (p0 / 1000).toString() + "s"
        }

        override fun onFinish() {
            finishGame()
        }

    }


    constructor(amountOfBugs: UInt, parentGameView: GameView) {
        this.amountOfBugs = amountOfBugs
        this.parentGameView = parentGameView
        bugs = ArrayList(amountOfBugs.toInt())
        hitSound = MediaPlayer.create(parentGameView.context, R.raw.hit)
        missSound = MediaPlayer.create(parentGameView.context, R.raw.miss)
    }


    fun touchEvent(x: Float, y: Float) {
        if (!gameRunning) {
            score = 0
            gameRunning = true
            gameTimer.start()
            return
        }
        var hit = false
        for (bug in bugs) {
            if (abs(bug.position.x - x + 60) < 140 && abs(bug.position.y - y + 60) < 150) {
                hitSound.start()
                bug.die()
                score += 10
                hit = true
                break
            }
        }
        if (!hit) {
            missSound.start()
            score -= 10
            score = if (score < 0) 0 else score
        }
    }


    fun createBug(): Bug {
        val newBug: Bug = Bug(parentGameView)
        bugs.add(newBug)
        newBug.matrix.setRotate(0F, (newBug.texture.width / 2).toFloat(),
            (newBug.texture.height / 2).toFloat()
        )
        newBug.matrix.reset()
        newBug.p = 0
        newBug.isRunning = false
        val temp = (Math.random() * 4).toInt()

        when(temp) {
            0 -> {
                newBug.position.x = 0F
                newBug.position.y = (Math.random() * parentGameView.height).toFloat()
            }
            1 -> {
                newBug.position.x = parentGameView.width.toFloat()
                newBug.position.y = (Math.random() * parentGameView.width).toFloat()
            }
            2 -> {
                newBug.position.x = (Math.random() * parentGameView.width).toFloat()
                newBug.position.y = 0F
            }
            3 -> {
                newBug.position.x = (Math.random() * parentGameView.width).toFloat()
                newBug.position.y = parentGameView.height.toFloat()
            }
        }
        newBug.matrix.postTranslate(newBug.position.x, newBug.position.y)

        return newBug
    }


    fun drawBugs(canvas: Canvas) {
        bugs.forEach {
                bug -> canvas.drawBitmap(bug.texture, bug.matrix, null)
        }
    }


    private fun removeDead() {
        bugs = ArrayList(
            bugs.stream()
                .filter { bug -> bug.isAlive }
                .toList()
        )
    }


    @Synchronized fun finishGame() {
        bugs.clear()
        gameRunning = false
    }


    fun update() {
        if (!gameRunning) {
            return
        }
        removeDead()
        while(bugs.size < amountOfBugs.toInt()) {
           Thread(createBug()).start()
        }
    }
}