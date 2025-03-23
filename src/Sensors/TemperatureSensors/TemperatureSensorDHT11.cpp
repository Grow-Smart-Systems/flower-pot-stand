#include "TemperatureSensorDHT11.h"
#include "../../ESP32_defines.h"

TemperatureSensorDHT11::TemperatureSensorDHT11()
    : _dht(PIN_TEMPERATURE_SENSOR, DHTTYPE)
{
    _dht.begin();
}

float TemperatureSensorDHT11::GetTemperature()
{
    return _dht.readTemperature();
}

float TemperatureSensorDHT11::GetHumidity()
{
    return _dht.readHumidity();
}