#include <iostream>

#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>

#include <stdint.h>

#include "../include/window.hpp"


extern "C" void externUwU() {
    std::cout << "UwU" << std::endl;
}

//can be platform dependent
extern "C" uint32_t getColor(uint8_t r,uint8_t g,uint8_t b){

    return (r<<16) | (g<<8) | b;
}

extern "C" Surface* getWindow(uint32_t width,uint32_t height,const char* name){
    Surface* out = new Surface;
    out->height = height;
    out->width = width;

    out->display = XOpenDisplay(nullptr);

    if (out->display == nullptr) {
        throw std::runtime_error("Could not open display");
    }

    int screen = DefaultScreen(out->display);
    out->window = XCreateWindow(out->display, RootWindow(out->display, screen), 0, 0, width, height, 0, CopyFromParent, InputOutput, CopyFromParent, 0, nullptr);

    //non resizable
    unsigned int borderWidth;
    Window rootWindow;
    int x, y;
    uint32_t depth;
    XGetGeometry(out->display, out->window, &rootWindow, &x, &y, &width, &height, &borderWidth, &depth);
    
    XSizeHints sizeHints;
    sizeHints.flags = PMinSize | PMaxSize;
    sizeHints.min_width = sizeHints.max_width = width + 2 * borderWidth;
    sizeHints.min_height = sizeHints.max_height = height + 2 * borderWidth;
    XSetWMNormalHints(out->display, out->window, &sizeHints);

    //close prevention
    Atom wmDeleteMessage = XInternAtom(out->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(out->display, out->window, &wmDeleteMessage, 1);

    if (out->window == None) {
        XCloseDisplay(out->display);
        throw std::runtime_error("Could not create window");
    }

    XStoreName(out->display, out->window, name);
    XSelectInput(out->display, out->window, StructureNotifyMask | ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);
    XMapWindow(out->display, out->window);

    //wait till window map
    XEvent eve;
    do {
        XNextEvent(out->display, &eve);
    } while (eve.type != MapNotify || eve.xmap.event != out->window);

    //graphic context stuff
    out->fb = new uint32_t[width*height];

    out->image = XCreateImage(out->display, DefaultVisual(out->display, screen), 24, ZPixmap, 0, (char *)out->fb, width, height, 8, 0);

    return out;
}

//after running this command the pointer can't be used anymore
extern "C" void destroyWindow(Surface* window){
    XDestroyWindow(window->display, window->window);

    XDestroyImage(window->image);
    
    XCloseDisplay(window->display);

    delete [] window->fb;

    window->fb = nullptr;

    delete window;
}

extern "C" void drawFrame(Surface* window){
    GC gc = XCreateGC(window->display, window->window, 0, nullptr);
    
    XPutImage(window->display, window->window, gc, window->image, 0, 0, 0, 0, window->width, window->height);
    XFlush(window->display);

    XFreeGC(window->display, gc);
}

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

Event nextEvent(Surface* window){

    if(XPending(window->display) < 1)
        return {none};

    XEvent event;
    Event out;
    XNextEvent(window->display, &event);
    switch (event.type) {
        case KeyPress:{
            char key = XkbKeycodeToKeysym(window->display, event.xkey.keycode, 0, 0);
            
            out.type = KeyDown;
            out.data.key = key;
            return out;
        }
        case KeyRelease:{
            char key = XkbKeycodeToKeysym(window->display, event.xkey.keycode, 0, 0);
            
            out.type = KeyUp;
            out.data.key = key;
            return out;
        }
        case ButtonPress: {
            //event.xbutton.button 1 - left,2 - middle, 3 - right
            out.type = MouseDown;
            out.data.pos.x = event.xbutton.x;
            out.data.pos.y = event.xbutton.y;
            return out;
        }
        case ButtonRelease: {
            out.type = MouseUp;
            out.data.pos.x = event.xbutton.x;
            out.data.pos.y = event.xbutton.y;
            return out;
        }
        case MotionNotify: {
            out.type = MouseMove;
            out.data.pos.x = event.xmotion.x;
            out.data.pos.y = event.xmotion.y;
            return out;
        }
        case ClientMessage:
            if (event.xclient.message_type == XInternAtom(window->display, "WM_PROTOCOLS", True)
                && (Atom)event.xclient.data.l[0] == XInternAtom(window->display, "WM_DELETE_WINDOW", False)) {
                    out.type = close;
                return out;
            }
    }
    return {none};
}

extern "C" Event* getEvent(Surface* window){
    return new Event(nextEvent(window));
}

extern "C" uint8_t getEventType(Event* event){
    return event->type;
}

extern "C" char getEventKey(Event* event){
    return event->data.key;
}

extern "C" int32_t getEventX(Event* event){
    return event->data.pos.x;
}

extern "C" int32_t getEventY(Event* event){
    return event->data.pos.y;
}

extern "C" void destroyEvent(Event* event){
    delete event;
}

