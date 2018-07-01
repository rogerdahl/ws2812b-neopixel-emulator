#include "Adafruit_NeoPixel.h"
#include <inttypes.h>

#define NEOPIXEL_PIN 1

// We use "pixel" to refer to a single WS2812B package, which contains three
// LEDs (red, green and blue).

// Select number of pixels.
#define NUM_PIXELS 60

// We copy some type name defines here to keep the sketch self contained.
#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define s16 int16_t

// Create the NeoPixel driver object. On the PC, this becomes the emulator.
Adafruit_NeoPixel pixels =
  Adafruit_NeoPixel(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// This must be below the short int type names and the NeoPixel library init.
#ifndef Arduino_h
#include "arduino_sketch_2.hpp"
// When running on the PC, we include stdio.h for printf() debugging.
#include <stdio.h>
#endif

// End of boilerplate.

void setup()
{
// Arduino_h is only defined when compiling the sketch in the Arduino IDE.
#ifndef Arduino_h
  // Select line, circle or grid pixel layout for emulator.
  pixels.setPixelLayout(Strip);
// pixels.setPixelLayout(Ring);
// pixels.setPixelLayout(Grid);
#endif
  pixels.begin();
  pixels.setBrightness(50);
  pixels.show();
}

struct Segment
{
  u32 color;
  s16 speed;
  u16 superPos;
  u8 numSegmentPixels;
};

void loop()
{
  int runSec = 60;
  // runSec, delayMs, numMeteors, minPixels, maxPixels, minSpeed, maxSpeed
  meteors(runSec, 20, 20, 2, 4, 50, 150);
  meteors(runSec, 20, 10, 2, 50, 50, 150);
  meteors(runSec, 20, 10, 2, 10, 50, 150);
}

void meteors(
  u16 runSec, u16 delayMs, u8 numMeteors, u8 minPixels, u8 maxPixels,
  s16 minSpeed, s16 maxSpeed)
{
  Segment segmentArr[numMeteors];
  for (u8 i = 0; i < numMeteors; ++i) {
    segmentArr[i].superPos = 0xffff;
  }
  u16 maxSuperPosition = (pixels.numPixels() + maxPixels) << 8;
  u32 startMs = millis();
  while (millis() < startMs + (runSec * 1000UL)) {
    clear();
    for (u8 i = 0; i < numMeteors; ++i) {
      if (segmentArr[i].superPos >= maxSuperPosition) {
        segmentArr[i].color = random(0, 0xffffff);
        segmentArr[i].speed = random(minSpeed, maxSpeed);
        segmentArr[i].superPos = 0;
        segmentArr[i].numSegmentPixels = random(minPixels, maxPixels);
      }
      drawTaperedSegment(
        segmentArr[i].superPos, segmentArr[i].numSegmentPixels,
        segmentArr[i].color, maxPixels);
      segmentArr[i].superPos += segmentArr[i].speed;
    }
    pixels.show();
    delay(delayMs);
  }
}

void drawTaperedSegment(
  u16 superPos, u8 numSegmentPixels, u32 color, u8 numEnterExitPixels)
{
  u8 shiftPos = superPos & 0xff;
  u8 pixelPos = superPos >> 8;
  for (u8 i = 0; i <= numSegmentPixels; ++i) {
    u8 drawPos = pixelPos + i;
    if (
      drawPos < numEnterExitPixels
      || drawPos >= pixels.numPixels() + numEnterExitPixels) {
      continue;
    }
    u32 color1 = calcTailSegmentPixel(numSegmentPixels, i, color);
    u32 color2 = calcTailSegmentPixel(numSegmentPixels, i + 1, color);
    u32 avgColor = colorWeightedAvg(color1, color2, 255 - shiftPos);
    addPixelColor(drawPos - numEnterExitPixels, avgColor);
  }
}

u32 calcTailSegmentPixel(u8 numSegmentPixels, u8 pos, u32 startColor)
{
  if (pos == 0 || pos == numSegmentPixels + 1) {
    return 0x000000;
  }
  u8 rStart, gStart, bStart;
  colorPackedToScalar(&rStart, &gStart, &bStart, startColor);
  u8 rStep = rStart / (numSegmentPixels + 1);
  u8 gStep = gStart / (numSegmentPixels + 1);
  u8 bStep = bStart / (numSegmentPixels + 1);
  return pixels.Color(rStep * pos, gStep * pos, bStep * pos);
}

void clear()
{
  for (u16 i = 0; i < pixels.numPixels(); ++i) {
    pixels.setPixelColor(i, 0);
  }
}

// Copied from arduino_sketch.cpp.

u32 colorWeightedAvg(u32 color1, u32 color2, u8 weight)
{
  u8 r1, g1, b1, r2, g2, b2;
  colorPackedToScalar(&r1, &g1, &b1, color1);
  colorPackedToScalar(&r2, &g2, &b2, color2);
  r1 = channelWeightedAvg(r1, r2, weight);
  g1 = channelWeightedAvg(g1, g2, weight);
  b1 = channelWeightedAvg(b1, b2, weight);
  return pixels.Color(r1, g1, b1);
}

u8 channelWeightedAvg(u8 a, u8 b, u8 weight)
{
  u16 aa = a * (256 - weight);
  u16 bb = b * weight;
  return (aa + bb) >> 8;
}

void addPixelColor(u16 pixelPos, u32 addColor)
{
  u32 oldColor = pixels.getPixelColor(pixelPos);
  u32 newColor = additiveColorMix(oldColor, addColor);
  pixels.setPixelColor(pixelPos, newColor);
}

u32 additiveColorMix(u32 color1, u32 color2)
{
  u8 r1, g1, b1, r2, g2, b2;
  colorPackedToScalar(&r1, &g1, &b1, color1);
  colorPackedToScalar(&r2, &g2, &b2, color2);
  r1 = colorChannelClampedAdd(r1, r2);
  g1 = colorChannelClampedAdd(g1, g2);
  b1 = colorChannelClampedAdd(b1, b2);
  u32 c = pixels.Color(r1, g1, b1);
  return c;
}

void colorPackedToScalar(u8* r, u8* g, u8* b, u32 color)
{
  *b = color;
  color >>= 8;
  *g = color;
  color >>= 8;
  *r = color;
}

u8 colorChannelClampedAdd(u8 a, u8 b)
{
  u16 c = a + b;
  if (c > 255) {
    c = 255;
  }
  return c;
}
