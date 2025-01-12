#include "LightSensor.h"

void LightSensor::getData(SensorsData& data)
{
    data.lux = getLightCoef();
    data.isDark = getIsDarkFlag();
}
