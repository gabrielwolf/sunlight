// -------- Some handy color functions --------

// - RGBW (32 bit int) -> R, G, B, W (8 bit ints)
// - R, G, B, W (8 bit ints) -> RGBW (32 bit int)

// --> uint32_t RGB2RGBW(uint16_t red, uint16_t green, uint16_t blue)
// Calculates RGBW values from a given RGB triplet. Algorithm is based on the
// selected solution of a StackOverflow answer:
// https://stackoverflow.com/questions/40312216/converting-rgb-to-rgbw

// --> uint32_t colorTemperature2RGB(double temperature)
// An algorithm from Tanner Helland that calculates coresponding RGB values for
// a given color temperature.
// http://www.tannerhelland.com/4435/convert-temperature-rgb-algorithm-code/

// --> uint16_t RGB2ColorTemperature(uint16_t r, uint16_t g, uint16_t b)
// An algorithm from Adafruit, which calculates a corrected color temperature
// out of RGB values.
// https://github.com/adafruit/Adafruit_TCS34725/blob/master/Adafruit_TCS34725.cpp

byte neopix_gamma[] = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,
    1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,   2,
    2,   2,   2,   2,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,
    4,   5,   5,   5,   5,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,
    8,   9,   9,   9,   10,  10,  10,  11,  11,  11,  12,  12,  13,  13,  13,
    14,  14,  15,  15,  16,  16,  17,  17,  18,  18,  19,  19,  20,  20,  21,
    21,  22,  22,  23,  24,  24,  25,  25,  26,  27,  27,  28,  29,  29,  30,
    31,  32,  32,  33,  34,  35,  35,  36,  37,  38,  39,  39,  40,  41,  42,
    43,  44,  45,  46,  47,  48,  49,  50,  50,  51,  52,  54,  55,  56,  57,
    58,  59,  60,  61,  62,  63,  64,  66,  67,  68,  69,  70,  72,  73,  74,
    75,  77,  78,  79,  81,  82,  83,  85,  86,  87,  89,  90,  92,  93,  95,
    96,  98,  99,  101, 102, 104, 105, 107, 109, 110, 112, 114, 115, 117, 119,
    120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142, 144, 146,
    148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175, 177,
    180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
    215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252,
    255};

#include "FastLED.h"
#include "FastLED_RGBW.h"

#define NUM_LEDS 144
#define DATA_PIN 6
const uint8_t brightness = 100;

CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *)&leds[0];

int potPin = 0;

void setup() {
  pinMode(potPin, INPUT);  // get potPin ready
  Serial.begin(115200);

  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void loop() {
  uint32_t potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 0, 20000);

  // Serial.print("potValue=");
  // Serial.println(potValue);

  uint32_t color = colorTemperature2RGB(potValue);

  // debug test colors
  // color = 0xff00ff22;
  // color = RGBWtoInt(0xff, 0, 0xff, 0x88);
  // Serial.println(color);

  // make use of the RGB(W) LED of SK6812 NeoPixels.
  // color = RGB2RGBW(maskRed(rgb), maskGreen(rgb), maskBlue(rgb));

  printRGBW(maskRed(color), maskGreen(color), maskBlue(color), maskWhite(color));

  for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGBW(neopix_gamma[maskRed(color)], neopix_gamma[maskGreen(color)],
                    neopix_gamma[maskBlue(color)], neopix_gamma[maskWhite(color)]);
    // leds[i] = CRGBW(maskRed(color), maskGreen(color), maskBlue(color), 0);

    FastLED.show();
  }
}

// -------- debug helper --------

void printRGBW(unsigned int red, unsigned int green, unsigned int blue,
               unsigned int white) {
  Serial.print("R=");
  Serial.print(red);
  Serial.print(" ");
  Serial.print("G=");
  Serial.print(green);
  Serial.print(" ");
  Serial.print("B=");
  Serial.print(blue);
  Serial.print(" ");
  Serial.print("W=");
  Serial.print(white);
  Serial.println("");
}

// -------- color variable tools --------

uint32_t RGBWtoInt(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  uint32_t rgb = r;
  rgb = (rgb << 8) | g;
  rgb = (rgb << 8) | b;
  rgb = (rgb << 8) | w;
  return rgb;
}

