#include <define.h>
// put other includes here
#include <espweb.h>
#include <error.h>
#include <temp.h>
#include <pulse.h>
#include <weight.h>
#include <height.h>

void setup() {
    Serial.begin(serial_speed);
    Wire.begin();
    errorSetup();
    scanI2CDevices();

    //Initialize ESP-WEB connection
    espweb::setup();

    // Initialize HX711 Weight Sensor
    weight::setup();

    // Initialize HCSR04 Ranging Sensor functions
    height::setup();

    // Initialize MLX90614 Temp Sensor
    temp::setup(); //0x57

    // Initialize MAX30100 Pulse Oximeter
    pulse::setup();  //0x5A

}

void loop() {       
    {
        pox.update();   height::update();   weight::update();   espweb::loop();

        if (millis() - lastPrintTime >= printInterval) {
            //Print the sensor data
            Serial.print("\tHeight: " + String(height::get(), 2) + " cm  ");
            Serial.print("\tTemp: " + String(temp::get(), 2) + "°C ");
            Serial.print("\tHeart Rate: " + String(pulse::getRate(), 2) + " BPM\t");
            Serial.print("\tSpO2: " + String(pulse::getOxy()) + " %\t");
            Serial.print("\tWeight: " + String(weight::get(), 2) + " kg\t");    
            Serial.println("\tBMI: " + String(weight::get() / pow(height::get() / 100.0, 2), 2));


            lastPrintTime = millis();  // Update the last print time
        }
        checkI2C(); checkManualReset();
    }
}