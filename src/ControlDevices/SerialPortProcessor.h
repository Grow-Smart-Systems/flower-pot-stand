#pragma once

#include <Arduino.h>


class SerialPortProcessor final
{
public:
    SerialPortProcessor() = default;
    ~SerialPortProcessor() = default;

    void process(const String& command);

private:
    bool processMovementCommands(const String& command);
};

