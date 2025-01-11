#include "AdKeyboradDevice.h"

AdKeyboardDevice::Buttons AdKeyboardDevice::readButtons()
{
    int value = analogRead(KEYBOARD_PIN);
    Serial.println("AdKeyboardDevice | analogRead return" + String(value));
    if (value < 3000)
    {
        return Buttons(getKey(value));
    }
    return Buttons::UNDEFINED;
}

int AdKeyboardDevice::getKey(int value)
{
    for (int i = 0; i < KEYS_COUNT; ++i)
    {
        //если измеренное значение попало в диапазон между референсными значениями, выводим номер диапазона
        if (value < _buttonValues[i])
            return i + 1;
    }
    return -1;
}
