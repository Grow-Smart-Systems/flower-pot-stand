#pragma once

#include <Arduino.h>
#include "SensorData.h"

class SensorsData;

class TemperatureSensor
{
public:
    TemperatureSensor() = default;
    ~TemperatureSensor() = default;

    virtual float getTemperature() = 0;
    virtual float getHumidity() = 0;

    void getData(SensorsData &data);
};

#if TEMPERATURE_SENSOR == SENSOR_DHT11
    #include <DHT.h>

    #define PIN_TEMPERATURE_SENSOR 0x02
    #define DHTTYPE DHT11


    class TemperatureSensorDHT11 : public TemperatureSensor
    {
    private:
        DHT _dht;

    public:
        TemperatureSensorDHT11();
        ~TemperatureSensorDHT11() = default;

        float getTemperature() override;
        float getHumidity() override;
    };

#endif