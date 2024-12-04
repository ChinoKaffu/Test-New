#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(
            ULTRASONIC_TRIGGER, 
            ULTRASONIC_ECHO
        );


namespace height {
    volatile float heightNow = 0;
    volatile float storedHeight;  // Declare as volatile to be used in ISR
    volatile unsigned long lastInterruptTime = 0;  // Track the last interrupt time
    const unsigned long debounceDelay = 300;  // Debounce delay in milliseconds (adjust as needed)

    float update() {
        static unsigned long lastUpdate = 0;
        unsigned long currentTime = millis();
        
        if (currentTime - lastUpdate >= 500) {
            heightNow = distanceSensor.measureDistanceCm();
            lastUpdate = currentTime;
        }
        return heightNow;
    }

    float get(){
        return storedHeight - heightNow;
    }

    void IRAM_ATTR buttonISR() {
        unsigned long currentTime = millis();  // Get the current time
        if (currentTime - lastInterruptTime > debounceDelay) {  // Check if debounce time has passed
            storedHeight = heightNow;  // Safely update the height count
            lastInterruptTime = currentTime;  // Update the last interrupt time
        }
    }

    void setup() {
        pinMode(heightReference, INPUT_PULLDOWN);  // Use pulldown or pullup depending on button wiring
        attachInterrupt(digitalPinToInterrupt(heightReference), buttonISR, RISING);  // Trigger on rising edge
    }
}
