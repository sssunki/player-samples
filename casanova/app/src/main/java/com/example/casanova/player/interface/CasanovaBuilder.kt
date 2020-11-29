package com.example.casanova.player.`interface`

import com.example.casanova.player.internal.CasanovaImpl

class CasanovaBuilder {

    companion object {
        public fun build(): Casanova {
            return CasanovaImpl()
        }
    }

}