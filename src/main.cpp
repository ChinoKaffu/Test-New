#include <define.h>
// put other includes here
#include <error.h>
#include <temp.h>
#include <pulse.h>
#include <height.h>

void setup() {
    Serial.begin(115200);

    // Initialize Pulse Oximeter
    pulse::setup(); 
    delay(100);

    // Initialize MLX90614 Temperature Sensor
    temp::setup();  
    delay(100);
}

void loop() {
  pox.update();
  
  if (millis() - lastPrintTime >= printInterval) {
        // Print the sensor data
        printf("\tHeight: %.2f cm", height::get());
        printf("\tTemp: %.2f *C", temp::get());
        printf("\tHeart Rate: %.2f BPM", pulse::getRate());
        printf("\tSpO2: %.2f%%\n", pulse::getOxy());
        // printf("\tWeight: ## kg\n");

        lastPrintTime = millis();  // Update the last print time
    }
}