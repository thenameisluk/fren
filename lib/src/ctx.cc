#include <stdint.h>
#include <iostream>
// #include <functional>
#include <cmath>
#include <algorithm>

#include "../include/window.hpp"

#define swp(a, b)   \
    {               \
        auto t = a; \
        a = b;      \
        b = t;      \
    }

#define max(a, b) {((a) > (b)) ? (a) : (b)}
#define min(a, b) {((a) < (b)) ? (a) : (b)}

// ascii
const inline uint64_t characters[] = {
    // https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h
    0x0000000000000000, // U+0020 (space)
    0x183C3C1818001800, // U+0021 (!)
    0x3636000000000000, // U+0022 (")
    0x36367F367F363600, // U+0023 (#)
    0x0C3E031E301F0C00, // U+0024 ($)
    0x006333180C666300, // U+0025 (%)
    0x1C361C6E3B336E00, // U+0026 (&)
    0x0606030000000000, // U+0027 (')
    0x180C0606060C1800, // U+0028 (()
    0x060C1818180C0600, // U+0029 ())
    0x00663CFF3C660000, // U+002A (*)
    0x000C0C3F0C0C0000, // U+002B (+)
    0x00000000000C0C06, // U+002C (,)
    0x0000003F00000000, // U+002D (-)
    0x00000000000C0C00, // U+002E (.)
    0x6030180C06030100, // U+002F (/)
    0x3E63737B6F673E00, // U+0030 (0)
    0x0C0E0C0C0C0C3F00, // U+0031 (1)
    0x1E33301C06333F00, // U+0032 (2)
    0x1E33301C30331E00, // U+0033 (3)
    0x383C36337F307800, // U+0034 (4)
    0x3F031F3030331E00, // U+0035 (5)
    0x1C06031F33331E00, // U+0036 (6)
    0x3F3330180C0C0C00, // U+0037 (7)
    0x1E33331E33331E00, // U+0038 (8)
    0x1E33333E30180E00, // U+0039 (9)
    0x000C0C00000C0C00, // U+003A (:)
    0x000C0C00000C0C06, // U+003B (;)
    0x180C0603060C1800, // U+003C (<)
    0x00003F00003F0000, // U+003D (=)
    0x060C1830180C0600, // U+003E (>)
    0x1E3330180C000C00, // U+003F (?)
    0x3E637B7B7B031E00, // U+0040 (@)
    0x0C1E33333F333300, // U+0041 (A)
    0x3F66663E66663F00, // U+0042 (B)
    0x3C66030303663C00, // U+0043 (C)
    0x1F36666666361F00, // U+0044 (D)
    0x7F46161E16467F00, // U+0045 (E)
    0x7F46161E16060F00, // U+0046 (F)
    0x3C66030373667C00, // U+0047 (G)
    0x3333333F33333300, // U+0048 (H)
    0x1E0C0C0C0C0C1E00, // U+0049 (I)
    0x7830303033331E00, // U+004A (J)
    0x6766361E36666700, // U+004B (K)
    0x0F06060646667F00, // U+004C (L)
    0x63777F7F6B636300, // U+004D (M)
    0x63676F7B73636300, // U+004E (N)
    0x1C36636363361C00, // U+004F (O)
    0x3F66663E06060F00, // U+0050 (P)
    0x1E3333333B1E3800, // U+0051 (Q)
    0x3F66663E36666700, // U+0052 (R)
    0x1E33070E38331E00, // U+0053 (S)
    0x3F2D0C0C0C0C1E00, // U+0054 (T)
    0x3333333333333F00, // U+0055 (U)
    0x33333333331E0C00, // U+0056 (V)
    0x6363636B7F776300, // U+0057 (W)
    0x6363361C1C366300, // U+0058 (X)
    0x3333331E0C0C1E00, // U+0059 (Y)
    0x7F6331184C667F00, // U+005A (Z)
    0x1E06060606061E00, // U+005B ([)
    0x03060C1830604000, // U+005C (\)
    0x1E18181818181E00, // U+005D (])
    0x081C366300000000, // U+005E (^)
    0x00000000000000FF, // U+005F (_)
    0x0C0C180000000000, // U+0060 (`)
    0x00001E303E336E00, // U+0061 (a)
    0x0706063E66663B00, // U+0062 (b)
    0x00001E3303331E00, // U+0063 (c)
    0x3830303e33336E00, // U+0064 (d)
    0x00001E333f031E00, // U+0065 (e)
    0x1C36060f06060F00, // U+0066 (f)
    0x00006E33333E301F, // U+0067 (g)
    0x0706366E66666700, // U+0068 (h)
    0x0C000E0C0C0C1E00, // U+0069 (i)
    0x300030303033331E, // U+006A (j)
    0x070666361E366700, // U+006B (k)
    0x0E0C0C0C0C0C1E00, // U+006C (l)
    0x0000337F7F6B6300, // U+006D (m)
    0x00001F3333333300, // U+006E (n)
    0x00001E3333331E00, // U+006F (o)
    0x00003B66663E060F, // U+0070 (p)
    0x00006E33333E3078, // U+0071 (q)
    0x00003B6E66060F00, // U+0072 (r)
    0x00003E031E301F00, // U+0073 (s)
    0x080C3E0C0C2C1800, // U+0074 (t)
    0x0000333333336E00, // U+0075 (u)
    0x00003333331E0C00, // U+0076 (v)
    0x0000636B7F7F3600, // U+0077 (w)
    0x000063361C366300, // U+0078 (x)
    0x00003333333E301F, // U+0079 (y)
    0x00003F190C263F00, // U+007A (z)
    0x380C0C070C0C3800, // U+007B ({)
    0x1818180018181800, // U+007C (|)
    0x070C0C380C0C0700, // U+007D (})
    0x6E3B000000000000, // U+007E (~)
    0x0000000000000000  // U+007F
};

