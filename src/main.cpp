#include <Arduino.h>
#include <memory>

#include "Screen/Screen.h"
#include "Sensors/Sensors.h"
#include "ControlDevices/ControlDevices.h"

#include "Utils/Timer.h"

#include "Common/Data.h"


/// ===== define ===== //
/// ===== globals ===== //

Data& data = Data::GetInstance();

Timer _sensorsTimer;
Timer _screenTimer;

// ===== functions ===== //

void setup(void)
{
    Serial.begin(115200);
    Serial.println(F("Start!"));

    // Screen
    Wire.begin(SDA, SCL);
    Serial.println(F("Initialize Screen ..."));
    std::shared_ptr<Screen> _screen = std::make_shared<Screen>();
    data.SetScreen(_screen);
    if (!data.GetScreen()->Init())
    {
        Serial.println(F("Error: Display initialization failed"));
        return;
    }
    data.GetScreen()->PrintInitializeScreen();
    Serial.println(F("Screen initialized!"));
    //

    // Sensors
    std::shared_ptr<Sensors> _sensors = std::make_shared<Sensors>();
    data.SetSensors(_sensors);

    // Control devices
    std::shared_ptr<ControlDevices> _controlDevices = std::make_shared<ControlDevices>();
    data.SetControlDevices(_controlDevices);
    //

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
        data.GetSensors()->Update();
    }

    if (_screenTimer.ready())
    {
        // Обновим экран
        data.GetScreen()->PrintMenu();
    }
    data.GetControlDevices()->LoopIteration();
}


/// TODOLIST:
// 1. Сделать абстрактный класс для всех классов интерфейсов (Sensors, ControlDevices, Screen)
// 2. Прописать в этом классе общие методы для всех классов (LoopIteration)
// 3. В main.cpp созвать вектор с указателями и перебирать его в loop
// 4. Переписать все классы на наследование от абстрактного класса и прописать у каждого свой метод LoopIteration
// 5. Перенести все таймеры в свои классы и использовать их в LoopIteration
// -------------------
// 6. Продумать и приступить к реализации класса для обработки данных с датчиков и управления устроством (Статусами)