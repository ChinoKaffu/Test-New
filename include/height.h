#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(
    ULTRASONIC_TRIGGER, 
    ULTRASONIC_ECHO
);

namespace height {
    volatile float heightNow = 0;
    const float referenceHeight = 185.0;  // Fixed reference height in cm

    float update() {
        static unsigned long lastUpdate = 0;
        unsigned long currentTime = millis();
        
        if (currentTime - lastUpdate >= 500) {
            heightNow = distanceSensor.measureDistanceCm();
            lastUpdate = currentTime;
        }
        return heightNow;
    }

    float get() {
        return referenceHeight - heightNow;
    }

    void setup() {
        // Nothing needed here since we don't use interrupts anymore
    }
}
