package com.example.databaseapp

import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteException
import android.database.sqlite.SQLiteOpenHelper


class StudentsDatabaseHelper(private val context: Context) :
    SQLiteOpenHelper(context, DB_NAME, null, DB_VERSION) {
    override fun onCreate(db: SQLiteDatabase) {
        db.execSQL(
            "CREATE TABLE STUDENTS (_id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                    "NAME TEXT, " +
                    "WEIGHT INTEGER, " +
                    "HEIGHT INTEGER, " +
                    "AGE INTEGER);"
        )
        val sg = StudentsGenerator(context)
        for (i in 0..999) {
            insertStudent(db, sg.generateName(), sg.generateWeight(), sg.generateHeight(), sg.generateAge())
        }
    }

    override fun onUpgrade(db: SQLiteDatabase, oldVersion: Int, newVersion: Int) {
        throw SQLiteException("Database cannot be upgraded")
    }

    companion object {
        private val DB_NAME = "students"
        private val DB_VERSION = 1
        private fun insertStudent(
            db: SQLiteDatabase,
            name: String,
            weight: Int,
            height: Int,
            age: Int
        ) {
            val studentValues = ContentValues()
            studentValues.put("NAME", name)
            studentValues.put("WEIGHT", weight)
            studentValues.put("HEIGHT", height)
            studentValues.put("AGE", age)
            db.insert("STUDENTS", null, studentValues)
        }
    }
}