package com.example.casanova.player.ni

class JNIT {

    public external fun getStringFromJNI(): String

    companion object {
        init {
            System.loadLibrary("my-sdk")
        }
    }

}