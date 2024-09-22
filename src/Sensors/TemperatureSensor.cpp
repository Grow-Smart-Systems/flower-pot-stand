#include "TemperatureSensor.h"

void TemperatureSensor::getData(SensorsData &data)
{
    data.temperature = getTemperature();
    data.humidity = getHumidity();
}

#if TEMPERATURE_SENSOR == SENSOR_DHT11
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
#endif