uint8_t maskRed(uint32_t c) { return (c >> 24); }
uint8_t maskGreen(uint32_t c) { return (c >> 16); }
uint8_t maskBlue(uint32_t c) { return (c >> 8); }
uint8_t maskWhite(uint32_t c) { return (c); }

uint32_t RGB2RGBW(uint16_t red, uint16_t green, uint16_t blue) {
  // Get the maximum between R, G, and B
  float tM = max(red, max(green, blue));

  // If the maximum value is 0, immediately return pure black.
  if (tM == 0) return RGBWtoInt(0, 0, 0, 0);

  // This section serves to figure out what the color with 100% hue is
  float multiplier = 255.0f / tM;
  float hR = red * multiplier;
  float hG = green * multiplier;
  float hB = blue * multiplier;

  // This calculates the Whiteness (not strictly speaking luminance) of the
  // color
  float M = max(hR, max(hG, hB));
  float m = min(hR, min(hG, hB));
  float luminance = ((M + m) / 2.0f - 127.5f) * (255.0f / 127.5f) / multiplier;

  // Calculate the output values
  red = (uint8_t)(red - luminance);
  green = (uint8_t)(green - luminance);
  blue = (uint8_t)(blue - luminance);
  uint8_t white = (uint8_t)luminance * 0.6;  // 0.6 is a first subjective
                                             // correction towards the expected
                                             // sample RGB color impression.

  return RGBWtoInt(red, green, blue, white);
}

// -------- color temperature --------

uint32_t colorTemperature2RGB(double temperature) {
  // if (temperature < 1000) temperature = 1000;
  if (temperature > 40000) temperature = 40000;

  temperature = temperature / 100;

  int red;
  int green;
  int blue;

  // red

  if (temperature <= 66.0) {
    red = 255;
  } else {
    red = temperature - 60.0;
    red = 329.698727446 * pow(red, -0.1332047592);
    if (red < 0) red = 0;
    if (red > 255) red = 255;
  }

  // green

  if (temperature <= 66.0) {
    green = temperature;
    green = 99.4708025861 * log(green) - 161.1195681661;
    if (green < 0) green = 0;
    if (green > 255) green = 255;
  } else {
    green = temperature - 60.0;
    green = 288.1221695283 * pow(green, -0.0755148492);
    if (green < 0) green = 0;
    if (green > 255) green = 255;
  }

  // blue

  if (temperature >= 66.0) {
    blue = 255;
  } else {
    if (temperature <= 19.0) {
      blue = 0;
    } else {
      blue = temperature - 10;
      blue = 138.5177312231 * log(blue) - 305.0447927307;
      if (blue < 0) blue = 0;
      if (blue > 255) blue = 255;
    }
  }

  return RGBWtoInt(red, green, blue, 0);
}

uint16_t RGB2ColorTemperature(uint16_t r, uint16_t g, uint16_t b) {
  float X, Y, Z; /* RGB to XYZ correlation      */
  float xc, yc;  /* Chromaticity co-ordinates   */
  float n;       /* McCamy's formula            */
  float cct;

  /* 1. Map RGB values to their XYZ counterparts.    */
  /* Based on 6500K fluorescent, 3000K fluorescent   */
  /* and 60W incandescent values for a wide range.   */
  /* Note: Y = Illuminance or lux                    */
  X = (-0.14282F * r) + (1.54924F * g) + (-0.95641F * b);
  Y = (-0.32466F * r) + (1.57837F * g) + (-0.73191F * b);
  Z = (-0.68202F * r) + (0.77073F * g) + (0.56332F * b);

  /* 2. Calculate the chromaticity co-ordinates      */
  xc = (X) / (X + Y + Z);
  yc = (Y) / (X + Y + Z);

  /* 3. Use McCamy's formula to determine the CCT    */
  n = (xc - 0.3320F) / (0.1858F - yc);

  /* Calculate the final CCT */
  cct =
      (449.0F * powf(n, 3)) + (3525.0F * powf(n, 2)) + (6823.3F * n) + 5520.33F;

  /* Return the results in degrees Kelvin */
  return (uint16_t)cct;
}

