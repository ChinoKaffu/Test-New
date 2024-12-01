#include <HX711.h>

HX711 scale;

namespace weight {

    // initialize HX711
    void setup() {
        scale.begin(weightDT, weightSCK);
        if (!scale.is_ready()) {
            Serial.println("Error connecting to HX711 Weight sensor. Check wiring.");
            errorWarn();
        }
        scale.tare();
        printf("Weight sensor initialized! \n");
    }

    long get(){
        return scale.read();
    }

    void calibrate() {
        Serial.println("HX711 calibration starting...");
        Serial.println("Remove all weight from the scale");
        delay(5000);  // Give time to remove weight
        
        Serial.println("Taring...");
        scale.tare();  // Reset scale to zero
        
        Serial.println("Place known weight on scale (e.g., 1kg)");
        delay(5000);  // Give time to place weight
        
        long reading = scale.get_value(10);  // Average of 10 readings
        
        Serial.print("Raw value for known weight: ");
        Serial.println(reading);
        
        // Calculate calibration factor
        // Known weight in grams divided by raw reading
        // Example: float calibration_factor = 1000.0 / reading;  // for 1kg weight
        
        Serial.println("Calibration complete");
        Serial.println("Use the raw reading to calculate your calibration factor");
    }
}



