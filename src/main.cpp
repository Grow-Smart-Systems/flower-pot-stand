#include <Arduino.h>
#include <memory>

#include "Screen/Screen.h"
#include "Sensors/SensorData.h"
#include "Utils/Timer.h"
#include "Common/Data.h"
#include "ControlDevices/ControlDevices.h"

/// ===== define ===== //
/// ===== globals ===== //

Data& data = Data::getInstance();

ControlDevices _controlDevices;

Timer _sensorsTimer;
Timer _screenTimer;

// ===== functions ===== //

void setup(void)
{
    Serial.begin(115200);
    Serial.println(F("Start!"));

    // OLED
    Wire.begin(SDA, SCL);
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

    _controlDevices.LoopIteration();
}
