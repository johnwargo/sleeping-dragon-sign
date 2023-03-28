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
#define checkVal2 1000
#define checkVal4 250
unsigned long curTime1;
unsigned long curTime2;
unsigned long curTime4;
bool direction1 = true;
bool direction2 = true;
bool direction4 = true;
unsigned long prevTime1 = millis();
unsigned long prevTime2 = millis();
unsigned long prevTime4 = millis();

bool strategyChanged = true;

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
  // Serial.println("Loop");
  detectSomething = false;
  if (!detectSomething) {
    doStrandOneThing();
    doStrandTwoThing();
    doStrandThreeThing();
  } else {
    doThatOtherThing();
  }
  // delay(DELAY_VALUE);
}

void doStrandOneThing() {
  // Serial.println("doStrandOneThing");
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
    delay(100);
  }
}

void doStrandTwoThing() {
  int colorVal;

  // Serial.println("doStrandTwoThing");

  curTime2 = millis();
  if (curTime2 - prevTime2 > checkVal2) {
    prevTime2 = curTime2;
    direction2 = !direction2;
  }

  colorVal = round(((curTime2 - prevTime2) / checkVal2) * 255);

  if (direction2) colorVal = 255 - colorVal;
  Serial.println(colorVal);
  for (int i = 0; i < NUM_LEDS_2; i++) {
    // Red
    leds2[i].setRGB(colorVal, 0, 0);
  }
  FastLED.show();
}

void doStrandThreeThing() {
  // Serial.println("doStrandThreeThing");
  // Default behavior of strand three is all lights on and White.
  // Did the strand colors change elsewhere?
  if (strategyChanged) {
    // then we have to switch them back
    strategyChanged = false;
    // set all the LEDs to white
    for (int i = 0; i < NUM_LEDS_3; i++) {
      leds3[i] = CRGB::White;
    }
    FastLED.show();
  }
}

void doThatOtherThing() {
  // Blink everything, strand 1 White, everything else Red
  strategyChanged = true;
  // everything blinks together
  curTime4 = millis();
  if (curTime4 - prevTime4 > checkVal4) {
    prevTime4 = curTime4;
    direction4 = !direction4;
    if (direction4) {
      setStrandColor(leds1, NUM_LEDS_1, CRGB::White);
      setStrandColor(leds2, NUM_LEDS_2, CRGB::Red);
      setStrandColor(leds3, NUM_LEDS_3, CRGB::Red);
    } else {
      FastLED.clear();
    }
    FastLED.show();
  }
}

void setStrandColor(CRGB leds[], int numLEDs, CRGB color) {
  for (int i = 0; i < numLEDs; i++) {
    leds[i] = color;
  }
}
