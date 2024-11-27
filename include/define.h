#include <Arduino.h>
#include <Wire.h>

#define ULTRASONIC_TRIGGER  26
#define ULTRASONIC_ECHO     25
#define MAX_DEVICES         20
#define checkInterval       5000
#define printInterval       500 //interval of printing updates

#define tempSDA             19
#define tempSCL             18
#define pulseSDA            21
#define pulseSCL            22

unsigned long lastI2CCheck = 0;
unsigned long lastPrintTime = 0;  // Store the last time the prints were executed
  // Interval in milliseconds (2 seconds)
