package com.example.tabs

import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ListView


class SecondFragment : Fragment() {

    lateinit var theView: View

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        theView = inflater.inflate(R.layout.fragment_second, container, false)
        val list = theView.findViewById<ListView>(R.id.list)
        val texts = arrayOf("1", "2", "3")
        val adapter = ArrayAdapter(theView.context, android.R.layout.simple_list_item_1, texts)
        list.adapter = adapter

        return theView
    }


}