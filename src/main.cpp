#include <Arduino.h>
#include <memory>

#include "Screen/Screen.h"
#include "Sensors/SensorData.h"
#include "Utils/Timer.h"
#include "Common/Data.h"
#include "ControlDevices/ControlDevices.h"

#include "esp_system.h"

/// ===== define ===== //
/// ===== globals ===== //

Data& data = Data::getInstance();

ControlDevices _controlDevices;

Timer _sensorsTimer;
Timer _screenTimer;

// ===== functions ===== //

void printMemoryInfo()
{
    // Получение информации о свободной памяти
    multi_heap_info_t heap_info;
    heap_caps_get_info(&heap_info, MALLOC_CAP_DEFAULT);

    Serial.println("====================================");
    Serial.println("Memory Info:");
    Serial.print("Total free bytes: ");
    Serial.println(heap_info.total_free_bytes);
    Serial.print("Total allocated bytes: ");
    Serial.println(heap_info.total_allocated_bytes);
    Serial.print("Largest free block: ");
    Serial.println(heap_info.largest_free_block);
    Serial.print("Minimum free bytes ever: ");
    Serial.println(heap_info.minimum_free_bytes);
    Serial.print("Number of free blocks: ");
    Serial.println(heap_info.free_blocks);
    Serial.print("Number of allocated blocks: ");
    Serial.println(heap_info.allocated_blocks);
    Serial.println("====================================");
}

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
