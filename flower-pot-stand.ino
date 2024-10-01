#include "src/OLED/OLED.h"
#include "src/Sensors/SensorData.h"
#include "src/Utils/Timer.h"
#include "src/Utils/Debug.h"

/// ===== define ===== //

// ARDUINO LED
#define PIN_LED 13

/// ===== globals ===== //

OLED _screen;
SensorsData _data;
Timer _globalTimer;
Debug* _debug = nullptr;

// ===== functions ===== //

void setup(void) 
{
  // Serial
  _debug = Debug::getInstance(Debug::Baudrate::Baud9600);
  _debug->printLine("Start program!");

  // OLED
  if(_screen.init())
    _debug->printLine("OLED init success!");
  else
    _debug->printLine("OLED init failed!");
  _screen.printInitializeScreen();

  //pinMode(PIN_LED, OUTPUT);

  _globalTimer.start(2000);
}

void loop(void) 
{
  if(_globalTimer.ready())
  {
    Serial.println(F("Data update!"));
    // Обновим данные от сенсоров
    _data.update(); 
    _screen.printAllData(_data);
  }
}


