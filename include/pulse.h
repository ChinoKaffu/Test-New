#ifndef PULSE_H
#define PULSE_H

#include <Wire.h>
#include <MAX30105.h>

MAX30105 particleSensor;

namespace pulse {
    // Initializes the sensor
    void setup() {
        // Initialize sensor with default I2C pins (GPIO 21 SDA, GPIO 22 SCL)
        if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
            Serial.println("ERROR: Failed to initialize pulse oximeter");
            while (1); // Halt on failure
        }

        particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

    }

    float getRate() {
        uint32_t irValue = particleSensor.getIR();
          // Detect if the sensor is touched (you can set a threshold for detecting a finger)
        if (irValue > 5000) { 
            float simulatedBPM = 80 + random(0, 11);
            return simulatedBPM;
        }
        return 0.0;
    }


    // Returns the oxygen saturation level (SpO2) as a percentage
    float getOxy() {
        // Read both red and IR values for SpO2 calculation
        uint32_t redValue = particleSensor.getRed();
        uint32_t irValue = particleSensor.getIR();

        // Basic SpO2 estimation using ratio of red to IR signals
        if (irValue < 5000 || redValue < 5000) { // Signal too weak
            return 0;
        }

        // Calculate ratio and empirical SpO2
        float ratio = (float)redValue / (float)irValue;
        float spo2 = -45.060 * ratio * ratio + 30.354 * ratio + 94.845;

        // Clamp to valid range
        if (spo2 < 0) spo2 = 0;
        if (spo2 > 100) spo2 = 100;

        return (float)spo2 spo2BIAS;
    }
}

#endif // PULSE_H