#pragma once

#include <Arduino.h>
#include <memory>

#include "SerialPortProcessor.h"
#include "AdKeyboardDevice.h"
#include "../Utils/Timer.h"


class ControlDevices final
{
    using Buttons = AdKeyboardDevice::Buttons;

public:
    ControlDevices();
    ~ControlDevices() = default;

    void LoopIteration();

private:
    std::shared_ptr<SerialPortProcessor> _serialPortProcessor;
    std::shared_ptr<AdKeyboardDevice> _keyboard;
    Timer _keyboardTimer;
};
