#pragma once

#include <Arduino.h>

#include "../Common/Containers/SensorsDataContainer.h"

/// @brief Виртуальный базовый класс для всех сенсоров
class BaseSensor
{
public:
    /// @brief Конструктор
    BaseSensor() = default;

    /// @brief Деструктор
    virtual ~BaseSensor() = default;

    /// @brief Установка данных в контейнер
    /// @param data Контейнер данных
    virtual void SetDataIn(SensorsDataContainer& container) = 0;
};