package com.example.casanova.player.`interface`

import com.example.casanova.player.internal.CasanovaImpl

class CasanovaBuilder {

    public fun build(): Casanova {
        return CasanovaImpl()
    }

}