#include <esp_system.h>
#include <Arduino.h>
#include <Wire.h>

uint8_t i2cDevices[MAX_DEVICES];
uint8_t numDevices = 0;  // Keep track of the number of detected devices

// blink on board led for 3 sec then restart sys
void errorWarn() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.println("!!! ERROR OCCURED! REBOOTING ESP32 !!!");

    unsigned long startTime = millis(); // Record the start time
    
    while (millis() - startTime < 3000) { // Run for 3 seconds (3000ms)
        digitalWrite(LED_BUILTIN, HIGH);
        delay(200);
        digitalWrite(LED_BUILTIN, LOW);
        delay(200);
    }

    esp_restart(); // Restart the ESP32 after 3 seconds
}

//checks status of i2c devices, if an error found, runs errorWarn(), loop end
void checkI2C() {
    if (millis() - lastI2CCheck > checkInterval) {
        for (uint8_t i = 0; i < numDevices; i++) {
        Wire.beginTransmission(i2cDevices[i]);
            if (Wire.endTransmission() != 0) {  // Check for errors
                Serial.print("I2C Error at address 0x");
                Serial.println(i2cDevices[i], HEX);
                errorWarn();  // Handle error if detected
            }
        }
        lastI2CCheck = millis();  // Reset timer
    }
}


//gets all connected i2c devices, setup
void scanI2CDevices() {
    Serial.println();
    byte error;
    numDevices = 0;  // Reset the device count

    // Scan all possible I2C addresses from 0x03 to 0x77
    for (uint8_t i = 3; i < 128; i++) {
        Wire.beginTransmission(i);  // Start transmission to device at address i
        error = Wire.endTransmission();  // End transmission and check for error
        
        if (error == 0) {  // If no error, device found
            if (numDevices < MAX_DEVICES) {
                i2cDevices[numDevices] = i;  // Store the device address
                numDevices++;  // Increment the device count
                Serial.print("I2C device found at address 0x");
                Serial.println(i, HEX);  // Print the address of the device
            }
        }
    }

    // If no devices were found, display a message
    if (numDevices == 0) {
        Serial.println("No I2C devices found.");
    }
}