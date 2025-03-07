#include <define.h>
// put other includes here
#include <error.h>
#include <temp.h>
#include <pulse.h>
#include <height.h>
//#include <weight.h>

void setup() {
    Serial.begin(115200);
    Wire.begin();
    scanI2CDevices();

    // Initialize HCSR04 Ranging Sensor functions
    height::setup();

    // Initialize MLX90614 Temp Sensor
    temp::setup(); //0x57

    // Initialize MAX30100 Pulse Oximeter
    pulse::setup();  //0x5A

    // Initialize HX711 Weight Sensor
    //weight::setup();
}

void loop() {
  // these functions are passive and has to run as fast as possible
  pox.update();
  height::update();


  if (millis() - lastPrintTime >= printInterval) {
        // Print the sensor data
        Serial.print("\tHeight: " + String     (height::get(),2) + " cm  ");
        Serial.print("\tTemp: " + String       (temp  ::get(), 2) + "°C ");
        Serial.print("\tHeart Rate: " + String (pulse ::getRate(), 2) + " BPM\t");
        Serial.println("\tSpO2: " + String     (pulse ::getOxy()) + " %\t");
        //Serial.println("\tWeight: " + String(weight::get(), 2) + " kg");    

        lastPrintTime = millis();  // Update the last print time
    }
    
    
    checkI2C();
}