#include "src/OLED/OLED.h"
#include "src/Sensors/SensorData.h"
#include "src/Utils/Timer.h"

/// ===== define ===== //

// ARDUINO LED
#define PIN_LED 13

/// ===== globals ===== //

OLED _screen;

SensorsData _data;

Timer _globalTimer;

// ===== functions ===== //

void setup(void)
{
  Serial.begin(9600);
  Serial.println(F("Start!"));

  // OLED
  _screen.init();
  _screen.printInitializeScreen();

  // pinMode(PIN_LED, OUTPUT);

  _globalTimer.start(2000);
}

void loop(void)
{
  if (_globalTimer.ready())
  {
    // Обновим данные от сенсоров
    _data.update();
    _screen.printAllData(_data);
  }
}
