#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <cstring>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <stdint.h>

#include "../include/ctx.hpp"

struct linuxFB
{
    int fbfd;
    bool rotated;
    uint32_t width;
    uint32_t height;
    uint32_t *buffer;
    context *ctx;
    uint32_t fblen;
};

extern "C" void externUwU()
{
    printf("C++ uwu");
}

extern "C" linuxFB *getFB()
{
    linuxFB *s = new linuxFB;
    struct fb_var_screeninfo vinfo;

    // Open the file for reading and writing
    s->fbfd = open("/dev/fb0", O_RDWR);
    if (s->fbfd == -1)
    {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get variable screen information
    if (ioctl(s->fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1)
    {
        perror("Error reading variable information");
        exit(3);
    }

    printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    s->width = vinfo.xres;
    s->height = vinfo.yres;
    if (s->height > s->width)
    {
        // for whatever dumb reason screen on my device is rotated
        printf("Note. fixed up screen rotations");
        s->width = vinfo.yres;
        s->height = vinfo.xres;
        s->rotated = true;
    }

    s->fblen = s->width * s->height * 4;

    // Map the device to memory
    s->buffer = (uint32_t *)mmap(0, s->fblen, PROT_READ | PROT_WRITE, MAP_SHARED, s->fbfd, 0);

    s->ctx = new context;
    s->ctx->data = s->buffer;
    s->ctx->width = s->height;
    s->ctx->height = s->width;

    if (vinfo.bits_per_pixel != 32)
    {
        perror("sorry the device doesn't suppoer 32 bit color depth");
        exit(5);
    }

    return s;
}

extern "C" context *getFBctx(linuxFB *s)
{
    return s->ctx;
}

extern "C" void destroyFB(linuxFB *s)
{
    munmap(s->buffer, s->fblen);
    close(s->fbfd);
    delete s;
}

// test purposes
//  int main(){
//      linuxFB* s = getWindow();

//     while (true)
//     {
//         uint32_t col = getColor(255,0,0);
//         for(int i = 0;i<s->width*s->height;i++){
//             s->ctx[i] = col;
//         }
//         drawFrame(s);
//     }

// }