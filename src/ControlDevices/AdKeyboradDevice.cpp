#include "AdKeyboradDevice.h"

AdKeyboardDevice::Buttons AdKeyboardDevice::readButtons()
{
    int value = analogRead(KEYBOARD_PIN);
    unsigned long currentTime = millis();
    if (value < 3000)
    {
        auto button = Buttons(getKey(value));
        if (button != Buttons::UNDEFINED)
        {
            if (button != _lastButton || (currentTime - _lastPressTime) > _debounceDelay)
            {
                _lastButton = button;
                _lastPressTime = currentTime;
                return button;
            }
        }
    }
    return Buttons::UNDEFINED;
}

int AdKeyboardDevice::getKey(int value)
{
    for (int i = 0; i < KEYS_COUNT; ++i)
    {
        //если измеренное значение попало в диапазон между референсными значениями, выводим номер диапазона
        if (value < _buttonValues[i])
            return i;
    }
    return -1;
}
