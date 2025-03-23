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
            
            // Используем защиту от дребезга
            unsigned long elapsed = (currentTime >= _lastPressTime) ? 
                                   (currentTime - _lastPressTime) : 
                                   ((ULONG_MAX - _lastPressTime) + currentTime + 1);
                                   
            if (elapsed > _debounceDelay)
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
    const int thresholds[KEYS_COUNT + 1] = {0, 50, 500, 1200, 2000, 2800}; // Добавляем нулевой порог
    
    for (int i = 0; i < KEYS_COUNT; ++i)
    {
        if (value >= thresholds[i] && value < thresholds[i + 1])
        {
            return i;
        }
    }
    
    return -1;
}