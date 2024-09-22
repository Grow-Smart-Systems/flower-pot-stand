#pragma once

#include <U8glib.h>
#include "src/Sensors/SensorData.h"

// SSD1306 OLED
#define TEXT_STRING_0 10
#define TEXT_STRING_1 20
#define TEXT_STRING_2 30
#define TEXT_STRING_3 40
#define TEXT_STRING_4 50
#define TEXT_STRING_5 60

class SensorsData;

class OLED 
{
    public:
        OLED::OLED();
        OLED::~OLED() = default;
        void printInitializeScreen();
        void printAllData(const SensorsData& data);

    private:
        U8GLIB_SSD1306_128X64 _u8g;
};