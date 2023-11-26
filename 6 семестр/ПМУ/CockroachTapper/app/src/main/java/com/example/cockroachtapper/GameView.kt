package com.example.cockroachtapper

import android.view.View
import android.content.Context
import android.graphics.*
import android.view.MotionEvent

class GameView: View {
    var background: Bitmap
    var scoreStyle: Paint
    var strokeScoreStyle: Paint
    val gameController: GameController = GameController(5u, this)


    constructor(context: Context) : super(context) {
        background = BitmapFactory.decodeResource(context.resources, R.drawable.img_1)
        scoreStyle = Paint()
        scoreStyle.color = Color.RED
        scoreStyle.textAlign = Paint.Align.LEFT;
        scoreStyle.textSize = 150F
        scoreStyle.typeface = Typeface.DEFAULT_BOLD;
        scoreStyle.isAntiAlias = true;

        strokeScoreStyle = Paint(scoreStyle)
        strokeScoreStyle.style = Paint.Style.STROKE
        strokeScoreStyle.strokeWidth = 3F
        strokeScoreStyle.color = Color.WHITE
    }


    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        gameController.update()
        canvas.drawBitmap(background, -500F, 0F, null)

        gameController.drawBugs(canvas)

        var text: String = gameController.score.toString()
        var x = 100F
        var y = 200F
        canvas.drawText(text, x, y, scoreStyle)
        canvas.drawText(text, x, y, strokeScoreStyle)

        text = gameController.remainingTimeString
        x = width - 300F
        y = 200F
        canvas.drawText(text, x, y, scoreStyle)
        canvas.drawText(text, x, y, strokeScoreStyle)

    }


    override fun onTouchEvent(event: MotionEvent): Boolean {
        if (event.action == MotionEvent.ACTION_DOWN) {
            val x = event.x
            val y = event.y
            gameController.touchEvent(x, y)
        }
        return true
    }

}