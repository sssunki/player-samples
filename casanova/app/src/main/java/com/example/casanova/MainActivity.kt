package com.example.casanova

import android.Manifest
import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.util.Log
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.casanova.model.MediaRepo
import com.example.casanova.model.Video
import com.example.casanova.player.`interface`.CasanovaBuilder
import com.example.casanova.player.ni.JNIT
import com.google.android.exoplayer2.MediaItem
import com.google.android.exoplayer2.SimpleExoPlayer
import kotlinx.android.synthetic.main.activity_main.*
import kotlin.math.log

class MainActivity : AppCompatActivity() {

    lateinit var recyclerView: RecyclerView
    lateinit var layoutManager: LinearLayoutManager
    lateinit var adapter: SAdapter
    private val casanova by lazy {
        CasanovaBuilder.build()
    }
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

        request_video.text = JNIT().getStringFromJNI()

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
            val i = 2
            val mVideoPath = videoList[i].uri.toString() + "/" + videoList[i].name
            JNIT().initPlayer(mVideoPath)
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
                Manifest.permission.READ_EXTERNAL_STORAGE
            ) == PackageManager.PERMISSION_GRANTED -> {
                MediaRepo.INSTANCE.getData(videoList)
            }

            else -> {
                requestPermissions(
                    arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE),
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
            play()
        }

    }
}