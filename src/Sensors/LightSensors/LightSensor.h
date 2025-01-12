#pragma once

#include <Arduino.h>
#include "../SensorData.h"
#include "../../ESP32_defines.h"


class SensorsData;

class LightSensor
{
public:
    LightSensor() = default;
    ~LightSensor() = default;

    virtual void getData(SensorsData& data) = 0;

    virtual uint16_t getLightCoef() = 0;

    virtual bool getIsDarkFlag() = 0;
};

