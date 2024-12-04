#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(
            ULTRASONIC_TRIGGER, 
            ULTRASONIC_ECHO
        );
volatile float storedHeight = 0;

namespace height {

    float get(){
        return distanceSensor.measureDistanceCm();
    }

    void IRAM_ATTR buttonISR() {
        storedHeight = get();
        //Serial.println(storedHeight);
    }

    void setup(){
        pinMode(heightReference, INPUT);
        attachInterrupt(heightReference, buttonISR, RISING);
    }

    // test func that displays detected distance continously
    void loop() {
        // Print the distance values
        printf("Distance (cm): {%.2f}\n", distanceSensor.measureDistanceCm());
        delay(1000); // Wait 1 second before next measurement
    }
}