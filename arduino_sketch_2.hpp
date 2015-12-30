/* This file was automatically generated.  Do not edit! */
u8 colorChannelClampedAdd(u8 a,u8 b);
u32 additiveColorMix(u32 color1,u32 color2);
u8 channelWeightedAvg(u8 a,u8 b,u8 weight);
void colorPackedToScalar(u8 *r,u8 *g,u8 *b,u32 color);
void addPixelColor(u16 pixelPos,u32 addColor);
u32 colorWeightedAvg(u32 color1,u32 color2,u8 weight);
u32 calcTailSegmentPixel(u8 numSegmentPixels,u8 pos,u32 startColor);
void drawTaperedSegment(u16 superPos,u8 numSegmentPixels,u32 color,u8 numEnterExitPixels);
void clear();
void meteors(u16 runSec,u16 delayMs,u8 numMeteors,u8 minPixels,u8 maxPixels,s16 minSpeed,s16 maxSpeed);
void loop();
void setup();
extern Adafruit_NeoPixel pixels;
