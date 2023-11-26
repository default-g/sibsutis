package com.example.newsapp

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.BorderStroke
import androidx.compose.foundation.border
import androidx.compose.foundation.layout.*
import androidx.compose.material.Button
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Surface
import androidx.compose.material.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.dp
import com.example.newsapp.ui.theme.NewsAppTheme
import kotlinx.coroutines.delay


class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            NewsAppTheme {
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colors.background
                ) {
                    NewsApp()
                }
            }
        }
    }
}


val newsViewModel: NewsViewModel = NewsViewModel()

@Composable
@Preview
fun NewsApp() {

    LaunchedEffect(Unit) {
        while(true) {
            delay(5000)

            newsViewModel.changeNews()

        }
    }

    val currentNews by newsViewModel.newsList.collectAsState()
    Column(Modifier.fillMaxSize()) {
        Row(Modifier.weight(1f)) {
            Column(Modifier.weight(1f)) {
                NewCard(new = currentNews[0])
            }
            Column(Modifier.weight(1f)) {
                Column(Modifier.weight(1f)) {
                    NewCard(new = currentNews[1])
                }
            }
        }
        Row(Modifier.weight(1f)) {
            Column(Modifier.weight(1f)) {
                Column(Modifier.weight(1f)) {
                    NewCard(new = currentNews[2])
                }
            }
            Column(Modifier.weight(1f)) {
                Column(Modifier.weight(1f)) {
                    NewCard(new = currentNews[3])
                }
            }
        }
    }
}


@Composable
fun NewCard(new: New) {
    Column(modifier = Modifier.fillMaxSize().border(BorderStroke(1f.dp, Color.Black))) {
        Row(modifier = Modifier.weight(0.9f)) {
            Text(text = new.content)
        }
        Row(modifier = Modifier.weight(0.1f)) {
            Button(onClick = { newsViewModel.incrementLikes(new) }, modifier = Modifier
                .padding(1.dp)
                .fillMaxSize()) {
                Text(text = new.likes.toString(), modifier = Modifier.fillMaxSize())
            }
        }

    }
}

