package com.example.casanova.player.ni

import android.view.Surface

class FFmpegPlayer {

    public external fun init(url: String)
    public external fun getStringFromJNI(): String
    public external fun initDecoder(url: String, surface: Surface)

    companion object {
        init {
            System.loadLibrary("player-internal")
            System.loadLibrary("avcodec")
            System.loadLibrary("avfilter")
            System.loadLibrary("avformat")
            System.loadLibrary("avutil")
            System.loadLibrary("swresample")
            System.loadLibrary("swscale")
        }
    }

}