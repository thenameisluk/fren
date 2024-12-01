#pragma once
#include <stdint.h>
//might add image later

//can be up to 15 colors + alpha
struct Sprite{
    /*
    first uint8_t
    X
    X> compression none/rle/?/?

    rest discarder
    */
    //size
    uint32_t w;
    uint32_t h;
    //data
    uint32_t pallet[15];
    uint8_t* data;//already uncompressed
};

//can be any (one) color and is just a shape
struct Symbol{
    /*
    first uint8_t
    X
    X> compression 00/01/10 (none/rle/srle)

    rest discarder
    */
    //size
    uint32_t w;
    uint32_t h;
    //data
    uint8_t* data;//already uncompressed
};