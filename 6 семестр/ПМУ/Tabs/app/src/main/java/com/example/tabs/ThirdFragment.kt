package com.example.tabs

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.RelativeLayout
import android.widget.TableLayout
import android.widget.TableRow
import android.widget.TextView


class ThirdFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_third, container, false)
        val relativeLayout = view.findViewById<RelativeLayout>(R.id.main)
        val tableLayout = TableLayout(view.context)
        tableLayout.setColumnStretchable(0, true)
        tableLayout.setColumnStretchable(1, true)


        for (i in 0..10 step 2) {
            val tableRow = TableRow(view.context)
            val textView = TextView(view.context)
            textView.text = i.toString()
            tableRow.addView(textView)

            val textView2 = TextView(view.context)
            textView2.text = (i + 1).toString()
            tableRow.addView(textView2)

            tableLayout.addView(tableRow)
        }

        relativeLayout.addView(tableLayout)

        return view
    }
}