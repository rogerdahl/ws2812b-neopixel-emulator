#include <inttypes.h>
#include <vector>

#ifndef NEOPIXEL_EMULATOR_H
#define NEOPIXEL_EMULATOR_H

// We ignore all these but define them so that client code doesn't break.
#define NEO_RGB     0x00
#define NEO_GRB     0x00
#define NEO_BRG     0x00
#define NEO_COLMASK 0x00
#define NEO_KHZ800  0x00
#define NEO_KHZ400  0x00
#define NEO_SPDMASK 0x00

class NeoPixelEmulator
{
public:
    // Constructor: number of LEDs, pin number, LED type
    NeoPixelEmulator(uint16_t numPixels, uint8_t pinNumber=0, uint8_t t=NEO_GRB);
    ~NeoPixelEmulator();

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
    std::vector<uint32_t> pixels;
};

#endif
