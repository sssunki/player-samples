package com.example.casanova

import android.content.Context

object ContextUtil {

    lateinit var context: Context

    fun initApplicationContext(context: Context) {
        this.context = context
    }

}