#include "TemperatureSensorDHT11.h"

TemperatureSensorDHT11::TemperatureSensorDHT11()
    : _dht(PIN_TEMPERATURE_SENSOR, DHTTYPE)
{
    _dht.begin();
}

float TemperatureSensorDHT11::getTemperature()
{
    return _dht.readTemperature();
}

float TemperatureSensorDHT11::getHumidity()
{
    return _dht.readHumidity();
}