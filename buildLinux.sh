#!/bin/bash

#linux
g++ -o3 -o "libctx-flip-$(uname -m).so" -shared -fPIC lib/src/ctx-flip.cc
g++ -o3 -o "libctx-$(uname -m).so" -shared -fPIC lib/src/ctx.cc
g++ -o3 -o "libfren-lfb-$(uname -m).so" -shared -fPIC lib/src/lfb.cc
g++ -o3 -o "libfren-x11-$(uname -m).so" -shared -fPIC lib/src/x11.cc -lX11 
#windows
#will likely not have fb version
