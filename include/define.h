#include <Arduino.h>
#include <Wire.h>

#define serial_speed        115200
#define MAX_DEVICES         20
#define checkInterval       5000
#define printInterval       1000 //interval of printing updates

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
#define wifissid            "Kenvj"
#define wifipass            "unliload"
#define addressServer       "192.168.157.50"
#define addressPort         4000

#define weightBIAS          +2
#define tempBIAS            +4
#define heightBIAS          +8
double emissivity           = 0.99;


unsigned long lastI2CCheck  = 0;
unsigned long lastPrintTime = 0;  // Store the last time the prints were executed
// Interval in milliseconds (2 seconds)

// Sampling is tightly related to the dynamic range of the ADC.
// refer to the datasheet for further info
#define SAMPLING_RATE       MAX30100_SAMPRATE_100HZ
#define IR_LED_CURRENT      MAX30100_LED_CURR_24MA     // Lower current = less noise //before 24MA
#define RED_LED_CURRENT     MAX30100_LED_CURR_27_1MA   // Safe default for SpO₂
#define PULSE_WIDTH         MAX30100_SPC_PW_800US_15BITS // Best for non-High-Res
#define HIGHRES_MODE        false


// Global variables to store sensor readings
float   heightValue = 0, tempValue = 0, heartRate = 0, 
        spO2 = 0, weightValue = 0, bmiValue = 0;

void gatherData(float h, float t, int hr, int oxy, float w, float bmi) {
    heightValue = h;    tempValue = t;
    heartRate = hr;     spO2 = oxy;
    weightValue = w;    bmiValue = bmi;
}
