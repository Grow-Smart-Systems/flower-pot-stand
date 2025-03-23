#include "LightSensorLM393.h"
#include "../../ESP32_defines.h"

// light sensor pins
#define PIN_ANALOG_PHOTO_SENSOR     GPIO35


LightSensorLM393::LightSensorLM393()
{
    pinMode(PIN_ANALOG_PHOTO_SENSOR, INPUT);
}

uint16_t LightSensorLM393::GetLightCoef()
{
    return analogRead(PIN_ANALOG_PHOTO_SENSOR);
}

void LightSensorLM393::SetDataIn(SensorsDataContainer& container)
{
    container.lux = GetLightCoef();
}
