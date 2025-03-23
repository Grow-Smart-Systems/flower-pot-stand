#pragma once

#include "../BaseSensor.h"


/// @brief Базовый класс для всех датчиков температуры
class TemperatureSensor : public BaseSensor
{
public:
    /// @brief Конструктор по умолчанию
    TemperatureSensor() = default;

    /// @brief Деструктор по умолчанию
    ~TemperatureSensor() = default;

    /// @brief Получение температуры
    /// @return Температура в градусах Цельсия
    virtual float GetTemperature() = 0;

    /// @brief Получение влажности
    /// @return Влажность в процентах
    virtual float GetHumidity() = 0;

    /// @brief Установка данных в контейнер
    /// @param container Контейнер данных
    void SetDataIn(SensorsDataContainer& container) override;
};
