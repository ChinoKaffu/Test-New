#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(
            ULTRASONIC_TRIGGER, 
            ULTRASONIC_ECHO
        );


namespace height {

    float get(){
        return distanceSensor.measureDistanceCm();
    }
    // test func that displays detected distance continously
    void loop() {
        // Print the distance values
        printf("Distance (cm): {%.2f}\n", distanceSensor.measureDistanceCm());
        delay(1000); // Wait 1 second before next measurement
    }
}