// ctx

extern "C" void drawLineLeftRight(Surface *ctx, int32_t x, int32_t y, int32_t l, uint32_t c)
{
    if (y < 0 || y >= ctx->height)
        return;

    l = min(l, (int32_t)ctx->width - x - 1);

    uint32_t point = x + y * ctx->width;

    for (uint32_t i = 0; i < l; i++)
    {

        ctx->fb[point] = c;
        point += 1;
    }
}

extern "C" void drawLineUpDown(Surface *ctx, int32_t x, int32_t y, int32_t l, uint32_t c)
{
    if (x < 0 || x >= ctx->width)
        return;

    l = min(l, (int32_t)ctx->height - y - 1);

    uint32_t point = x + y * ctx->width;

    for (uint32_t i = 0; i < l; i++)
    {

        ctx->fb[point] = c;
        point += ctx->width;
    }
}

extern "C" void fillRect(Surface *ctx, int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t c)
{

    x = max(0, x);
    y = max(0, y);

    int32_t x2 = x + (int32_t)w;
    int32_t y2 = y + (int32_t)h;

    x2 = min(x2, (int32_t)ctx->width);
    y2 = min(y2, (int32_t)ctx->height);

    for (int32_t ix = x; ix < x2; ix++)
    {
        for (int32_t iy = y; iy < y2; iy++)
        {
            ctx->fb[ix + (iy * ctx->width)] = c;
        }
    }
};

extern "C" void drawRect(Surface *ctx, int32_t x, int32_t y, uint32_t w, uint32_t h, uint32_t c) // to-optimize
{
    drawLineUpDown(ctx, x, y, h, c);
    drawLineUpDown(ctx, x, y + h - 1, h, c);
    drawLineLeftRight(ctx, x, y, w, c);
    drawLineLeftRight(ctx, x + w - 1, y, w, c);
};

extern "C" void fill(Surface *ctx, uint32_t c)
{
    for (uint32_t i = 0; (int32_t)i < (int32_t)ctx->height * (int32_t)ctx->width; i++)
    {
        ctx->fb[i] = c;
    }
};

// Important
// to-optimize/fix (cut the lines outside)
extern "C" void drawLine(Surface *ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t c)
{
    int32_t dx = x2 - x1;
    int32_t dy = y2 - y1;

    uint32_t w = ctx->width;
    uint32_t h = ctx->height;
    uint32_t *fb = ctx->fb;

    if (dx == 0 && dy == 0)
    {

        if ((uint32_t)x1 >= w || (uint32_t)y1 >= h) // since it's unsgned, negative values get super hight
            return;

        fb[x1 + y1 * w] = c;
        return;
    }

    if (abs(dx) < abs(dy))
    {
        // od ^
        // </* *\>
        if (dy < 0)
        {
            swp(x1, x2);
            swp(y1, y2);
            dx = x2 - x1;
            dy = y2 - y1;
        }

        if (dy == 0)
        {
            drawLineUpDown(ctx, x1, y1, dy, c);
            return;
        }

        for (int32_t i = 0; i < dy; i++)
        {
            float p = ((float)i / (float)dy) * (float)dx;

            uint32_t x = x1 + p;
            uint32_t y = y1 + i;

            // std::cout << x << ":" << y << std::endl;

            if (x >= w || y >= h) // since it's unsgned, negative values get super hight
                continue;

            fb[x + y * w] = c;
        }
    }
    else
    {
        // od ^
        // </* *\>
        if (dx < 0)
        {
            swp(x1, x2);
            swp(y1, y2);
            dx = x2 - x1;
            dy = y2 - y1;
        }

        if (dx == 0)
        {
            drawLineLeftRight(ctx, x1, y1, dx, c);
            return;
        }

        for (int32_t i = 0; i < dx; i++)
        {
            float p = ((float)i / (float)dx) * (float)dy;

            uint32_t x = x1 + i;
            uint32_t y = y1 + p;

            // std::cout << x << ":" << y << std::endl;

            if (x >= w || y >= h) // since it's unsgned, negative values get super hight
                continue;

            fb[x + y * w] = c;
        }
    }
};

extern "C" void drawTriangle(Surface *ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t c)
{
    drawLine(ctx, x1, y1, x2, y2, c);
    drawLine(ctx, x2, y2, x3, y3, c);
    drawLine(ctx, x3, y3, x1, y1, c);
};

