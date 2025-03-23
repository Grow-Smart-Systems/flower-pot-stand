#pragma once

#include <Arduino.h>
#include <memory>

#include "../Common/DeviceInterface/DeviceInterface.h"

#include "SerialPortProcessor.h"
#include "AdKeyboardDevice.h"


/// @brief Класс интерфейс устройств управления
class ControlDevices final : public DeviceInterface
{
    using Buttons = AdKeyboardDevice::Buttons;

public:
    /// @brief Конструктор
    ControlDevices();

    /// @brief Деструктор по умолчанию
    ~ControlDevices() = default;

    /// @brief Итератор цикла
    void LoopIteration() override;

    /// @brief Запуск таймеров
    void StartTimers() override;

private:
    /// @brief Обработчик серийного порта
    std::shared_ptr<SerialPortProcessor> _serialPortProcessor;

    /// @brief Обработчик клавиатуры
    std::shared_ptr<AdKeyboardDevice> _keyboard;

    /// @brief Таймер для клавиатуры
    Timer _keyboardTimer;
};
