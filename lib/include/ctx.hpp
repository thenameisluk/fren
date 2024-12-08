#pragma once
#include <stdint.h>

struct context{
    uint32_t width;
    uint32_t height;
    uint32_t* data;
};

struct symbol{
    uint32_t width;
    uint32_t height;
    uint8_t* data;
    //0b0000
    //  0001
    //  1010
    //  0100
};

extern "C" uint32_t getWidth(context* ctx);

extern "C" uint32_t getHeight(context* ctx);

extern "C" uint32_t getColor(uint8_t r,uint8_t g,uint8_t b);

// ctx

extern "C" void drawLineLeftRight(context *ctx, int32_t x, int32_t y, int32_t l, uint32_t c);

extern "C" void drawLineUpDown(context *ctx, int32_t x, int32_t y, int32_t l, uint32_t c);

extern "C" void fillRect(context *ctx, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t c);

extern "C" void drawRect(context *ctx, int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t c); // to-optimize

extern "C" void fill(context *ctx, uint32_t c);

// Important
// to-optimize/fix (cut the lines outside)
extern "C" void drawLine(context *ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t c);

extern "C" void drawTriangle(context *ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t c);

extern "C" void fillCircle(context *ctx,int32_t x, int32_t y, uint32_t radius, uint32_t c);

extern "C" void fillThickLine(context *ctx,int32_t x1, int32_t y1,int32_t x2, int32_t y2,uint32_t thickness,uint32_t c);

uint32_t getLen(int32_t x1, int32_t y1,int32_t x2, int32_t y2);

extern "C" void fillThickCurvedLine(context *ctx,int32_t x1, int32_t y1,int32_t x2, int32_t y2,int32_t offx,int32_t offy,uint32_t thickness,uint32_t c);

extern "C" void fillTriangle(context *ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t c);

void drawLetter(context *ctx, char ch, int32_t x, int32_t y, int32_t scale, uint32_t c);

void drawSymbol(context *ctx, symbol* s, int32_t x, int32_t y, int32_t scale, uint32_t c);

// void drawCtx(int32_t x, int32_t y, ctx &context, uint8_t scale)
// {
//     for (int32_t ix = 0; ix < context.width; ix++)
//     {
//         for (int32_t iy = 0; iy < context.height; iy++)
//         {
//             fillRect(x + ix * scale, y + iy * scale, scale, scale, context.img[ix + context.width * iy]);
//         }
//     }
// }

extern "C" void print(context *ctx, const char *text, int32_t x, int32_t y, uint32_t scale, uint32_t c);