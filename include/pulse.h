#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>
#include <MAX30100.h>

#define REPORTING_PERIOD_MS     1000
#define AVERAGE_OVER            5

PulseOximeter pox;
MAX30100 sensor;
uint32_t tsLastReport = 0;

namespace pulse {

    // initializes the sensor
    void setup() {
        //pulsei2c.begin(pulseSDA,pulseSCL);
        if (!pox.begin()) {
            Serial.println("ERROR: Failed to initialize pulse oximeter");
            errorWarn();
        }
        sensor.setMode(MAX30100_MODE_SPO2_HR);
        sensor.setLedsCurrent(IR_LED_CURRENT, RED_LED_CURRENT);
        sensor.setLedsPulseWidth(PULSE_WIDTH);
        sensor.setSamplingRate(SAMPLING_RATE);
        sensor.setHighresModeEnabled(HIGHRES_MODE);


        pox.setIRLedCurrent(IR_LED_CURRENT);
        Serial.println(pox.getRedLedCurrentBias()); //8
        printf("PulseOxy sensor initialized! \n");
    }

    float getRate(){
        return pox.getHeartRate();
    }

    uint8_t getOxy(){
        return pox.getSpO2();
    }
}