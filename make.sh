#!/bin/sh

SKETCH=arduino_sketch
#SKETCH = arduino_sketch_2

./makeheaders ${SKETCH}.cpp

g++ -o emulator ${SKETCH}.cpp main.cpp NeoPixelEmulator.cpp Arduino.cpp -I. -lm -lglut -lGL -lGLU -include Arduino.h -std=c++11
# -fstack-protector-all

