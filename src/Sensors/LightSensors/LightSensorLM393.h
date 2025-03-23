#pragma once

#include "LightSensor.h"


/// @brief Класс датчика освещенности LM393
class LightSensorLM393 final : public LightSensor
{
public:
    /// @brief Конструктор
    LightSensorLM393();

    /// @brief Деструктор
    ~LightSensorLM393() = default;

    /// @brief Получение коэффициента освещенности
    /// @return Коэффициент освещенности
    uint16_t GetLightCoef() override;

    /// @brief Установка данных в контейнер
    /// @param container Контейнер данных
    void SetDataIn(SensorsDataContainer& container) override;
};
