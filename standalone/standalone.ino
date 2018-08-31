// Standalone fern software for Project Illuminate 2018
// Written by Jason Chu <me@chuie.io>
// Last updated: September 01 2018
// Code licensed under the MIT license

#include <FastLED.h>
#include <math.h>

#define ORDER_M20 RBG

#define LED_TYPE UCS1903

#define PIN_1 10
#define PIN_2 9
#define PIN_3 6
#define PIN_4 5

#define NUM_LEDS 40

CRGB leds[NUM_LEDS];

void setupLEDs() {
    pinMode(PIN_1, OUTPUT);
    FastLED.addLeds<LED_TYPE, PIN_1, ORDER_M20>(leds, NUM_LEDS);
}

void setup() {
  setupLEDs();
  srand(millis());
}

double t;
unsigned char v;
unsigned char h;
unsigned long mi;

bool whiteActive = 0;
unsigned int whiteLED;
double whiteValue;
double whiteTime;

void handleWhite() {
  whiteTime = (double)(mi % 5000) / 1000.0;
  if (whiteTime > 3.0) {
    whiteActive = 0;
    return;
  } else if (!whiteActive) {
    whiteLED = rand() % NUM_LEDS;
    whiteActive = 1;
  }

  whiteValue = sin(((whiteTime / 1.5) - 0.5) * PI) / 2.0 + 0.5;

  double dr = 255 - leds[whiteLED].r;
  double dg = 255 - leds[whiteLED].g;
  double db = 255 - leds[whiteLED].b;

  leds[whiteLED].r += (int)(dr * whiteValue);
  leds[whiteLED].g += (int)(dg * whiteValue);
  leds[whiteLED].b += (int)(db * whiteValue);
}

void loop() {
  mi = millis();
  double t = (double)(mi) / 1000.0;
  int v = (int)(((sin((t/2.0) * PI) + 2.0) / 3.0) * 255.0);
  int h = (int)(sin((t * PI)/30.0 + 1.0) * 127.0 + 127.0);

  fill_solid(leds, NUM_LEDS, CHSV(h, 255, v));

  handleWhite();
  
  FastLED.show();
}
