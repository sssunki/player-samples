package com.example.casanova

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.os.Environment
import android.provider.MediaStore
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.casanova.model.MediaRepo
import com.example.casanova.model.Video
import com.example.casanova.player.`interface`.CasanovaBuilder
import com.example.casanova.player.ni.FFmpegPlayer
import com.google.android.exoplayer2.MediaItem
import com.google.android.exoplayer2.SimpleExoPlayer
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    lateinit var recyclerView: RecyclerView
    lateinit var layoutManager: LinearLayoutManager
    lateinit var adapter: SAdapter
    private val assetsVideoPath = Environment.getExternalStorageDirectory().absolutePath + "/sunkaiyi/one_piece.mp4"
    private var videoList = mutableListOf<Video>()
    private lateinit var player: SimpleExoPlayer

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        ContextUtil.initApplicationContext(applicationContext)
        recyclerView = findViewById(R.id.recyclerView)
        layoutManager = LinearLayoutManager(this)

        initPlayer()

        val dataSet = arrayListOf(
            "sun", "kai", "yi", "test"
        )

        request_video.text = FFmpegPlayer().getStringFromJNI()

        adapter = SAdapter(dataSet)
        recyclerView.apply {
            setHasFixedSize(true)
            layoutManager = this@MainActivity.layoutManager
            adapter = this@MainActivity.adapter
        }

        request_video.setOnClickListener {
            requestPermission()
        }

        play_button.setOnClickListener {
            FFmpegPlayer().initDecoder(assetsVideoPath, surface_view.holder.surface)
        }

    }

    private fun initPlayer() {
        player = SimpleExoPlayer.Builder(this).build()
        player.setVideoSurfaceView(surface_view)
    }

    private fun requestPermission() {
        when {
            ContextCompat.checkSelfPermission(
                ContextUtil.context,
                Manifest.permission.WRITE_EXTERNAL_STORAGE
            ) == PackageManager.PERMISSION_GRANTED -> {
                MediaRepo.INSTANCE.getData(videoList)
            }

            else -> {
                requestPermissions(
                    arrayOf(Manifest.permission.WRITE_EXTERNAL_STORAGE,
                        Manifest.permission.RECORD_AUDIO),
                    0
                )
            }

        }
    }

    private fun startPlay() {
        val uri = videoList[1].uri
        var mediaItem = MediaItem.fromUri(uri)
        player.apply {
            setMediaItem(mediaItem)
            prepare()
            play()
        }

    }
}