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

#define DELAY_VALUE 200

CRGB leds1[NUM_LEDS_1];
CRGB leds2[NUM_LEDS_2];
CRGB leds3[NUM_LEDS_3];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS_1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS_2);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_3>(leds3, NUM_LEDS_3);
}

void loop() {
  FastLED.clear();  // clear all pixel data
  exerciseStrand(leds1, NUM_LEDS_1);
  exerciseStrand(leds2, NUM_LEDS_2);
  exerciseStrand(leds3, NUM_LEDS_3);
  delay(DELAY_VALUE);
}

void exerciseStrand(CRGB leds[], int numLEDs) {
  for (int i = 0; i < numLEDs; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(DELAY_VALUE);
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(DELAY_VALUE);
  }
}