#!/bin/sh

gcc -shared -o ../libsdl_harfbuzz_ext.so -fPIC -std=c++11 \
  -I/usr/include/freetype2 \
  sdl_harfbuzz_ext.cpp \
  -lharfbuzz -lfreetype -lSDL2 -lSDL2main -lstdc++
