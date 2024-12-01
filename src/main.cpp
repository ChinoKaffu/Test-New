#include <define.h>
// put other includes here
#include <error.h>
#include <temp.h>
#include <pulse.h>
#include <height.h>
#include <weight.h>

void setup() {
    Serial.begin(115200);
    Wire.begin();
    scanI2CDevices();

    // Initialize MLX90614 Temp Sensor
    temp::setup(); //0x57
    delay(100);

    // Initialize MAX30100 Pulse Oximeter
    pulse::setup();  //0x5A
    delay(100);

    // Initialize HX711 Weight Sensor
    weight::setup();
    delay(100);
}

void loop() {
  pox.update();
  
  if (millis() - lastPrintTime >= printInterval) {
        // Print the sensor data
        printf("\tHeight: %.2f cm  ", height::get());
        printf("\tTemp: %.2f°C  ", temp::get());
        printf("\tHeart Rate: %.2f BPM\tSpO2: %.2f%%  ", pulse::getRate(),pulse::getOxy());
        printf("\tWeight: %.2f kg\n",weight::get());    

        lastPrintTime = millis();  // Update the last print time
    }
    checkI2C();
}