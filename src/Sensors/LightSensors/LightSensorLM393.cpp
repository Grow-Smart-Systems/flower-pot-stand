#include "LightSensorLM393.h"

// light sensor pins
#define PIN_ANALOG_PHOTO_SENSOR     GPIO35


LightSensorLM393::LightSensorLM393()
{
    pinMode(PIN_ANALOG_PHOTO_SENSOR, INPUT);
}

uint16_t LightSensorLM393::getLightCoef()
{
    return analogRead(PIN_ANALOG_PHOTO_SENSOR);
}

bool LightSensorLM393::getIsDarkFlag()
{
    return false;
}

void LightSensorLM393::getData(SensorsData& data)
{
    data.lux = getLightCoef();
    data.isDark = getIsDarkFlag();
}
