#pragma once

#include <Arduino.h>
#include "../../ESP32_defines.h"
#include "../SensorData.h"

class SensorsData;

class TemperatureSensor
{
public:
    TemperatureSensor() = default;
    ~TemperatureSensor() = default;

    virtual float getTemperature() = 0;
    virtual float getHumidity() = 0;

    void getData(SensorsData& data);
};

