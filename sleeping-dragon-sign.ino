/***********************************************
  Sleeping Dragon Sign

  Created March 26, 2023
  by John M. Wargo
  https://johnwargo.com
  https://github.com/johnwargo/sleeping-dragon-sign

  Illuminates a "Warning, Sleeping Dragon" sign
  with three different strands of NeoPixels

**************************************************/
#include <math.h>
#include <FastLED.h>

// first strand
#define NUM_LEDS_1 2
#define DATA_PIN_1 10
// second strand
#define NUM_LEDS_2 3
#define DATA_PIN_2 11
// third strand
#define NUM_LEDS_3 5
#define DATA_PIN_3 12

#define DELAY_VALUE 100

CRGB leds1[NUM_LEDS_1];
CRGB leds2[NUM_LEDS_2];
CRGB leds3[NUM_LEDS_3];

#define checkVal1 500
#define checkVal2 500
unsigned long curTime1;
unsigned long curTime2;
bool direction1 = true;
bool direction2 = true;
unsigned long prevTime1 = millis();
unsigned long prevTime2 = millis();

// used to determine whether the PIR sensor 'sensed' something
bool detectSomething;

void setup() {
  Serial.begin(9600);
  // Initialize all of the LED arrays
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS_1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS_2);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_3>(leds3, NUM_LEDS_3);
  // just to make sure
  FastLED.clear();  // clear all pixel data
}

void loop() {
  Serial.println("Loop");
  detectSomething = false;
  if (!detectSomething) {
    doStrandOneThing();
    doStrandTwoAndThreeThing();
    // doStrandTwoThing();
    // doStrandThreeThing();
  } else {
    doThatOtherThing();
  }
  delay(DELAY_VALUE);
}

void doStrandOneThing() {
  // Alternate the Warning Symbols White
  curTime1 = millis();
  if (curTime1 - prevTime1 > checkVal1) {
    prevTime1 = curTime1;
    direction1 = !direction1;
    if (direction1) {
      leds1[0] = CRGB::White;
      leds1[1] = CRGB::Black;
    } else {
      leds1[0] = CRGB::Black;
      leds1[1] = CRGB::White;
    }
    FastLED.show();
  }
}

// void doStrandTwoThing() {
// }

// void doStrandThreeThing() {
// }

void doStrandTwoAndThreeThing() {
  // Fade Strand two (Red) and three (White) up and down

  int colorVal;

  curTime2 = millis();
  if (curTime2 - prevTime2 > checkVal2) {
    prevTime2 = curTime2;
    direction2 = !direction2;
  }

  colorVal = round((curTime2 - prevTime2) / checkVal2);
  Serial.println(colorVal);
  delay(100);

  // for (int i = 0; i < NUM_LEDS_2; i++) {
  // // Red
  //   leds2[i].setRGB(colorVal, 0, 0);
  // }
  // for (int i = 0; i < NUM_LEDS_3; i++) {
  // // White
  //   leds3[i].setRGB(colorVal, colorVal, colorVal);
  // }
  // FastLED.show();
}


void doThatOtherThing() {
  // Blink everything, strand 1 White, everything else Red
}