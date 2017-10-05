// This file reads RGB values from a sensor (e.g. the GY-31) and directly
// outputs the colors to a LED strip. The code is based on a video tutorial:
// www.toptechboy.com/arduino/lesson-15-super-cool-arduino-color-sensor-project/

// Git at: https://github.com/gabrielwolf/sunlight

#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LEDS 144
#define BRIGHTNESS 30

Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRBW + NEO_KHZ800);

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

int redled = 11;
int greenled = 10;
int blueled = 6;

int S3 = 8;
int S2 = 7;
int outpin = 4;
int ledpin = 2;

unsigned int plusewidth;

int rcolour;
int gcolour;
int bcolour;

void setup() {
  Serial.begin(9600);
  pinMode(redled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);

  pinMode(S3, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(outpin, INPUT);
  pinMode(ledpin, OUTPUT);

  digitalWrite(ledpin, LOW);

  Serial.print("red");
  Serial.print(", ");
  Serial.print("green");
  Serial.print(", ");
  Serial.println("blue");

  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show();
}

void loop() {
  // read red
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

  plusewidth = pulseIn(outpin, LOW);
  rcolour = plusewidth / 400. - 1;
  rcolour = (rcolour);

  // read green
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  plusewidth = pulseIn(outpin, LOW);
  gcolour = plusewidth / 400. - 1;
  gcolour = (gcolour);

  // read blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  plusewidth = pulseIn(outpin, LOW);
  bcolour = plusewidth / 400. - 1;
  bcolour = (bcolour);

  // Stretch values for testing purposes
  // if (rcolour > bcolour && bcolour > gcolour) {
  //   rcolour = 255;
  //   bcolour = bcolour / 2;
  //   gcolour = 0;
  // }
  // if (rcolour > gcolour && gcolour > bcolour) {
  //   rcolour = 255;
  //   gcolour = gcolour / 2;
  //   bcolour = 0;
  // }
  // if (gcolour > bcolour && bcolour > rcolour) {
  //   gcolour = 255;
  //   bcolour = bcolour / 2;
  //   rcolour = 0;
  // }
  // if (gcolour > rcolour && rcolour > bcolour) {
  //   gcolour = 255;
  //   rcolour = rcolour / 2;
  //   bcolour = 0;
  // }
  // if (bcolour > rcolour && rcolour > gcolour) {
  //   bcolour = 255;
  //   rcolour = rcolour / 2;
  //   gcolour = 0;
  // }
  // if (bcolour > gcolour && gcolour > rcolour) {
  //   bcolour = 255;
  //   gcolour = bcolour / 2;
  //   rcolour = 0;
  // }

  for (int i = 0; i <= NUM_LEDS; i++) {
    Serial.print(rcolour);
    Serial.print(", ");
    Serial.print(gcolour);
    Serial.print(", ");
    Serial.println(bcolour);
    Serial.println(" ");
    Serial.println("");

    strip.setPixelColor(i, rcolour, gcolour, bcolour, 0);
  }

  strip.show();
}
