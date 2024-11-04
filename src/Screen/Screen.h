#pragma once

#include <Arduino.h>
#include <memory>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "../Sensors/SensorData.h"
#include "../Common/Data.h"
#include "Menu.h"

class SensorsData;
class Display;
class Menu;

class Screen
{
public:
    Screen();

    ~Screen() = default;

    /// @brief Инициализация экрана
    /// @return true - успешно, false - ошибка
    bool init();

    void initMenu();

    void printInitializeScreen();

    void printMenu();

    void showMenu();

    // move menu
    void movemenuUp();

    void movemenuDown();

    void movemenuBack();

    void movemenuEnter();

    std::shared_ptr<Display> getDisplay() const { return _display; }

private:
    /// @brief Экземпляр дисплея объекта для SSD1306 с разрешением 128x64, с использованием аппаратного I2C.
    std::shared_ptr<Display> _display{ nullptr };

    std::shared_ptr<Menu> _menu{ nullptr };
};