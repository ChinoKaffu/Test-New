#include <Arduino.h>
#include <Wire.h>

#define serial_speed        115200
#define MAX_DEVICES         20
#define checkInterval       5000
#define printInterval       2000 //interval of printing updates

//connections
#define ULTRASONIC_TRIGGER  25
#define ULTRASONIC_ECHO     26
#define tempSDA             19
#define tempSCL             18
#define pulseSDA            21
#define pulseSCL            22
#define RESET_BUTTON_PIN    15
#define weightSCK           12
#define weightDT            13

//wifi
#define wifissid            "tite"
#define wifipass            "bayag"


#define tempBIAS            4  //temp bias to acceptable level
double emissivity           = 0.99;


unsigned long lastI2CCheck  = 0;
unsigned long lastPrintTime = 0;  // Store the last time the prints were executed
// Interval in milliseconds (2 seconds)

// Sampling is tightly related to the dynamic range of the ADC.
// refer to the datasheet for further info
#define SAMPLING_RATE                       MAX30100_SAMPRATE_100HZ

#define IR_LED_CURRENT                      MAX30100_LED_CURR_50MA
#define RED_LED_CURRENT                     MAX30100_LED_CURR_27_1MA
// set HIGHRES_MODE to true only when setting PULSE_WIDTH to MAX30100_SPC_PW_1600US_16BITS
#define PULSE_WIDTH                         MAX30100_SPC_PW_1600US_16BITS
#define HIGHRES_MODE                        false
