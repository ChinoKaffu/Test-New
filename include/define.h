#include <Arduino.h>
#include <Wire.h>

#define ULTRASONIC_TRIGGER  26
#define ULTRASONIC_ECHO     25
#define MAX_DEVICES         20
#define checkInterval       5000
#define printInterval       500 //interval of printing updates


#define serial              115200
#define tempSDA             19
#define tempSCL             18
#define tempBias            5
#define pulseSDA            21
#define pulseSCL            22
#define heightReference     15

const int weightDT          = 32;
const int weightSCK         = 33;

double emissivity           = 1.00;
unsigned long lastI2CCheck  = 0;
unsigned long lastPrintTime = 0;  // Store the last time the prints were executed
// Interval in milliseconds (2 seconds)

// Sampling is tightly related to the dynamic range of the ADC.
// refer to the datasheet for further info
#define SAMPLING_RATE                       MAX30100_SAMPRATE_100HZ

// The LEDs currents must be set to a level that avoids clipping and maximises the
// dynamic range
#define IR_LED_CURRENT                      MAX30100_LED_CURR_50MA
#define RED_LED_CURRENT                     MAX30100_LED_CURR_27_1MA

// The pulse width of the LEDs driving determines the resolution of
// the ADC (which is a Sigma-Delta).
// set HIGHRES_MODE to true only when setting PULSE_WIDTH to MAX30100_SPC_PW_1600US_16BITS
#define PULSE_WIDTH                         MAX30100_SPC_PW_1600US_16BITS
#define HIGHRES_MODE                        true
