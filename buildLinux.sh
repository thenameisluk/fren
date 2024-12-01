#!/bin/bash

#linux
g++ -o2 -o "libctx-$(uname -m).so" --share -fPIC lib/src/ctx.cc
g++ -o2 -o "libfren-lfb-$(uname -m).so" --share -fPIC lib/src/lfb.cc
g++ -o2 -o "libfren-x11-$(uname -m).so" --share -fPIC lib/src/x11.cc -lX11 
#windows
#will likely not have fb version
