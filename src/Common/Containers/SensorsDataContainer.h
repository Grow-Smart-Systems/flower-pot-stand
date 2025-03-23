#pragma once

#include <Arduino.h>


struct SensorsDataContainer
{
    float temperature {.0};
    float humidity {.0};
    uint16_t lux {0};
};