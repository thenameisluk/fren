#pragma once

#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>

#include <stdint.h>
struct Surface
{
    uint32_t width;
    uint32_t height;
    Window window;
    XImage* image;
    Display* display;
    uint32_t* fb;
};