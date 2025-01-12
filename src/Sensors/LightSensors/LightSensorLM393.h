#pragma once

#include "LightSensor.h"

class LightSensorLM393 : public LightSensor
{
public:
    LightSensorLM393();
    ~LightSensorLM393() = default;

    uint16_t getLightCoef() override;

    bool getIsDarkFlag() override;

    void getData(SensorsData& data) override;
};
