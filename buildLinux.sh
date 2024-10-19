#!/bin/bash

g++ --share -fPIC lib/src/ctx.cc lib/src/windowLinux.cc -lX11 -o "libfren-$(uname -m).so"
