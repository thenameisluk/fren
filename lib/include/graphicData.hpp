#pragma once
#include <stdint.h>

//can be multiple colors
struct Sprite{
    /*
    first byte
    X
    X> palet size(bits per pixel) 2(1)/4(2)/16(4)/256(8)
    
    X> alpha channel (0 ^ = alpha)

    X
    X> compression none/rle/?/?
    
    X
    X
    X> unknown
    */
    
    //metadata
    uint8_t spriteInfo; // paletSize 00/01/10/11 (2/4/16/256) + 0/1 alpha !! compressin info from first byte is ommited
    //size
    uint32_t w;
    uint32_t h;
    //data
    uint32_t* pallet;//size with alpha => paletSize - 1 / without => paletSize
    uint8_t* data;//already uncompressed
};

//can be any (one) color and is just a shape
struct Symbol{
    /*
    first byte
    X
    X> compression 00/01/10 (none/rle/srle)
    
    X
    X
    X
    X
    X
    X> unknown
    */

    uint32_t w;
    uint32_t h;
    uint8_t* data;//already uncompressed
};