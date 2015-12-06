#include "NeoPixelEmulator.h"
#include "stdio.h"

#include <GL/freeglut.h>

NeoPixelEmulator::NeoPixelEmulator(uint16_t numLEDs, uint8_t p, uint8_t t)
    : pixels(numLEDs, 0)
{
}

NeoPixelEmulator::~NeoPixelEmulator()
{
}

void NeoPixelEmulator::begin(void)
{
}

void NeoPixelEmulator::show(void)
{
    //printf("show()\n");
    // Double buffering.
    glutSwapBuffers();
    // Set flag that causes GLUT to call display() in glutMainLoopEvent().
    glutPostRedisplay();
    // GLUT process events, redrew screen.
    glutMainLoopEvent();
}

void NeoPixelEmulator::setPin(uint8_t)
{
}

// Set pixel color from separate R,G,B components:
void NeoPixelEmulator::setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b)
{
    if (n < pixels.size()) {
        setPixelColor(n, Color(r, g, b));
    }
}

// Set pixel color from 'packed' 32-bit RGB color:
void NeoPixelEmulator::setPixelColor(uint16_t n, uint32_t c)
{
    if (n < pixels.size()) {
        pixels[n] = c;
    }
}

// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
uint32_t NeoPixelEmulator::Color(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Query color from previously-set pixel (returns packed 32-bit RGB value)
uint32_t NeoPixelEmulator::getPixelColor(uint16_t n) const
{
    if (n >= pixels.size()) {
        return 0;
    }
    return pixels[n];
}

// Returns pointer to pixels[] array.  Pixel data is stored in device-
// native format and is not translated here.  Application will need to be
// aware whether pixels are RGB vs. GRB and handle colors appropriately.
// *** Interface change: Removed const on function. Don't know how
// the Adafruit implementation was able to return non-const pointer from
// const function there.
uint8_t* NeoPixelEmulator::getPixels(void)
{
    return reinterpret_cast<uint8_t*>(&pixels[0]);
}

uint16_t NeoPixelEmulator::numPixels(void) const
{
    return pixels.size();
}

void NeoPixelEmulator::setBrightness(uint8_t)
{
}

uint8_t NeoPixelEmulator::getBrightness(void) const
{
    return 255;
}

void NeoPixelEmulator::clear()
{
    std::fill(pixels.begin(), pixels.end(), 0);
}
