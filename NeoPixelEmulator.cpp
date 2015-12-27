#include "NeoPixelEmulator.h"
#include "stdio.h"

#define M_PI 3.14159265358979323846

NeoPixelEmulator::NeoPixelEmulator(uint16_t numLEDs, uint8_t p, uint8_t t)
    : pixels(numLEDs, 0)
{
}

NeoPixelEmulator::~NeoPixelEmulator()
{
}

void NeoPixelEmulator::setPixelLayout(PixelLayout pixelLayout) {
    _pixelLayout = pixelLayout;
}

void NeoPixelEmulator::begin(void)
{
}

void NeoPixelEmulator::show(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    switch (_pixelLayout) {
    case Strip:
        drawLedStrip(500, 500, numPixels(), 15, 10);
        break;
    case Ring:
        drawLedRing(500, 500, numPixels(), 50, 50);
        break;
    case Grid:
        int s = sqrt(numPixels());
        drawLedGrid(500, 500, s, s, 80, 50);
        break;
    }
    // Double buffering.
    glutSwapBuffers();
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

//
// OpenGL.
//

void NeoPixelEmulator::drawLedStrip(GLfloat xCenter, GLfloat yCenter, int numLeds, GLfloat space, GLfloat ledRadius)
{
    for (int x = 0; x < numLeds; ++x) {
        uint32_t c = pixels[x];
        uint8_t R, G, B;
        colorPackedToScalar(&R, &G, &B, c);
        drawFilledCircle(xCenter - ((numLeds - 1) * space / 2.0f) + (x) * space,
                         yCenter,
                         ledRadius, R, G, B);
    }
}

void NeoPixelEmulator::drawLedRing(GLfloat xCenter, GLfloat yCenter, int numLeds, GLfloat space, GLfloat ledRadius)
{
    GLfloat circleRadius = numLeds * (space + ledRadius) / (2.0 * M_PI);
    for (int i = 0; i < numLeds; ++i) {
        uint32_t c = pixels[i];
        uint8_t R, G, B;
        colorPackedToScalar(&R, &G, &B, c);
        drawFilledCircle(xCenter + (circleRadius * cos(i * 2.0f * M_PI / numLeds)),
                         yCenter + (circleRadius * sin(i * 2.0f * M_PI / numLeds)),
                         ledRadius, R, G, B);
    }
}

// Draw LED grid where the LEDs are ordered in a continuous, back-and-forth sequence.
void NeoPixelEmulator::drawLedGrid(GLfloat xCenter, GLfloat yCenter, int numLedsX, int numLedsY, GLfloat space, GLfloat ledRadius)
{
    for (int y = 0; y < numLedsY; ++y) {
        for (int x = 0; x < numLedsX; ++x) {
            uint32_t c;
            if (y & 1) {
                c = pixels[x + y * numLedsX];
            }
            else {
                c = pixels[numLedsX - x - 1 + y * numLedsX];
            }
            uint8_t R, G, B;
            colorPackedToScalar(&R, &G, &B, c);
            drawFilledCircle(xCenter - ((numLedsX - 1) * space / 2.0f) + (x) * space,
                             yCenter - ((numLedsY - 1) * space / 2.0f) + (y) * space,
                             ledRadius, R, G, B);
        }
    }
}

void NeoPixelEmulator::drawFilledCircle(GLfloat x, GLfloat y, GLfloat r, u8 R, u8 G, u8 B)
{
    glColor3ub(R, G, B);
    glPointSize(r);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// When using AA with this method, I get some undrawn pixels radiating out from
// the center. I'd like to find out why.
void NeoPixelEmulator::__drawFilledCircle(GLfloat x, GLfloat y, GLfloat r)
{
    int numTriangles = 30;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= numTriangles; ++i) {
        glVertex2f(x + (r * cos(i * 2.0f * M_PI / numTriangles)),
                   y + (r * sin(i * 2.0f * M_PI / numTriangles)));
    }
    glEnd();
}

void NeoPixelEmulator::colorPackedToScalar(uint8_t* R, uint8_t* G, uint8_t* B, uint32_t color) {
    *B = color;
    color >>= 8;
    *G = color;
    color >>= 8;
    *R = color;
}
