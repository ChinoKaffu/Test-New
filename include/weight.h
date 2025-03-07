#include <HX711_ADC.h>
#include <EEPROM.h>

//pins:
const int HX711_dout = weightDT;
const int HX711_sck = weightSCK;

//HX711 constructor:
HX711_ADC LoadCell(HX711_dout, HX711_sck);

const int calVal_eepromAdress = 0;
unsigned long t = 0;

namespace weight{

  void setup() {
    LoadCell.begin();
    float calibrationValue;
    EEPROM.begin(512);
    EEPROM.get(calVal_eepromAdress, calibrationValue);
    unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
    boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
    LoadCell.start(stabilizingtime, _tare);
  }

  float get(){
    LoadCell.update();
    return LoadCell.getData()/22.2222/1000;
  }
}






