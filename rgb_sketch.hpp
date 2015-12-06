/* This file was automatically generated.  Do not edit! */
int wrap_16pix(int p);
int wrap(int p,int w);
int wrap_numpixels(int p);
u32 rol(u32 v,u8 p);
u32 ror(u32 v,u8 p);
u32 addColor(u32 color,u8 v,u8 i);
void addPixelColor(u16 pixelPos,u8 brightness,u8 colorSelect);
u8 WeightAvg(u8 a,u8 b,u8 weight);
void drawTaperedSegment(u16 highRezPos,u8 colorSelect,u8 segmentLength,u8 *brightnessArray);
void genTaperedSegment(u8 *brightnessArray,u8 segmentLength,u8 brightestVal);
u16 wrap_add(s16 v,s16 add_v,s16 max_v);
void smoothRunners(u16 run_s,u16 delay_ms,s16 r_add,s16 g_add,s16 b_add,u8 r_len,u8 g_len,u8 b_len,u16 r_offset,u16 g_offset,u16 b_offset);
void halloweenRunners(u16 run_s,u16 delay_ms,u8 segLen,u8 speed);
void clear(u32 c,u8 delay_ms);
void xmasRedGreenTwinkles(u16 run_s);
void loop();
void setup();
extern Adafruit_NeoPixel pixels;
