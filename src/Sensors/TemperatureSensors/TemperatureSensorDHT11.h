#pragma once

#include <DHT.h>
#include "TemperatureSensor.h"

#define PIN_TEMPERATURE_SENSOR GPIO33
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
