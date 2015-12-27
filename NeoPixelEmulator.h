#ifndef NEOPIXEL_EMULATOR_H
#define NEOPIXEL_EMULATOR_H

#include <inttypes.h>
#include <math.h>
#include <vector>

#include <GL/freeglut.h>

// We ignore all these but define them so that client code doesn't break.
#define NEO_RGB     0x00
#define NEO_GRB     0x00
#define NEO_BRG     0x00
#define NEO_COLMASK 0x00
#define NEO_KHZ800  0x00
#define NEO_KHZ400  0x00
#define NEO_SPDMASK 0x00

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s16 int16_t

enum PixelLayout {
    Strip,
    Ring,
    Grid,
};

class NeoPixelEmulator
{
public:
    // Constructor: number of pixels, pin number, pixel type
    NeoPixelEmulator(uint16_t numPixels, uint8_t pinNumber=0, uint8_t t=NEO_GRB);
    ~NeoPixelEmulator();

    void setPixelLayout(PixelLayout);

    void begin(void);
    void show(void);
    void setPin(uint8_t p);
    void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
    void setPixelColor(uint16_t n, uint32_t c);
    void setBrightness(uint8_t);
    void clear();

    uint8_t* getPixels(void);
    uint8_t getBrightness(void) const;
    uint16_t numPixels(void) const;
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b);
    uint32_t getPixelColor(uint16_t n) const;
    inline bool canShow(void) {
        return true;
    }

private:
    void drawLedStrip(float xCenter, float yCenter, int numLeds, float space, float ledRadius);
    void drawLedRing(float x, float y, int numLeds, float circleRadius, float ledRadius);
    void drawLedGrid(float xCenter, float yCenter, int numLedsX, int numLedsY, float space, float ledRadius);
    void drawFilledCircle(GLfloat x, GLfloat y, GLfloat r, u8 R, u8 G, u8 B);
    void __drawFilledCircle(GLfloat x, GLfloat y, GLfloat r);
    void colorPackedToScalar(uint8_t* R, uint8_t* G, uint8_t* B, uint32_t color);

    std::vector<uint32_t> pixels;
    PixelLayout _pixelLayout;
};

#endif
