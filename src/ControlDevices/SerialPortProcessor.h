#pragma once

#include <Arduino.h>


/// @brief Класс обработки команд серийного порта
class SerialPortProcessor final
{
public:
    /// @brief Конструктор по умолчанию
    SerialPortProcessor() = default;

    /// @brief Деструктор по умолчанию
    ~SerialPortProcessor() = default;

    /// @brief Обработка команды
    /// @param command Команда
    void process(const String& command);

private:
    /// @brief Обработка команд перемещения
    /// @param command Команда
    /// @return true - команда обработана, false - команда не обработана
    bool processMovementCommands(const String& command);
};

