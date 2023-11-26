package com.example.compass

import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorManager
import android.os.Bundle
import android.view.View
import android.view.animation.Animation
import android.view.animation.RotateAnimation
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity(), SensorEventListener {
    // device sensor manager
    private var SensorManage: SensorManager? = null

    // define the compass picture that will be use
    private var compassimage: ImageView? = null

    // record the angle turned of the compass picture
    private var DegreeStart = 0f
    var DegreeTV: TextView? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        //
        compassimage = findViewById<View>(R.id.compass_image) as ImageView
        // TextView that will display the degree
        DegreeTV = findViewById<View>(R.id.DegreeTV) as TextView
        // initialize your android device sensor capabilities
        SensorManage = getSystemService(SENSOR_SERVICE) as SensorManager
    }

    override fun onPause() {
        super.onPause()
        // to stop the listener and save battery
        SensorManage!!.unregisterListener(this)
    }

    override fun onResume() {
        super.onResume()
        // code for system's orientation sensor registered listeners
        SensorManage!!.registerListener(
            this, SensorManage!!.getDefaultSensor(Sensor.TYPE_ORIENTATION),
            SensorManager.SENSOR_DELAY_GAME
        )
    }

    override fun onSensorChanged(event: SensorEvent) {
        // get angle around the z-axis rotated
        val degree = event.values[0]
        DegreeTV!!.text = String.format("%.2f", degree)
        // rotation animation - reverse turn degree degrees
        val ra = RotateAnimation(
            DegreeStart,
            -degree,
            Animation.RELATIVE_TO_SELF, 0.5f,
            Animation.RELATIVE_TO_SELF, 0.5f
        )
        // set the compass animation after the end of the reservation status
        ra.fillAfter = true
        // set how long the animation for the compass image will take place
        ra.duration = 210
        // Start animation of compass image
        compassimage!!.startAnimation(ra)
        DegreeStart = -degree
    }

    override fun onAccuracyChanged(sensor: Sensor, accuracy: Int) {
        // not in use
    }
}