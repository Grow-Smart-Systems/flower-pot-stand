#pragma once

#include "SensorsConfiguration.h"
#include "LightSensors/LightSensor.h"
#include "TemperatureSensors/TemperatureSensor.h"

class LightSensor;
class TemperatureSensor;

class SensorsData
{

public:
    SensorsData();
    ~SensorsData();

    void update();

    float temperature{ .0 };
    float humidity{ .0 };
    uint16_t lux{ 0 };
    uint8_t isDark{ 0 };

private:

    LightSensor* _lightSensor;
    TemperatureSensor* _temperatureSensor;

};