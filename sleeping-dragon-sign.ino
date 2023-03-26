/***********************************************
  Sleeping Dragon Sign

  Created March 26, 2023
  by John M. Wargo
  https://johnwargo.com
  https://github.com/johnwargo/sleeping-dragon-sign

  Illuminates a "Warning, Sleeping Dragon" sign
  with three different strands of NeoPixels

**************************************************/
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

// used to determine whether the PIR sensor 'sensed' something
bool detectSomething;

void setup() {
  // Initialize all of the LED arrays
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS_1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS_2);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_3>(leds3, NUM_LEDS_3);
  // just to make sure
  FastLED.clear();  // clear all pixel data
}

void loop() {

  detectSomething = true;
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

}

// void doStrandTwoThing() {
// }

// void doStrandThreeThing() {
// }

void doStrandTwoAndThreeThing() {
  // Fade Strand two and three up and down
  // strand 2 Red, strand 3 White

}


void doThatOtherThing() {
  // Blink everything, strand 1 White, everything else Red

}