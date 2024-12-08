#!/bin/bash

g++ lib/src/x11.cc lib/src/ctx.cc lib/src/pureByte.cc lib/utils/symbol-maker.cc lib/src/files.cc -lX11 -o symbol-maker