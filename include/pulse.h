#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <MAX30100.h>

PulseOximeter pox;
MAX30100 sensor;
uint32_t tsLastReport = 0;

namespace pulse {

    // initializes the sensor
    void setup() {
        if (!pox.begin()) {
            Serial.println("ERROR: Failed to initialize pulse oximeter");
            errorWarn();
        }

        pox.setIRLedCurrent(IR_LED_CURRENT);
        sensor.setMode(MAX30100_MODE_SPO2_HR);
        sensor.setLedsCurrent(IR_LED_CURRENT, RED_LED_CURRENT);
        sensor.setLedsPulseWidth(PULSE_WIDTH);
        sensor.setSamplingRate(SAMPLING_RATE);
        sensor.setHighresModeEnabled(HIGHRES_MODE);


        pox.setIRLedCurrent(IR_LED_CURRENT);
        Serial.println("PulseOxy sensor initialized!");
    }

    float getRate(){return pox.getHeartRate();}
    uint8_t getOxy(){return pox.getSpO2();}
}