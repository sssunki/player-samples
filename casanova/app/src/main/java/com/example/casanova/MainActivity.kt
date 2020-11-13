package com.example.casanova

import android.Manifest
import android.app.Application
import android.app.Instrumentation
import android.content.pm.PackageManager
import android.os.Build
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.annotation.RequiresApi
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.casanova.model.MediaRepo
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    lateinit var recyclerView: RecyclerView
    lateinit var layoutManager: LinearLayoutManager
    lateinit var adapter: SAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        ContextUtil.initApplicationContext(applicationContext)
        recyclerView = findViewById(R.id.recyclerView)
        layoutManager = LinearLayoutManager(this)
        val dataSet = arrayListOf(
            "sun", "kai", "yi", "test"
        )
        adapter = SAdapter(dataSet)
        recyclerView.apply {
            setHasFixedSize(true)
            layoutManager = this@MainActivity.layoutManager
            adapter = this@MainActivity.adapter
        }

        add_item.setOnClickListener {
            adapter.addData("sunkaiyi")
        }


    }

    private fun requestPermission() {
        when {
            ContextCompat.checkSelfPermission(
                ContextUtil.context,
                Manifest.permission.READ_EXTERNAL_STORAGE
            ) == PackageManager.PERMISSION_GRANTED -> {
                MediaRepo.INSTANCE.getData()
            }

            else -> {
                requestPermissions(
                    arrayOf(Manifest.permission.READ_EXTERNAL_STORAGE),
                    0
                )
            }

        }
    }
}