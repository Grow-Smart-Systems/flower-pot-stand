#include "src/Screen/Screen.h"
#include "src/Sensors/SensorData.h"
#include "src/Utils/Timer.h"

/// ===== define ===== //

// ARDUINO LED
#define PIN_LED 13

/// ===== globals ===== //

Screen _screen;

SensorsData _data;

Timer _sensorsTimer;
Timer _screenTimer;

// ===== functions ===== //

void setup(void)
{
    Serial.begin(9600);
    Serial.println(F("Start!"));

    // OLED
    _screen.init();
    _screen.printInitializeScreen();

    //pinMode(PIN_LED, OUTPUT);

    _sensorsTimer.start(2000);
    _screenTimer.start(500);
}

void loop(void)
{
    if (_sensorsTimer.ready())
    {
        // Обновим данные от сенсоров
        _data.update();
    }

    if (_screenTimer.ready())
    {
        // Обновим экран
        _screen.printMenu();
    }
}
