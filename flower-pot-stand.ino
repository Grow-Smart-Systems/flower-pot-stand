#include "src/OLED/OLED.h"

#include "src/Sensors/SensorData.h"

/// ===== define ===== //

// ARDUINO LED
#define PIN_LED 13

/// ===== globals ===== //

OLED _screen;

SensorsData _data = SensorsData();

// ===== functions ===== //

void setup(void) 
{
  Serial.begin(9600);
  Serial.println(F("Start!"));

  // OLED
  _screen.printInitializeScreen();

  //pinMode(PIN_LED, OUTPUT);

  delay(2000);
}

void loop(void) 
{
  // Обновим данные от сенсоров
  _data.update();

  // picture loop  
  _screen.printAllData(_data);
  
  // rebuild the picture after some delay
  delay(2000);
}


