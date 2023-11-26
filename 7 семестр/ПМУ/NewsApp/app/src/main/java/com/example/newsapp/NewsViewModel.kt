package com.example.newsapp

import androidx.compose.runtime.State
import androidx.compose.runtime.mutableStateListOf
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow

class NewsViewModel : ViewModel() {
    var newsList = MutableStateFlow(
        listOf(
            New("News 1", 0),
            New("News 2", 0),
            New("News 3", 0),
            New("News 4", 0),
            New("News 5", 0),
            New("News 6", 0),
            New("News 8", 0),
            New("News 9", 0),
            New("News 10", 0)
        ))

    init {
        changeNews()
    }

    fun changeNews() {
        newsList.value = newsList.value.shuffled()
    }

    fun incrementLikes(new: New) {
        val news = newsList.value.toMutableList()
        val index =news.indexOfFirst { it == new }
        if (index != -1) {
            val updatedNew = news[index].copy(likes = new.likes + 1)
            news[index] = updatedNew
            newsList.value = news
        }
    }



}