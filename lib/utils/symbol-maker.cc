#include <iostream>

#include "../include/x11.hpp"
#include "../include/ctx.hpp"
#include "../include/pureByte.hpp"
#include "../include/files.hpp"

bool* data;

symbol* s;

int rx = -1;
int ry = -1;

bool mouseDown = false;

void genSymbol(){
    PbWriter write;
    for(int i = 0;i<s->width*s->height;i++){
        write.writeBit(data[i]);
    }
    delete [] s->data;
    s->data = write.exportData().steal();
}

void HandleMouse(Event* e){
    if(!mouseDown)
        return;

    int rxt = e->data.pos.x/10;
    int ryt = e->data.pos.y/10;
    if(rxt==rx&&ryt==ry){
        return;
    }
    // std::cout << rxt<< ":" << ryt << std::endl;//for debugging
    rx = rxt;
    ry = ryt;

    data[rx + ry * s->width] = !data[rx + ry * s->width];

    genSymbol();
}

void frame(Surface* window,context* ctx){
    fill(ctx,getColor(0,0,0));
    drawSymbol(ctx,s,0,0,10,getColor(255,255,255));
    drawFrame(window);
}

int main(){
    std::cout << "file to open (blank for new file)> ";

    std::string fname;
    std::getline(std::cin,fname);

    if(fname==""){
        s = new symbol;
        std::cout << "new file width > ";
        std::cin >> s->width;
        std::cout << "new file hidth > ";
        std::cin >> s->height;

        data = new bool[s->width*s->height];
        s->data = nullptr;
    }else{
        s = readSymbolFile(fname.c_str());
        PbView view(s->data);

        data = new bool[s->width*s->height];

        for(int i = 0;i<s->width*s->height;i++){
            data[i] = view.readBit();
        }
    }
    

    genSymbol();

    auto window = getWindow(s->width*10,s->height*10,"symbol maker");

    auto ctx = getWindowctx(window);
    frame(window,ctx);

    while(true){
        Event* e = getEvent(window);

        

        if(e->type == eventType::MouseDown){
            mouseDown = true;
            HandleMouse(e);
            frame(window,ctx);
        }
        if(e->type == eventType::MouseMove){
            HandleMouse(e);
            frame(window,ctx);
        }
        if(e->type == eventType::MouseUp){
            mouseDown = false;
            rx = -1;
            ry = -1;
        }
        if(e->type == eventType::close){
            break;
        }

        destroyEvent(e);
    }

    std::cout << "path to save > ";

    std::string name;
    std::cin >> name;

    if(name=="")
        return 0;

    PbWriter file;
    file.writeStatic(s->width,32);
    file.writeStatic(s->height,32);

    int rlen = s->width*s->height;
    int len = rlen/8;

    if(rlen%8)
        len++;
    
    for(int i = 0;i<len;i++){
        file.writeStatic(s->data[i],8);
    }

    file.exportData().save(name);
}