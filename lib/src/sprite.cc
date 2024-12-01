#include "../include/graphicData.hpp"
#include "../include/pureByte.hpp"

Sprite* loadSprite(const char* filename){
    Sprite* out = new Sprite;
    dataArray  file(filename);
    PbView raw(file);
    
    //read size
    out->w = raw.readStatic(32);
    out->h = raw.readStatic(32);

    //read palet
    for(uint32_t i = 0;i<15;i++){
        out->pallet[i] = raw.readStatic(32);
    }

    //read color
    uint32_t len = out->w*out->h;

    if(len%2==1)
        len++;
    
    len /= 2;

    //to-finish
    for(uint32_t i = 0;i<len;i++){
        out->data[i] = raw.readStatic(8);
    }

    return out;
}

Sprite* newSprite(uint32_t w,uint32_t h){
    Sprite* out = new Sprite;
    out->w=w;
    out->h=h;
    
    //clear pallet
    //palet doesn't require new since it's static
    for(uint32_t i = 0;i<15;i++){
        out->pallet[i] = 0;
    }

    //clear pixel data
    uint32_t len = w*h;

    if(len%2==1)
        len++;
    
    len /= 2;

    out->data = new uint8_t[len];

    for(uint32_t i = 0;i<len;i++){
        out->data[i] = 0;
    }
}

void setPixel(Sprite* spr,uint32_t x,uint32_t y,uint8_t index){
    if(index&0b11110000)
        throw "index out of bounds";
    
    uint32_t pos = x * y;
    bool offset = pos%2;

    if(offset)
        pos--;
    pos /= 2;

    if(offset)
        spr->data[pos] = (spr->data[pos]&0b11110000)|index;
    else
        spr->data[pos] = (spr->data[pos]&0b00001111)|(index<<4);
}


uint8_t getPixel(Sprite* spr,uint32_t x,uint32_t y){
    uint32_t pos = x * y;
    bool offset = pos%2;

    if(offset)
        pos--;
    pos /= 2;

    if(offset)
        return spr->data[pos]&0b00001111;
    else
        return spr->data[pos]&0b11110000;
}

void setPalletColor(Sprite* spr,uint8_t index,uint32_t c){
    //index 0 is not supported
    if(index&0b11110000 && !index)
        throw "index out of bounds";
    
    spr->pallet[index] = c;
}

uint32_t getSpriteWidth(Sprite* spr){
    return spr->w;
}

uint32_t getSpriteHeight(Sprite* spr){
    return spr->h;
}

void writeSprite(const char* filename){

}
