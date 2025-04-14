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
    errorSetup();
    scanI2CDevices();

    // Initialize HX711 Weight Sensor
    weight::setup();

    // Initialize HCSR04 Ranging Sensor functions
    height::setup();

sa_handler
FUNC_SD_DATA0_SD_DATA0asd
asd
sa_handlera
ASSERT_IF_DPORT_REGas
asctime


a64lAA
a64l Temp Sensor
a64la





















aaaaaaaaaaaaaaaaaaaaaaaaa
ravendavid





















      temp::setup(); //0x57

    // Initialize MAX30100 Pulse Oximeter
    pulse::setup();  //0x5A

}

void loop() {       
    {
        pox.update();   height::update();   weight::update();

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