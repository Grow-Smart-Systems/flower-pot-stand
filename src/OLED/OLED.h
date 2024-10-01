#pragma once

#include <Arduino.h>
#include <U8glib.h>
#include "../Sensors/SensorData.h"

// SSD1306 OLED DEBUG PRINT
#define DEBUG_TEXT_STRING_0 10
#define DEBUG_TEXT_STRING_1 20
#define DEBUG_TEXT_STRING_2 30
#define DEBUG_TEXT_STRING_3 40
#define DEBUG_TEXT_STRING_4 50
#define DEBUG_TEXT_STRING_5 60
#define DEBUG_TEXT_FONT u8g_font_6x10
//

class SensorsData;

class OLED 
{
    public:
        OLED::OLED();
        OLED::~OLED() = default;

        /// @brief Инициализация экрана
        /// @return true - успешно, false - ошибка
        bool init();

        void printInitializeScreen();
        
        void printAllData(const SensorsData& data);

    private:
        /// @brief Экземпляр дисплея U8G2 для SSD1306 с разрешением 128x64, без маркировки, с использованием аппаратного I2C.
        /// @note Если динамической памяти будет не хватать, можно заменить U8G2_SSD1306_128X64_NONAME_1_HW_I2C
        U8GLIB_SSD1306_128X64 _u8g;
};