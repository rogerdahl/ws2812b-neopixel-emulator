#### Adafruit NeoPixel Emulator

<img align="right" width="50%" src="./screenshot.png">

This is a tool to speed up development of animated patterns for [WS2812B](https://www.adafruit.com/datasheets/WS2812B.pdf) RGB LEDs that are supported by the [Adafruit NeoPixel](https://www.adafruit.com/category/168) library for Arduino. It consists of a library that has the same interface as the NeoPixel library but that, instead of writing to actual WS2812B LEDs, renders the LEDs on screen using OpenGL. In addition, there's simple adapter code and implementations of a couple of the most common functions used in Arduino sketches (`delay()`, `random()` and `millis()`).

This allows an Arduino sketch that uses only the Adafruit NeoPixel library and the supported functions to be compiled, linked and run on the PC, enabling a shorter development cycle and easy debugging for WS2812B blinkenlight projects.

After implementing the desired effects on the PC, the sketch can be copied unchanged to the Arduino IDE for programming one of the Atmel microcontrollers supported by the Adafruit NeoPixel library.

Currently, only rendering of Adafruit NeoPixel Rings, like the [24 LED Ring](https://www.adafruit.com/products/1586) has been implemented, with ring and LED diameters set to look somewhat like that particular product.

#### Setup and Use

As Douglas Adams might have said, getting things up and running with this app is almost, but not quite, entirely unlike getting things running on an Arduino. No part of the Arduino IDE or libraries are used in this project. It's just a regular PC app written in C++ and based on FreeGLUT that has been set up in such a way that one of the `.cpp` files can also be used as an Arduino sketch. The app should compile and run on any platform where FreeGLUT is available, such as Linux, Mac and Windows.     

This was used for developing some NeoPixel patterns for a DigiSpark ATtiny85. The DigiSpark is a convenient platform for running battery powered blinky lights but is not so convenient for development as it must be unplugged and plugged back into the USB port each time the code is updated (which can easily be hundreds of times when tweaking parameters for animated effects, etc). Hence this small app. 

These instructions should work on Ubuntu, Mint and other Debian based systems. Tested on Linux Mint 17.2 64-bit.

##### makeheaders

The main difference between an Arduino sketch and a regular .cpp file is that sketches have automatically generated prototypes. We use the [makeheaders](http://www.hwaci.com/sw/mkhdr/makeheaders.html) for this task.
 
Set up makeheaders:

    $ wget http://www.hwaci.com/sw/mkhdr/makeheaders.c
    $ gcc -o makeheaders makeheaders.c

##### freeGLUT

    $ sudo apt-get install freeglut3-dev

##### OpenGL

You also need OpenGL drivers. These are specific to your graphics card and there's a good chance you already have them. If they appear to be missing, it's worth a try to set up the Mesa drivers:

    $ sudo apt-get install mesa-common-dev (*install these only if you need them*)

##### Compiler and stuff

    $ sudo apt-get install build-essential

##### source

Grab this code directly via `git`. `cd` to the directory, then:

    $ make.sh && ./emulator
    
* Watch the blinkies on screen. Then exit by closing the window or hitting Ctrl-C in the shell.

* Tweak rgb_sketch.cpp to make your own patterns.

* Debug with a regular debugger or use `printf()` statements (the output appears in the shell).

* When done, copy paste the rgb_sketch.cpp code into the Arduino IDE and write it to your device.

