#pragma once

#include <Arduino.h>


/// @brief Класс таймера.

class Timer 
{
public:
    /// @brief Конструктор по умолчанию.
    Timer();

    /// @brief Конструктор с параметром.
    /// @param ms_period Период таймера в миллисекундах.
    /// @details После создания таймер сразу запускается.
    Timer(uint32_t ms_period);

    /// @brief Запуск таймера с указанием периода в миллисекундах.
    void start(uint32_t ms_period);

    /// @brief Запуск таймера.
    /// @details Период таймера остается прежним.
    void start();

    /// @brief Остановка таймера.
    void stop();

    /// @brief Проверка таймера.
    /// @return true - таймер сработал, false - таймер еще не сработал.
    bool ready();

private:

    /// @brief Переменная для хранения значения таймера.
    /// @details Используется для отслеживания времени в миллисекундах.
    uint32_t _timer {0};

    /// @brief Переменная для хранения периода таймера.
    /// @details Используется для определения времени, через которое таймер считается готовым.
    uint32_t _period {0};
};

/** @example пример использования:
 Timer tmr1(1000);
 Timer tmr2;
 void setup() {
   Serial.begin(9600);
   tmr2.start(2000);
 }
 void loop() {
   if (tmr1.ready()) Serial.println("timer 1!");
   if (tmr2.ready()) Serial.println("timer 2!");
 }
 **/