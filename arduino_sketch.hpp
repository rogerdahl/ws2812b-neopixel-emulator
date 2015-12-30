/* This file was automatically generated.  Do not edit! */
s16 wrap(s16 val,s16 maxVal);
u8 colorChannelClampedAdd(u8 a,u8 b);
u32 additiveColorMix(u32 color1,u32 color2);
u8 channelWeightedAvg(u8 a,u8 b,u8 weight);
void colorPackedToScalar(u8 *r,u8 *g,u8 *b,u32 color);
void addPixelColor(u16 pixelPos,u32 addColor);
u32 colorWeightedAvg(u32 color1,u32 color2,u8 weight);
u32 calcTaperedSegmentPixel(u8 numSegmentPixels,u8 pos,u32 centerColor);
void drawTaperedSegment(u16 superPos,u8 numSegmentPixels,u32 color);
u16 wrapAdd(s16 val,s16 addVal,s16 maxVal);
void clear(u32 color,u16 clearMs);
void smoothRunners(u16 runSec,u16 delayMs,struct Segment *segmentPtrIn,u8 numSegments);
void xmasRedGreenTwinkles(u16 runSec);
void loop();
void setup();
#if defined(Arduino_h)
void debugMarker();
#endif
extern Adafruit_NeoPixel pixels;
