#pragma once

#include <DHT.h>
#include "TemperatureSensor.h"

#define PIN_TEMPERATURE_SENSOR GPIO33
#define DHTTYPE DHT11


/// @brief Класс датчика температуры DHT11
class TemperatureSensorDHT11 final : public TemperatureSensor
{
public:
    /// @brief Конструктор
    TemperatureSensorDHT11();

    /// @brief Деструктор
    ~TemperatureSensorDHT11() = default;

    /// @brief Получение температуры
    /// @return Температура в градусах Цельсия
    float GetTemperature() override;

    /// @brief Получение влажности
    /// @return Влажность в процентах
    float GetHumidity() override;

private:
    /// @brief Объект датчика DHT
    DHT _dht;
};
