/***********************************************
  Sleeping Dragon Sign

  Created March 26, 2023
  by John M. Wargo
  https://johnwargo.com
  https://github.com/johnwargo/sleeping-dragon-sign

  Illuminates a "Warning, Sleeping Dragon" sign
  with three different strands of NeoPixels

**************************************************/

// This sketch is currently setup for the Adafruit Huzzah32
// https://learn.adafruit.com/adafruit-huzzah32-esp32-feather/pinouts

#include <FastLED.h>
#include <math.h>
#include <HardwareSerial.h>
#include <DFRobot_mmWave_Radar.h>

#define DEBUG

// first strand
#define NUM_LEDS_1 2
#define DATA_PIN_1 12
// second strand
#define NUM_LEDS_2 3
#define DATA_PIN_2 27
// third strand
#define NUM_LEDS_3 5
#define DATA_PIN_3 33

#define DELAY_VALUE 100

CRGB leds1[NUM_LEDS_1];
CRGB leds2[NUM_LEDS_2];
CRGB leds3[NUM_LEDS_3];

#define checkVal1 500
#define checkVal2 2000
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

// Flag to let the sketch know when switching between
// detected and not detected
bool strategyChanged = true;

// used to determine whether the sensor 'sensed' a person
bool detectedSomething = false;

HardwareSerial SerialPort(1);
DFRobot_mmWave_Radar sensor(&SerialPort);

void setup() {

#ifdef DEBUG
  // Enable serial connection to the IDE
  Serial.begin(115200);
#endif

  // Initialize communication with the mmWave board
  SerialPort.begin(15200, SERIAL_8N1, 20, 22);
  sensor.factoryReset();     //Restore to the factory settings
  sensor.DetRangeCfg(0, 3);  //The detection range is as far as 3m
  sensor.OutputLatency(0, 0);

  // Initialize all of the LED arrays
  FastLED.addLeds<NEOPIXEL, DATA_PIN_1>(leds1, NUM_LEDS_1);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_2>(leds2, NUM_LEDS_2);
  FastLED.addLeds<NEOPIXEL, DATA_PIN_3>(leds3, NUM_LEDS_3);
  // just to make sure
  FastLED.clear();  // clear all pixel data
  // test all the lights
  exerciseStrand(leds1, NUM_LEDS_1);
  exerciseStrand(leds2, NUM_LEDS_2);
  exerciseStrand(leds3, NUM_LEDS_3);
}

void loop() {
  // Serial.println("Loop");

#ifdef DEBUG
  detectedSomething = false;
#else
  detectedSomething = digitalRead(PIR_SENSOR_PIN);
#endif

  if (detectedSomething) {
    doThatOtherThing();
  } else {
    doStrandOneThing();
    doStrandTwoThing();
    doStrandThreeThing();
  }
  // delay(DELAY_VALUE);
}

void doStrandOneThing() {
  // Alternate the Warning Symbols White
  // Serial.println("doStrandOneThing");
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

void doStrandTwoThing() {
  // Fade strand 2 up and down in Red
  // Serial.println("doStrandTwoThing");
  curTime2 = millis();
  if (curTime2 - prevTime2 > checkVal2) {
    Serial.println("switching direction");
    prevTime2 = curTime2;
    direction2 = !direction2;
  }

  // had to convert the values to float to make the division work
  int colorVal = round(((float(curTime2) - float(prevTime2)) / float(checkVal2)) * 255);
  // Change direction
  if (direction2) colorVal = 255 - colorVal;

  for (int i = 0; i < NUM_LEDS_2; i++) {
    leds2[i].setRGB(colorVal, 0, 0);
  }
  FastLED.show();
}

void doStrandThreeThing() {
  // Default behavior of strand five is all lights on, White.
  // Serial.println("doStrandThreeThing");
  // Did the strand change elsewhere (doThatOtherThing)?
  if (strategyChanged) {
    // then we have to switch them back. otherwise leave them alone
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

void exerciseStrand(CRGB leds[], int numLEDs) {
  for (int i = 0; i < numLEDs; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(DELAY_VALUE);
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(DELAY_VALUE);
  }
  delay(500);
}