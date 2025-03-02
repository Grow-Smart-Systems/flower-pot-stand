#include "LightSensor.h"

void LightSensor::SetDataIn(SensorsDataContainer& container)
{
    container.lux = GetLightCoef();
}
