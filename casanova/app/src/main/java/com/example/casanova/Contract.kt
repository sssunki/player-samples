package com.example.casanova

import com.example.casanova.model.Video

interface Contract {
    interface Repo {
        fun getData(videoList: MutableList<Video>)
    }
}