package com.example.databaseapp

import android.content.Context
import java.util.*

class StudentsGenerator(context: Context) {
    private val names: List<String> = arrayListOf(
        "Дмитрий",
        "Артём",
        "Владимир",
        "Андрей"
    )
    private val random = Random()

    fun generateName(): String {
        return names[random.nextInt(names.size)]
    }

    fun generateWeight(): Int {
        return random.nextInt(40) + 50
    }

    fun generateHeight(): Int {
        return random.nextInt(50) + 150
    }

    fun generateAge(): Int {
        return random.nextInt(10) + 17
    }
}