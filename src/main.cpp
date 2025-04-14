#include <define.h>
// put other includes here
#include <error.h>
#include <temp.h>
#include <pulse.h>
#include <weight.h>
#include <height.h>
#include <espweb.h>

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

// Global variables to store sensor readings
float heightValue = 0;
float tempValue = 0;
float heartRate = 0;
float spO2 = 0;
float weightValue = 0;
float bmiValue = 0;

void loop() {
    // Update all sensors
    pox.update();    height::update();    weight::update();     webSocket.loop();
    
    // Store readings in variables (single call to each getter)
    
    
    if (millis() - lastPrintTime >= printInterval) {
        // Print using stored variables
        heightValue = height::get();
        tempValue = temp::get();
        heartRate = pulse::getRate();
        spO2 = pulse::getOxy();
        weightValue = weight::get();
        bmiValue = weightValue / pow(heightValue / 100.0, 2);
        
        Serial.print("\tHeight: " + String(heightValue, 2) + " cm  ");
        Serial.print("\tTemp: " + String(tempValue, 2) + "°C ");
        Serial.print("\tHeart Rate: " + String(heartRate, 2) + " BPM\t");
        Serial.print("\tSpO2: " + String(spO2) + " %\t");
        Serial.print("\tWeight: " + String(weightValue, 2) + " kg\t");    
        Serial.println("\tBMI: " + String(bmiValue, 2));
    

        // Pass same variables to web server
        espweb::send(heightValue, tempValue, heartRate, spO2, weightValue, bmiValue);
        
        lastPrintTime = millis();
    }

        
    checkI2C();
    checkManualReset();
}
