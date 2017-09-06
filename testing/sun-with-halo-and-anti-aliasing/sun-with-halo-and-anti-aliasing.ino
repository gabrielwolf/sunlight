// Sunlight with halo and anti aliasing

// Video at: https://vimeo.com/wolfzeitlos/sun-with-halo-and-anti-aliasing
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
double subpixel;

double sunSize = NUM_LEDS * 0.3;      // set the sun's size as a percentage of the total number of pixels
double sunHaloSize = sunSize * 1.5;   // define the halo's size in relation to the sun's size
double sunBrightness = 200;
double haloBrightness = sunBrightness * 1 / 4;

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
  // read poti in 10 bit
  readValue = analogRead(potPin);

  // map position of the poti to the number of pixels, and add imaginary Pixels left and right.
  // now we can partially see the sun
  subpixel = mapdouble(readValue, 0, 1023, - sunHaloSize, NUM_LEDS - 1 + sunHaloSize);

  // wipe values of all pixels to start every loop a clean calculating
  strip.clear();

  // set the actual position and width of the halo
  double from = subpixel - sunHaloSize / 2;
  double to = subpixel + sunHaloSize / 2;

  // debug via serial monitoring
  // Serial.println(from);

  // Halo
  for (int i = from + 1; i <= to; i++) {
    double cosinus = mapdouble(i, from, to, -PI / 2, PI / 2);
    strip.setPixelColor(i, haloBrightness * abs(cos(cosinus)), 0, 0, 0);
  }


  // set the actual position and width of the sun
  from = subpixel - sunSize / 2;
  to = subpixel + sunSize / 2;

  // Sun
  for (int i = from + 1; i <= to; i++) {
    uint32_t color = strip.getPixelColor(i);
    uint8_t r = red(color);
    uint8_t g = green(color);
    uint8_t b = blue(color);
    uint8_t w = white(color);
    double cosinus = mapdouble(i, from, to, -PI / 2, PI / 2);
    strip.setPixelColor(i, r + sunBrightness * pow(abs(cos(cosinus)), 3), 0, 0, 0);   // cosine is pimped, to sharpen the edge of the sun
  }

  // add gamma to all pixels
  for (int i = 0; i <= NUM_LEDS; i++) {
    uint32_t color = strip.getPixelColor(i);
    uint8_t r = red(color);
    uint8_t g = green(color);
    uint8_t b = blue(color);
    uint8_t w = white(color);
    strip.setPixelColor(i, neopix_gamma[(byte)r], neopix_gamma[(byte)g], neopix_gamma[(byte)b], neopix_gamma[(byte)w]);
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

// mapping in double precision
double mapdouble(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

