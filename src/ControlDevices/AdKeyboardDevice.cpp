#include "AdKeyboardDevice.h"

AdKeyboardDevice::Buttons AdKeyboardDevice::readButtons()
{
    int value = analogRead(KEYBOARD_PIN);
    unsigned long currentTime = millis();
    if (value < 3000)
    {
        int keyIndex = getKey(value);
        if (keyIndex != -1)
        {
            auto button = Buttons(keyIndex);
            if (button != Buttons::UNDEFINED)
            {
                if (button != _lastButton || ((currentTime - _lastPressTime) > _debounceDelay && currentTime >= _lastPressTime))
                {
                    _lastButton = button;
                    _lastPressTime = currentTime;
                    return button;
                }
            }
        }
    }
    return Buttons::UNDEFINED;
}

int AdKeyboardDevice::getKey(int value)
{
    const int thresholds[KEYS_COUNT] = {50, 500, 1200, 2000, 2800};
    for (int i = 0; i < KEYS_COUNT; ++i)
    {
        int lowerBound = (i == 0) ? 0 : (thresholds[i - 1] + thresholds[i]) / 2;
        int upperBound = thresholds[i];
        if (value >= lowerBound && value < upperBound)
        {
            return i;
        }
    }
    return -1;
}