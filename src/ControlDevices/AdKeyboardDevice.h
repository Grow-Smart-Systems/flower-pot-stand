#pragma once

#include <Arduino.h>
#include "../ESP32_defines.h"

#define KEYS_COUNT 5
#define KEYBOARD_PIN GPIO32


/// @brief Класс управления клавиатурой
class AdKeyboardDevice final
{
    /// @brief Массив значений кнопок
    const int _buttonValues[KEYS_COUNT] = {50, 500, 1200, 2000, 2800};

public:
    /// @brief Перечисление кнопок
    enum class Buttons
    {
        UNDEFINED = -1, // Неопределенная кнопка
        BUTTON_1 = 0,   // Кнопка 1
        BUTTON_2 = 1,   // Кнопка 2
        BUTTON_3 = 2,   // Кнопка 3
        BUTTON_4 = 3,   // Кнопка 4
        BUTTON_5 = 4    // Кнопка 5
    };

    /// @brief Конструктор по умолчанию
    AdKeyboardDevice() = default;

    /// @brief Деструктор по умолчанию
    ~AdKeyboardDevice() = default;

    /// @brief Чтение кнопок
    /// @return Кнопка
    Buttons readButtons();

private:
    /// @brief Получение индекса кнопки
    /// @param value Значение кнопки
    /// @return Индекс кнопки
    int getKey(int value);

    /// @brief Последняя нажатая кнопка
    Buttons _lastButton {Buttons::UNDEFINED};

    /// @brief Время последнего нажатия
    unsigned long _lastPressTime {0};

    /// @brief Время антидребезга
    const unsigned long _debounceDelay {500};
};