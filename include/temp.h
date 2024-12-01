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
        if (mlx.readEmissivity() != emissivity) { // Allow for small floating point differences
            mlx.writeEmissivity(emissivity);
        }
        printf("Temp sensor initialized! \n");
    }

    double get(){
        return mlx.readObjectTempC();
    }
    // Test func that returns ambient and read temp in C and F
    void getTemp() {
        Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
        Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
        //Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
        //Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
    }
}