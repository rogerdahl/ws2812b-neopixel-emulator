#include <Adafruit_NeoPixel.h>
#include <inttypes.h>

#define PIN 1
#define N_PIXELS 24

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s16 int16_t

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(N_PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// must be below my type defines and the pixels setup.
#ifndef Arduino_h
#include "rgb_sketch.hpp"
#include <stdio.h>
#endif


void setup()
{
    pixels.begin();
    pixels.setBrightness(50);
    pixels.show();
}

void loop()
{
    int runSeconds = 20;
    xmasRedGreenTwinkles(runSeconds);
    clear(pixels.Color(0, 0, 0), 75);
    halloweenRunners(8, 10, 9, 30);
//    halloweenRunners(8, 10, 7, 30);
    halloweenRunners(8, 10, 5, 30);
//    halloweenRunners(8, 10, 3, 30);
    halloweenRunners(8, 10, 1, 30);
    clear(pixels.Color(0, 0, 0), 75);
    // even, short
    smoothRunners(runSeconds, 20,
                  60, 60, 60,
                  3, 3, 3,
                  0, 8 * 256, 16 * 256);
    clear(pixels.Color(0, 0, 0), 75);
    // even, long, bright, reverse
    smoothRunners(runSeconds, 20,
                  60, 60, -60,
                  25, 25, 25,
                  0, 8 * 256, 16 * 256);
    clear(pixels.Color(0, 0, 0), 75);
    // even, long, darker, reverse
    smoothRunners(runSeconds, 20,
                  60, 60, -60,
                  11, 11, 11,
                  0, 8 * 256, 16 * 256);
    clear(pixels.Color(0, 0, 0), 75);
    // uneven, short
    smoothRunners(runSeconds, 20,
                  60, 65, 70,
                  7, 7, 7,
                  0, 8 * 256, 16 * 256);
    // uneven, short, reverse
    smoothRunners(runSeconds, 20,
                  60, 80, -100,
                  7, 7, 7,
                  0, 8 * 256, 16 * 256);
    clear(pixels.Color(0, 0, 0), 75);
    // uneven, long
    smoothRunners(runSeconds, 20,
                  40, 41, 42,
                  15, 15, 15,
                  0, 8 * 256, 16 * 256);
    clear(pixels.Color(0, 0, 0), 75);
    // uneven, very long, reverse
    smoothRunners(runSeconds, 20,
                  40, -41, 42,
                  21, 21, 21,
                  0, 8 * 256, 16 * 256);
    clear(pixels.Color(0, 0, 0), 75);
    // shimmer 1
    smoothRunners(runSeconds, 1,
                  123, 456, -789,
                  9, 9, 9,
                  0, 8 * 256, 16 * 256);
    // shimmer 2
    smoothRunners(runSeconds, 1,
                  1000, 2000, 3000,
                  9, 9, 9,
                  0, 8 * 256, 16 * 256);
    clear(pixels.Color(0, 0, 0), 75);
    delay(1000);
    clear(pixels.Color(255, 0, 0), 75);
    delay(1000);
    clear(pixels.Color(255, 255, 0), 75);
    delay(1000);
    clear(pixels.Color(0, 255, 0), 75);
    delay(1000);
    clear(pixels.Color(0, 255, 255), 75);
    delay(1000);
    clear(pixels.Color(0, 0, 255), 75);
    delay(1000);
    clear(pixels.Color(255, 0, 255), 75);
    delay(1000);
    clear(pixels.Color(255, 255, 255), 75);
    delay(1000);
    clear(pixels.Color(0, 0, 0), 75);
}

void smoothRunners(u16 run_s, u16 delay_ms,
                   s16 r_add, s16 g_add, s16 b_add,
                   u8 r_len, u8 g_len, u8 b_len,
                   u16 r_offset, u16 g_offset, u16 b_offset)
{
    u16 pos_r = r_offset;
    u16 pos_g = g_offset;
    u16 pos_b = b_offset;
    u8 brightnessArray[32]; // TODO: Artificial limit
    u16 pix256 = 256 * (pixels.numPixels());
    u32 start_ms = millis();
    while (millis() < start_ms + (run_s * 1000)) {
        pos_r = wrap_add(pos_r, r_add, pix256);
        pos_g = wrap_add(pos_g, g_add, pix256);
        pos_b = wrap_add(pos_b, b_add, pix256);
        clear(0, 0);
        genTaperedSegment(brightnessArray, r_len, 255);
        drawTaperedSegment(pos_r, 8, r_len, brightnessArray);
        genTaperedSegment(brightnessArray, g_len, 255);
        drawTaperedSegment(pos_g, 16, g_len, brightnessArray);
        genTaperedSegment(brightnessArray, b_len, 255);
        drawTaperedSegment(pos_b, 0, b_len, brightnessArray);
        pixels.show();
        delay(delay_ms);
    }
}

void halloweenRunners(u16 run_s, u16 delay_ms, u8 segLen, u8 speed)
{
    u16 pos1 = 0;
    u16 pos2 = 8 * 256;
    u16 pos3 = 16 * 256;
    // orange: 255,165,0
    u8 brightnessR[32]; // TODO: Artificial limit
    genTaperedSegment(brightnessR, segLen, 255);
    u8 brightnessG[32]; // TODO: Artificial limit
    genTaperedSegment(brightnessG, segLen, 165);
    u8 brightnessB[32]; // TODO: Artificial limit
    genTaperedSegment(brightnessB, segLen, 0);
    u16 pix256 = 256 * (pixels.numPixels());
    u32 start_ms = millis();
    while (millis() < start_ms + (run_s * 1000)) {
        pos1 = wrap_add(pos1, speed, pix256);
        pos2 = wrap_add(pos2, speed, pix256);
        pos3 = wrap_add(pos3, speed, pix256);
        clear(0, 0);
        drawTaperedSegment(pos1, 8, segLen, brightnessR);
        drawTaperedSegment(pos1, 16, segLen, brightnessG);
        drawTaperedSegment(pos1, 0, segLen, brightnessB);
        drawTaperedSegment(pos2, 8, segLen, brightnessR);
        drawTaperedSegment(pos2, 16, segLen, brightnessG);
        drawTaperedSegment(pos2, 0, segLen, brightnessB);
        drawTaperedSegment(pos3, 8, segLen, brightnessR);
        drawTaperedSegment(pos3, 16, segLen, brightnessG);
        drawTaperedSegment(pos3, 0, segLen, brightnessB);
        pixels.show();
        delay(delay_ms);
    }
}

// Example for 7 pixels.
//
//        X
//       X X
//      X   X
//     X     X
//
// pixel 3 is center, 255
// There are 4 pixels on each side, sharing the center pixel
// The values of the 4 pixels are assigned in such a way that an imagined 5th pixel on each side is 0.
// So, for 4 pixels:
// step = 255 / 4 = 63
// So, steps for 7 pixels: 64, 127, 191, 255, 191, 127, 64
// Note: Needs segmentLength + 2 bytes for "run off" on the ends.
void genTaperedSegment(u8* brightnessArray, u8 segmentLength, u8 brightestVal)
{
    u8 centerPos = segmentLength / 2;
    u8 stepVal = brightestVal / (centerPos + 1);
    brightnessArray[0] = 0;
    for (u8 i = 0; i < segmentLength; ++i) {
        if (i <= centerPos) {
            brightnessArray[i + 1] = stepVal * (i + 1);
        }
        else {
            brightnessArray[i + 1] = stepVal * (segmentLength - i);
        }
    }
    brightnessArray[segmentLength + 1] = 0;
}

void drawTaperedSegment(u16 highRezPos, u8 colorSelect, u8 segmentLength, u8* brightnessArray)
{
    u8 shiftPos = highRezPos & 0xff;
    u8 pixelPos = highRezPos >> 8;
    for (u8 i = 0; i <= segmentLength; ++i) {
        u8 brightness = WeightAvg(brightnessArray[i], brightnessArray[i + 1], 255 - shiftPos);
        addPixelColor(pixelPos, brightness, colorSelect);
        pixelPos = wrap_add(pixelPos, 1, pixels.numPixels() - 1);
    }
}

u8 WeightAvg(u8 a, u8 b, u8 weight)
{
    u16 aa = a * (256 - weight);
    u16 bb = b * weight;
    return (aa + bb) >> 8;
}

void addPixelColor(u16 pixelPos, u8 brightness, u8 colorSelect)
{
    u32 packedColor = pixels.getPixelColor(pixelPos);
    u32 packedColorAdded = addColor(packedColor, brightness, colorSelect);
    pixels.setPixelColor(pixelPos, packedColorAdded);
}

u32 addColor(u32 color, u8 v, u8 i)
{
    u32 c1 = ror(color, i);
    u16 c2 = c1 & 0xffUL;
    c2 += v;
    if (c2 > 255) {
        c2 = 255;
    }
    c1 &= 0xffffff00UL;
    c1 |= c2;
    c1 = rol(c1, i);
    return c1;
}

void clear(u32 c, u8 delay_ms)
{
    for (u16 i = 0; i < pixels.numPixels(); ++i) {
        pixels.setPixelColor(i, c);
        if (delay_ms) {
            pixels.show();
            delay(delay_ms);
        }
    }
}

void xmasRedGreenTwinkles(u16 run_s)
{
    u8 flash_on = 20;
    u8 flash_pause = 150;
    u8 twinkles_per_swap = 3;
    u16 p = 0;
    u16 p_cnt = 0;
    u32 start_ms = millis();
    while (millis() < start_ms + (run_s * 1000)) {
        u8 twinkle_i = random(0, pixels.numPixels() - 1);
        pixels.setPixelColor(twinkle_i, pixels.Color(255, 255, 255));
        pixels.show();
        delay(flash_on);
        for (u8 i = 0; i < pixels.numPixels(); ++i) {
            u32 c = (i + p) & 1 ? pixels.Color(255, 0, 0) : pixels.Color(0, 255, 0);
            pixels.setPixelColor(i, c);
        }
        pixels.show();
        delay(flash_pause);
        if (++p_cnt == twinkles_per_swap) {
            p_cnt = 0;
            p += 1;
        }
    }
}

u32 rol(u32 v, u8 p)
{
    return (v << p) | (v >> (32 - p));
}

u32 ror(u32 v, u8 p)
{
    return (v >> p) | (v << 32 - p);
}

int wrap_numpixels(int p)
{
    return wrap(p, pixels.numPixels());
}

int wrap_16pix(int p)
{
    return wrap(p, 16 * pixels.numPixels());
}

int wrap(int p, int w)
{
    if (p < 0) {
        return p + w;
    }
    else if (p >= w) {
        return p - w;
    }
    else {
        return p;
    }
}

u16 wrap_add(s16 v, s16 add_v, s16 max_v)
{
    s16 t = v + add_v;
    if (t > max_v) {
        return t - max_v - 1;
    }
    else if (t < 0) {
        return max_v + t + 1;
    }
    else {
        return t;
    }
}

