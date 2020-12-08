package com.example.casanova.player.ni

class JNIT {

    public external fun getStringFromJNI(): String
    public external fun initPlayer(url: String)

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