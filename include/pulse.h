#include <Wire.h>
#include <MAX30100_PulseOximeter.h>
#include <MAX30100.h>

#define REPORTING_PERIOD_MS     1000
#define AVERAGE_OVER            5

PulseOximeter pox;
uint32_t tsLastReport = 0;

namespace pulse {

    // initializes the sensor
    void setup() {
        //pulsei2c.begin(pulseSDA,pulseSCL);
        if (!pox.begin()) {
            Serial.println("ERROR: Failed to initialize pulse oximeter");
            errorWarn();
        }
    }

    float getRate(){
        return pox.getHeartRate();
    }

    float getOxy(){
        return pox.getSpO2();
    }
    
    float getAveragedHeartRate() {
        static float hrSum = 0;
        static int count = 0;

        hrSum += pox.getHeartRate();
        count++;

        if (count >= AVERAGE_OVER) {
            float avgHR = hrSum / count;
            hrSum = 0;
            count = 0;
            return avgHR;
        }
        return -1; // Indicate not enough data yet
    }

    // test func that returns hr and spo2
    void loop() {
        // Make sure to call update as fast as possible
        pox.update();

        if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
            Serial.print("Heart Rate: ");
            Serial.print(getAveragedHeartRate());
            Serial.print(" BPM");


            Serial.print("\t\tSpO2: ");
            Serial.print(pox.getSpO2());
            Serial.println("%");

            tsLastReport = millis();
        }
    }
}