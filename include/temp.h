#include <Adafruit_MLX90614.h>
#include <SPI.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

namespace temp {

    // Initialize the sensor
    void setup() {
        if (!mlx.begin()) {
            Serial.println("Error connecting to MLX sensor. Check wiring.");
            errorWarn();
        }

        printf("Temp sensor initialized! \n");
    }

    double get(){
        return mlx.readObjectTempC() tempBIAS;
    }
}