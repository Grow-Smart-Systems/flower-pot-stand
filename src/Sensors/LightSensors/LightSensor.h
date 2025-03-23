#pragma once

#include "../BaseSensor.h"


/// @brief Базовый класс для всех датчиков освещенности
class LightSensor : public BaseSensor
{
public:
    /// @brief Конструктор по умолчанию
    LightSensor() = default;

    /// @brief Деструктор по умолчанию
    ~LightSensor() = default;

    /// @brief Получение коэффициента освещенности
    /// @return Коэффициент освещенности
    virtual uint16_t GetLightCoef() = 0;

    /// @brief Установка данных в контейнер
    /// @param container Контейнер данных
    void SetDataIn(SensorsDataContainer& container) override;
};