// void drawCircle(int32_t x, int32_t y, uint32_t radius, uint32_t c)
// {
//     float len = 0;
//     for (int32_t i = 0; i < radius; i++)
//     {
//         len = sqrt((float(radius) * float(radius)) - (float(i) * float(i)));
//         mirrorDrawPoint(x, y, i, len, c);
//         mirrorDrawPoint(x, y, len, i, c);
//         if (i == len)
//             return;
//     }
// };

// void mirrorDrawPoint(int32_t x, int32_t y, uint32_t ox, uint32_t oy, uint32_t c)
// {
//     drawPoint(x + ox, y + oy, c);
//     drawPoint(x + ox, y - oy, c);
//     drawPoint(x - ox, y - oy, c);
//     drawPoint(x - ox, y + oy, c);
// }

// void fillCircle(int32_t x, int32_t y, uint32_t radius, uint32_t c)
// {
//     drawPoint(x, y, c);

//     float len = 0;
//     for (int32_t i = 1; i < radius; i++)
//     {
//         len = sqrt((float(radius) * float(radius)) - (float(i) * float(i)));
//         for (int32_t j = 1; j < len; j++)
//         {
//             if (i == j)
//                 break;

//             mirrorDrawPoint(x, y, i, j, c);
//             mirrorDrawPoint(x, y, j, i, c);
//         }
//         if (i == len)
//             break;
//     }

//     float skos = sqrt((float(radius) * float(radius)) / 2);

//     for (int32_t i = 1; i < skos; i++)
//     { // skos
//         mirrorDrawPoint(x, y, i, i, c);
//     }

//     for (int32_t i = 1; i < radius; i++)
//     { // pion/poziom
//         drawPoint(x + i, y, c);
//         drawPoint(x - i, y, c);
//         drawPoint(x, y + i, c);
//         drawPoint(x, y - i, c);
//     }
// };

extern "C" void fillTriangle(Surface *ctx, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t c)
{

    if (y1 > y2)
    {
        swp(x1, x2);
        swp(y1, y2);
    }
    if (y2 > y3)
    {
        swp(x2, x3);
        swp(y2, y3);
    }
    if (y1 > y2)
    {
        swp(x1, x2);
        swp(y1, y2);
    }
    // 1<2<3
    float x1ToX2 = float(x2 - x1) / float(y2 - y1);
    float x2ToX3 = float(x3 - x2) / float(y3 - y2);
    float x1ToX3 = float(x3 - x1) / float(y3 - y1);

    bool x1tox2S = true;
    float currentLX = x1;
    float currentSX = x1;
    if (y1 == y2)
        currentSX = x2;

    for (int32_t currentY = y1; currentY <= y3; currentY++)
    {
        if (currentY == y2)
            x1tox2S = false;
        if (currentLX < currentSX)
            drawLineLeftRight(ctx, currentLX, currentY, currentSX - currentLX, c);
        else
            drawLineLeftRight(ctx, currentSX, currentY, currentLX - currentSX, c);
        if (x1tox2S)
            currentSX += x1ToX2;
        else
            currentSX += x2ToX3;
        currentLX += x1ToX3;
    }
};

void drawLetter(Surface *ctx, char ch, int32_t x, int32_t y, int32_t scale, uint32_t c)
{

    uint8_t id = (uint8_t)ch - ' ';

    uint64_t p = 1;

    if(id>=96)
        id = '?'-' ';

    const uint64_t chr = characters[id];

    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (chr & p)
                fillRect(ctx, x + j * scale, y + (7 - i) /*nie chcialo mi się obracać każdy znak w tablicy*/ * scale, scale, scale, c);
            p <<= 1;
        }
    }
};

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

extern "C" void print(Surface *ctx, const char *text, int32_t x, int32_t y, uint32_t scale, uint32_t c)
{
    uint32_t place = 0;
    uint32_t line = 0;
    while (text[place] != '\0')
    {
        if (text[place] == '\n')
        {
            line++;
            continue;
        }
        else
            drawLetter(ctx, text[place], x + 8 * place * scale, y + line * scale * 8, scale, c);
        place++;
    }
};

extern "C" void printNumber(Surface *ctx, int32_t number, int32_t x, int32_t y, uint32_t scale, uint32_t c)
{
    bool negative = false;
    if (number < 0)
    {
        negative = true;
        number = -number;
    }
    uint32_t numlenght = 0;
    int32_t temp = number;
    do
    {
        temp -= temp % 10;
        temp /= 10;
        numlenght++;
    } while (temp != 0);
    numlenght += negative;
    char *txt = new char[numlenght + 1];
    txt[numlenght] = '\0';

    if (negative)
    {
        txt[0] = '-';
    }
    uint32_t itnumlenght = numlenght - 1;
    while (number != 0)
    {
        txt[itnumlenght] = number % 10 + '0';
        number /= 10;
        itnumlenght--;
    }
    print(ctx, txt, x, y, scale, c);
    delete[] txt;
}