#pragma once 

#include <Arduino.h>
#include <memory>
#include <vector>

#include "DeviceInterface.h"


/// @brief Класс контроллера интерфейса устройств
class DeviceInterfaceController final
{
public:
    /// @brief Конструктор
    DeviceInterfaceController() = default;

    /// @brief Деструктор
    ~DeviceInterfaceController() = default;

    /// @brief Добавление устройства
    /// @param device Устройство
    void AddDevice(std::shared_ptr<DeviceInterface> device);

    /// @brief Выполнение итерацию цикла для всех устройств
    void MakeLoopIterations();

    /// @brief Запуск таймеров для всех устройств
    void StartTimers();

private:
    /// @brief Вектор устройств
    std::vector<std::shared_ptr<DeviceInterface>> _devices;
};