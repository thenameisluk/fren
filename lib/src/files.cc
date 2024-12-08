#include "../include/ctx.hpp"
#include "../include/pureByte.hpp"

symbol* readSymbolFile(const char* filepath){
    symbol* out = new symbol;

    dataArray file = dataArray(std::string(filepath));

    PbView view(file);

    out->width = view.readStatic(32);
    out->height = view.readStatic(32);

    int rlen = out->width*out->height;
    int len = rlen/8;

    if(rlen%8)
        len++;

    dataArray a;
    for(int i = 0;i<len;i++)
        a.push(view.readStatic(8));

    out->data = a.steal();

    return out;

};

void destroySymbol(symbol* s){
    delete s;
};

