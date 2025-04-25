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
    Wire.begin(SCL,SDA);
    errorSetup();
    scanI2CDevices();  // Uncomment to scan for I2C devices

    //Initialize ESP-WEB connection
    //espweb::setup();

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
    // Update all sensors
    height::update();    weight::update();     webSocket.loop();
    
    if (millis() - lastPrintTime >= printInterval) {

        gatherData( // Store readings in variables (single call to each getter)
            height::get(),temp::get(),pulse::getRate(),
            pulse::getOxy(),weight::get() weightBIAS,
            weight::get() / pow(height::get() / 100.0, 2)
            );
        pulseoxyTest(pulse::getRate(),pulse::getOxy());
        

        // Serial monitor display
        printf("\tHeight: %.2f cm\tTemp: %.2f°C\tHeart Rate: %.2f BPM\tSpO2: %.0f %%\tWeight: %.2f kg \tBMI: %.2f\n",
        heightValue, tempValue, heartRate, spO2, weightValue, bmiValue);
        // Pass variables to web server
        //espweb::send(heightValue, tempValue, heartRate, spO2, weightValue, bmiValue);
        lastPrintTime = millis();
    }
        
    //checkI2C();
    //checkManualReset();
}