#include "ControlDevices.h"

ControlDevices::ControlDevices()
{
    _serialPortProcessor = std::make_shared<SerialPortProcessor>();
    _keyboard = std::make_shared<AdKeyboardDevice>();
    _keyboardTimer.start(100);
}

void ControlDevices::LoopIteration()
{
    if (_keyboardTimer.ready())
    {
        // Обработаем нажатия клавиш
        AdKeyboardDevice::Buttons key = _keyboard->readButtons();

        // TODO: 1. Не совмем удачное решение использовать процессор серийного порта, но пока так
        // TODO: 2. Нужно отладить с настоящим устройством, кнопки могут работать не так как ожидается
        switch (key)
        {
        case AdKeyboardDevice::Buttons::BUTTON_1:
            _serialPortProcessor->process("BACK");
            break;
        case AdKeyboardDevice::Buttons::BUTTON_2:
            _serialPortProcessor->process("UP");
            break;
        case AdKeyboardDevice::Buttons::BUTTON_3:
            _serialPortProcessor->process("DOWN");
            break;
        case AdKeyboardDevice::Buttons::BUTTON_4:
            _serialPortProcessor->process("ENTER");
            break;
        case AdKeyboardDevice::Buttons::BUTTON_5:
            break;
        default:
            break;
        }
    }

    if (Serial.available())
    {
        _serialPortProcessor->process(Serial.readString());
    }
}

