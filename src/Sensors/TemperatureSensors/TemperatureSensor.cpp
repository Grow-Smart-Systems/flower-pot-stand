#include "TemperatureSensor.h"

void TemperatureSensor::SetDataIn(SensorsDataContainer& container)
{
    container.temperature = GetTemperature();
    container.humidity = GetHumidity();
}
