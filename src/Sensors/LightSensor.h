#pragma once

#include <Arduino.h>
#include "SensorData.h"


class SensorsData;

class LightSensor
{
public:
    LightSensor() = default;
    ~LightSensor() = default;


    virtual void getData(SensorsData &data) = 0;

    virtual uint16_t getLightCoef() = 0;

    virtual bool getIsDarkFlag() = 0;
};

#if LIGHT_SENSOR == SENSOR_LM393
    class LightSensorLM393 : public LightSensor 
    {
    public:
        LightSensorLM393();
        ~LightSensorLM393() = default;

        uint16_t getLightCoef() override;

        bool getIsDarkFlag() override;

        void getData(SensorsData &data) override; 
    };
#endif