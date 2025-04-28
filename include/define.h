#include <Arduino.h>
#include <Wire.h>

#define serial_speed        115200
#define MAX_DEVICES         20
#define checkInterval       5000
#define printInterval       200 //interval of printing updates

//connections
#define ULTRASONIC_TRIGGER  25
#define ULTRASONIC_ECHO     26
#define SCL                 21 //goes for both temp and pulse
#define SDA                 22 //goes for both temp and pulse
#define RESET_BUTTON_PIN    15
#define weightSCK           12
#define weightDT            13

//wifi
#define wifissid            "Kenvj"
#define wifipass            "unliload"
#define addressServer       "192.168.157.50"
#define addressPort         4000

#define weightBIAS          +2
#define tempBIAS            +4-3
#define heightBIAS          -3
#define spo2BIAS            +10+5
double emissivity           = 0.99;

unsigned long lastI2CCheck  = 0;
unsigned long lastPrintTime = 0;  // Store the last time the prints were executed
// Interval in milliseconds (2 seconds)

// Sampling is tightly related to the dynamic range of the ADC.
// refer to the datasheet for further info
// #define SAMPLING_RATE       MAX30100_SAMPRATE_100HZ
// #define IR_LED_CURRENT      MAX30100_LED_CURR_24MA     // Lower current = less noise //before 24MA
// #define RED_LED_CURRENT     MAX30100_LED_CURR_27_1MA   // Safe default for SpO₂
// #define PULSE_WIDTH         MAX30100_SPC_PW_800US_15BITS // Best for non-High-Res
// #define HIGHRES_MODE        false

byte ledBrightness = 0x0A; //Options: 0=Off to 255=50mA
byte sampleAverage = 8; //Options: 1, 2, 4, 8, 16, 32
byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
int sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
int pulseWidth = 411; //Options: 69, 118, 215, 411
int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

// Global variables to store sensor readings
float   heightValue = 0, tempValue = 0, heartRate = 0, 
        spO2 = 0, weightValue = 0, bmiValue = 0;

void gatherData(float h, float t, float hr, float oxy, float w, float bmi) {
    heightValue = h;    tempValue = t;
    heartRate = hr;     spO2 = oxy;
    weightValue = w;    bmiValue = bmi;
}

void pulseoxyTest(float hr, float oxy){ heartRate = hr;     spO2 = oxy; };

const byte RATE_SIZE = 8; // Number of readings to average
byte rates[RATE_SIZE] = {0}; // Array of heart rates, initialized
byte rateSpot = 0; // Current index
long lastBeat = 0; // Time of last beat
float beatsPerMinute; // Instantaneous BPM
int beatAvg; // Average BPM
