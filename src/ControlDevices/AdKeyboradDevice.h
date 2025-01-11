#pragma once

#include <Arduino.h>
//#include <Wire.h>
#include "../ESP32_defines.h"

#define KEYS_COUNT 5
#define KEYBOARD_PIN GPIO32


class AdKeyboardDevice
{

    const int _buttonValues[KEYS_COUNT] = { 50, 500, 1200, 2000, 2800 };

public:
    enum class Buttons
    {
        UNDEFINED = -1,
        BUTTON_1 = 0,
        BUTTON_2 = 1,
        BUTTON_3 = 2,
        BUTTON_4 = 3,
        BUTTON_5 = 4
    };

    AdKeyboardDevice() = default;
    ~AdKeyboardDevice() = default;

    Buttons readButtons();

private:
    int getKey(int value);

    Buttons _lastButton{ Buttons::UNDEFINED };

    unsigned long _lastPressTime{ 0 };

    // Задержка для устранения дребезга
    const unsigned long _debounceDelay{ 1000 };

};