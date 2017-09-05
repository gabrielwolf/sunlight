// Sunlight

// First small test of a sun module. Hue is limited to red.
// Video at: https://vimeo.com/wolfzeitlos/sun-red
// Git at: https://github.com/gabrielwolf/sunlight

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUM_LEDS 144
#define BRIGHTNESS 255

const int potPin = A0;  // the purpose of the poti is testing variables tactically
int readValue;
int pixel;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

byte neopix_gamma[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
  115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
  144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
  177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
  215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255
};


void setup() {
  pinMode(potPin, INPUT);             // get potPin ready
  Serial.begin(9600);                 // open serial port as debug console
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();                       // initialize all pixels to 'off'
}


void loop() {
  // sun with variable halo (everything plain red for testing)
  int16_t sunHaloSize = NUM_LEDS / 2 * 0.15;     // the fraction between 0 and 1 is a percentage of the number of pixels
  uint8_t sunBrightness = 150;
  uint8_t haloBrightness = sunBrightness * 2 / 3;

  // read poti in 10 bit
  readValue = analogRead(potPin);

  // map variable to number of pixels, and add sunHaloSize left and right, then we have twilight before sunrise and after sunset
  pixel = map(readValue, 0, 1023, - sunHaloSize, NUM_LEDS - 1 + sunHaloSize);

  // debug via serial monitoring
  // Serial.print("readvalue: ");
  // Serial.println(readValue);

  // wipe values of all pixels for starting calculation fresh in every loop
  strip.clear();

  // set the center dot
  strip.setPixelColor(pixel, sunBrightness, 0, 0, 0);

  // calc the halos left and right
  for (int i = 1; i <= sunHaloSize; i++) {
    strip.setPixelColor(pixel - i, neopix_gamma[haloBrightness - map(i, 0, sunHaloSize, 0, haloBrightness)], 0, 0, 0);
    strip.setPixelColor(pixel + i, neopix_gamma[haloBrightness - map(i, 0, sunHaloSize, 0, haloBrightness)], 0, 0, 0);
  }

  // add a blue sky background color to all the strip testwise
  for (int i = 0; i < NUM_LEDS; i++)
  {
    uint32_t color = strip.getPixelColor(i);
    uint8_t r = red(color);
    uint8_t g = green(color);
    uint8_t b = blue(color);
    uint8_t w = white(color);
    strip.setPixelColor(i, r, g, b | 1, w);   // bitwise OR of the new colors (simply add a layer)
  }

  // all LEDs shall show their calculated values
  strip.show();

}

// ---- Tools ----

// get 8 bit RGBW values from a 32 bit color

uint8_t white(uint32_t c) {
  return (c >> 24);
}

uint8_t red(uint32_t c) {
  return (c >> 16);
}

uint8_t green(uint32_t c) {
  return (c >> 8);
}

uint8_t blue(uint32_t c) {
  return (c);
}

