package com.example.databaseapp

import android.database.Cursor
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteException
import android.database.sqlite.SQLiteOpenHelper
import android.os.Bundle
import android.widget.TableLayout
import android.widget.TableRow
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity


class MainActivity : AppCompatActivity() {
    private lateinit var db: SQLiteDatabase
    private lateinit var cursor: Cursor
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val tableLayout = findViewById<TableLayout>(R.id.table)
        val studentsDatabaseHelper: SQLiteOpenHelper = StudentsDatabaseHelper(this)
        try {
            db = studentsDatabaseHelper.readableDatabase
            cursor = db.query(
                "STUDENTS", arrayOf("NAME", "WEIGHT", "HEIGHT", "AGE"),
                null, null, null, null, "AGE"
            )
            while (cursor.moveToNext()) {
                val row = TableRow(this)
                val tvName = TextView(this)
                tvName.text = cursor.getString(0)
                val tvWeight = TextView(this)
                tvWeight.text = cursor.getInt(1).toString()
                val tvHeight = TextView(this)
                tvHeight.text = cursor.getInt(2).toString()
                val tvAge = TextView(this)
                tvAge.text = cursor.getString(3).toString()
                row.addView(tvName)
                row.addView(tvWeight)
                row.addView(tvHeight)
                row.addView(tvAge)
                tableLayout.addView(row)
            }
        } catch (e: SQLiteException) {
            Toast.makeText(this, "Database unavailable", Toast.LENGTH_SHORT).show()
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        cursor.close()
        db.close()
    }
}