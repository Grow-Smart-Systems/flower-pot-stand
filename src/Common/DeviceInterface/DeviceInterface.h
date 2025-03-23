#pragma once

#include <Arduino.h>

#include "../../Utils/Timer.h"


/// @brief Абстрактный класс для всех устройств
class DeviceInterface
{
public:
    /// @brief Конструктор
    DeviceInterface() = default;

    /// @brief Деструктор
    virtual ~DeviceInterface() = default;

    /// @brief Итератор цикла
    virtual void LoopIteration() = 0;

    /// @brief Запуск таймеров
    virtual void StartTimers() = 0;

private:
    /// @brief Конструктор копирования
    /// @param other Другой объект
    DeviceInterface(const DeviceInterface&) = delete;

    /// @brief Оператор присваивания
    /// @param other Другой объект
    DeviceInterface& operator=(const DeviceInterface&) = delete;
};