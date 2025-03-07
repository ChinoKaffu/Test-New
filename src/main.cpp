#include <define.h>
// put other includes here
#include <error.h>
#include <temp.h>
#include <pulse.h>
#include <weight.h>
#include <height.h>

void setup() {
    Serial.begin(115200);
    Wire.begin();
    scanI2CDevices();

    // Initialize HCSR04 Ranging Sensor functions
    //height::setup();

    // Initialize MLX90614 Temp Sensor
    //temp::setup(); //0x57

    // Initialize MAX30100 Pulse Oximeter
    pulse::setup();  //0x5A

    // Initialize HX711 Weight Sensor
    weight::setup();
}

float tall;
void loop() {       
    {
        pox.update();
        //height::update();

        if (millis() - lastPrintTime >= printInterval) {
            tall = height::get();
            // Print the sensor data
            //Serial.print("\tHeight: " + String(tall, 2) + " cm  ");
            //Serial.print("\tTemp: " + String(temp::get(), 2) + "°C ");
            Serial.print("\tHeart Rate: " + String(pulse::getRate(), 2) + " BPM\t");
            Serial.print("\tSpO2: " + String(pulse::getOxy()) + " %\t");
            Serial.print("\tWeight: " + String(weight::get(), 2) + " kg\n");    
            //Serial.println("\tBMI: " + String(weight::get() / tall*tall, 2));

            lastPrintTime = millis();  // Update the last print time
        }
        //checkI2C();
    }
    
}