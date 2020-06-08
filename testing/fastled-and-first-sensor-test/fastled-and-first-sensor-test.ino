// Adaption of FastLED RGBW Example Sketch
// Written by David Madison
// http://partsnotincluded.com

#include "FastLED.h"
#include "FastLED_RGBW.h"

#define NUM_LEDS 144
#define DATA_PIN 6

CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *)&leds[0];

const uint8_t brightness = 160;

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
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
  FastLED.setBrightness(brightness);
  FastLED.show();
}

void loop() {
  // colorFill(CRGB::Red);
  // colorFill(CRGB::Green);
  // colorFill(CRGB::Blue);
  // fillWhite();
  // rainbowLoop();
  // }

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
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);

  plusewidth = pulseIn(outpin, LOW);
  bcolour = plusewidth / 400. - 1;
  bcolour = (bcolour);

  // Stretch values for testing purposes
  if (rcolour > bcolour && bcolour > gcolour) {
    rcolour = 255;
    bcolour = bcolour / 2;
    gcolour = 0;
  }
  if (rcolour > gcolour && gcolour > bcolour) {
    rcolour = 255;
    gcolour = gcolour / 2;
    bcolour = 0;
  }
  if (gcolour > bcolour && bcolour > rcolour) {
    gcolour = 255;
    bcolour = bcolour / 2;
    rcolour = 0;
  }
  if (gcolour > rcolour && rcolour > bcolour) {
    gcolour = 255;
    rcolour = rcolour / 2;
    bcolour = 0;
  }
  if (bcolour > rcolour && rcolour > gcolour) {
    bcolour = 255;
    rcolour = rcolour / 2;
    gcolour = 0;
  }
  if (bcolour > gcolour && gcolour > rcolour) {
    bcolour = 255;
    gcolour = bcolour / 2;
    rcolour = 0;
  }

  for (int i = 0; i <= NUM_LEDS; i++) {
    if (rcolour == -1) {
      rcolour = 0;
    }
    if (gcolour == -1) {
      gcolour = 0;
    }
    if (bcolour == -1) {
      bcolour = 0;
    }

    Serial.print(rcolour);
    Serial.print(", ");
    Serial.print(gcolour);
    Serial.print(", ");
    Serial.println(bcolour);
    Serial.println(" ");
    Serial.println("");

    leds[i] = CRGBW(rcolour, gcolour, bcolour, 0);
  }

  FastLED.show();
}
