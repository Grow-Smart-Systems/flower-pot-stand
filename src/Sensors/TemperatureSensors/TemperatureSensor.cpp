#include "TemperatureSensor.h"

void TemperatureSensor::getData(SensorsData& data)
{
    data.temperature = getTemperature();
    data.humidity = getHumidity();
}
