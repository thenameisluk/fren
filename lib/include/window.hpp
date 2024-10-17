#pragma once

struct Surface
{
    uint32_t width;
    uint32_t height;
    Window window;
    XImage* image;
    Display* display;
    uint32_t* fb;
};