#!/bin/sh

./makeheaders rgb_sketch.cpp

g++ -o emulator rgb_sketch.cpp main.cpp NeoPixelEmulator.cpp Arduino.cpp -I. -lm -lglut -lGL -lGLU -include Arduino.h
# -include rgb_sketch.hpp
