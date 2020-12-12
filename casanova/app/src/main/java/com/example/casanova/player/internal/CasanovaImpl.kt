package com.example.casanova.player.internal

import android.net.Uri
import android.os.Environment
import android.provider.MediaStore
import android.view.Surface
import android.view.SurfaceView
import com.example.casanova.ContextUtil
import com.example.casanova.player.`interface`.Casanova
import com.example.casanova.player.ni.FFmpegPlayer

class CasanovaImpl : Casanova {

    private lateinit var surface: Surface
    public var surfaceView: SurfaceView? = null
    set(value) {
        surface = value?.holder?.surface!!
        field = value
    }

    private lateinit var path: String
    public var mediaSourceUri: Uri? = null
    set(value) {
        ContextUtil.context.contentResolver
            .query(value!!, arrayOf(MediaStore.Video.Media.DATA),
                null, null, null)
            ?.apply {
                val columnIndex = getColumnIndexOrThrow(MediaStore.Video.Media.DATA)
                moveToFirst()
                path = getString(columnIndex)
            }?.close()
        field = value
    }

    private val playerInternal: FFmpegPlayer by lazy {
        FFmpegPlayer()
    }

    override fun init() {
        playerInternal.init("url");
    }

    override fun setVideoSurface(surface: SurfaceView) {

    }

    override fun setMediaSource(uri: Uri) {
        TODO("Not yet implemented")
    }

    override fun prepare() {


    }

    override fun play() {
        TODO("Not yet implemented")
    }

    override fun pause() {
        TODO("Not yet implemented")
    }

    override fun release() {
        TODO("Not yet implemented")
    }
}