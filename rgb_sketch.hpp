/* This file was automatically generated.  Do not edit! */
int wrap(int p,int w);
u8 colorChannelClampedAdd(u8 a,u8 b);
u32 additiveColorMix(u32 color1,u32 color2);
u8 channelWeightedAvg(u8 a,u8 b,u8 weight);
void colorPackedToScalar(u8 *r,u8 *g,u8 *b,u32 color);
void addPixelColor(u16 pixelPos,u32 addColor);
u32 colorWeightedAvg(u32 color1,u32 color2,u8 weight);
u32 calcTaperedSegmentPixel(u8 numSegmentPixels,u8 pos,u32 centerColor);
void drawTaperedSegment(u16 superPos,u8 numSegmentPixels,u32 color);
u16 wrap_add(s16 v,s16 add_v,s16 max_v);
void clear(u32 color,u16 clear_ms);
void smoothRunners(u16 run_s,u16 delay_ms,struct Segment *segmentPtrIn,u8 numSegments);
void xmasRedGreenTwinkles(u16 run_s);
void loop();
void setup();
extern Adafruit_NeoPixel pixels;
