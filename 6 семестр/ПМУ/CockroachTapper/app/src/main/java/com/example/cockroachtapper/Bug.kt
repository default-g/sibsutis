package com.example.cockroachtapper

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.graphics.Matrix
import android.graphics.PointF
import android.os.SystemClock.sleep
import android.view.View
import java.util.concurrent.ThreadLocalRandom
import kotlin.math.abs
import kotlin.math.atan
import kotlin.math.floor

class Bug: Runnable {

    private var parentView: View
    var matrix: Matrix = Matrix()
    var isAlive: Boolean = true
    var isRunning: Boolean = false
    var texture: Bitmap
    var position: PointF = PointF(0.0F, 0.0F)
    var destination: PointF = PointF(0.0F, 0.0F)
    var step: PointF = PointF(0.0F, 0.0F)
    var p = 0

    constructor(parentView: View) {
        this.parentView = parentView
        val bugType = ThreadLocalRandom
            .current()
            .nextInt(0, 3)
        var drawableId = -1

        when(bugType) {
            0 -> drawableId = R.drawable.bug1
            1 -> drawableId = R.drawable.bug2
            else -> drawableId = R.drawable.bug3
        }

        texture = BitmapFactory.decodeResource(parentView.resources, drawableId)

    }


    override fun run() {
        while(isAlive) {
            if (!isRunning) {
                destination.x = (Math.random() * parentView.width).toFloat()
                destination.y = (Math.random() * parentView.height).toFloat()
                step.x = (destination.x - position.x) / 150
                step.y = (destination.y - position.y) / 150
                var tp: Int = if (position.x <= destination.x && position.y >= destination.y) floor(
                    Math.toDegrees(atan((abs(position.x - destination.x) / abs(position.y - destination.y)).toDouble()))
                ).toInt()
                else if (position.x <= destination.x && position.y <= destination.y) 90 + floor(
                    Math.toDegrees(atan(Math.abs(position.y - destination.y) / abs(position.x - destination.x)).toDouble())
                ).toInt()
                else if (position.x >= destination.x && position.y <= destination.y) 180 + floor(
                    Math.toDegrees(atan((abs(position.x - destination.x) / abs(position.y - destination.y)).toDouble()))
                ).toInt()
                else 270 + floor(
                    Math.toDegrees(atan((abs(position.y - destination.y) / abs(position.x - destination.x)).toDouble()))
                ).toInt()
                matrix.preRotate((tp - p).toFloat(), texture.width.toFloat() / 2, texture.height.toFloat() / 2 )
                p = tp
                isRunning = true
            } else {
                if (abs(position.x - destination.x) < 0.1 &&
                    abs(position.y - destination.y) < 0.1)
                    isRunning = false;

                matrix.postTranslate(step.x, step.y);
                position.x += step.x;
                position.y += step.y;
            }
            sleep(10)
        }
    }


    @Synchronized fun die() {
        isAlive = false
    }

}
