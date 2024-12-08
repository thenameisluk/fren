#pragma once
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>

#include <stdint.h>

#include "./ctx.hpp"

struct Surface
{
    uint32_t width;
    uint32_t height;
    Window window;
    XImage* image;
    Display* display;
    context ctx;
};


extern "C" void externUwU();

extern "C" Surface* getWindow(uint32_t width,uint32_t height,const char* name);

extern "C" context* getWindowctx(Surface* window);

//after running this command the pointer can't be used anymore
extern "C" void destroyWindow(Surface* window);
extern "C" void drawFrame(Surface* window);

enum eventType: uint8_t{
    none = 0,
    MouseDown = 1,
    MouseUp = 2,
    MouseMove = 3,
    KeyDown = 4,
    KeyUp = 5,
    close = 6
};

struct eventPos{
    int32_t x;
    int32_t y;
};
union eventDate{
    char key;
    eventPos pos;
};

struct Event
{
    eventType type;
    eventDate data;
};

Event nextEvent(Surface* window);

extern "C" Event* getEvent(Surface* window);

extern "C" uint8_t getEventType(Event* event);
extern "C" char getEventKey(Event* event);
extern "C" int32_t getEventX(Event* event);

extern "C" int32_t getEventY(Event* event);

extern "C" void destroyEvent(Event* event);

