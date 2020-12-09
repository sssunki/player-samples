package com.example.casanova.player.`interface`

import android.net.Uri
import android.view.SurfaceView

interface Casanova {

    fun init()
    fun setVideoSurface(surface: SurfaceView)
    fun setMediaSource(uri: Uri)
    fun prepare()
    fun play()
    fun pause()
    fun release()
}