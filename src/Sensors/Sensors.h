#pragma once

#include <memory>
#include "../Common/DeviceInterface/DeviceInterface.h"
#include "SensorsConfiguration.h"
#include "LightSensors/LightSensor.h"
#include "TemperatureSensors/TemperatureSensor.h"
#include "../Common/Containers/SensorsDataContainer.h"

class LightSensor;
class TemperatureSensor;


/// @brief Класс управления сенсорами
class Sensors final : public DeviceInterface
{
public:
    /// @brief Конструктор
    Sensors();

    /// @brief Деструктор
    ~Sensors();

    /// @brief Итератор цикла
    void LoopIteration() override;

    /// @brief Запуск таймеров
    void StartTimers() override;

    /// @brief Получение информации о сенсорах
    /// @return Контейнер данных сенсоров
    const SensorsDataContainer& GetSensorInfo();

protected:
    /// @brief Обновление данных сенсоров
    void update();

private:
    /// @brief Контейнер данных сенсоров
    SensorsDataContainer _dataContainer;

    /// @brief Сенсор освещенности
    std::shared_ptr<LightSensor> _lightSensor;

    /// @brief Сенсор температуры
    std::shared_ptr<TemperatureSensor> _temperatureSensor;

    /// @brief Таймер обновления данных сенсоров
    Timer _sensorsTimer;
};