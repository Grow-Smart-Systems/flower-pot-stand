#include <Arduino.h>
#include <memory>

#include "src/Screen/Screen.h"
#include "src/Sensors/SensorData.h"
#include "src/Utils/Timer.h"
#include "src/Common/Data.h"
#include "src/ControlDevices/SerialPortProcessor.h"

/// ===== define ===== //

// ARDUINO LED
#define PIN_LED 13

/// ===== globals ===== //

// Screen _screen;

// SensorsData _data;
Data& data = Data::getInstance();

SerialPortProcessor _serialPortProcessor;

Timer _sensorsTimer;
Timer _screenTimer;

// ===== functions ===== //

void setup(void)
{
    Serial.begin(115200);
    Serial.println(F("Start!"));

    // OLED
    Serial.println(F("Initialize Screen ..."));
    std::shared_ptr<Screen> _screen = std::make_shared<Screen>();
    data.setScreen(_screen);
    if (!data.getScreen()->init())
    {
        Serial.println(F("Error: Display initialization failed"));
        return;
    }
    data.getScreen()->printInitializeScreen();
    Serial.println(F("Screen initialized!"));
    //

    // Sensors
    std::shared_ptr<SensorsData> _sensorsData = std::make_shared<SensorsData>();
    data.setSensorsData(_sensorsData);

    //pinMode(PIN_LED, OUTPUT);

    delay(3000);
    Serial.println(F("Start menu ..."));
    _sensorsTimer.start(2000);
    _screenTimer.start(500);
}

void loop(void)
{
    if (_sensorsTimer.ready())
    {
        // Обновим данные от сенсоров
        data.getSensorsData()->update();
    }

    if (_screenTimer.ready())
    {
        // Обновим экран
        data.getScreen()->printMenu();
    }

    if (Serial.available())
    {
        _serialPortProcessor.process(Serial.readString());
    }
}
