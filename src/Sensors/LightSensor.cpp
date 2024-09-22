#include "LightSensor.h"

void LightSensor::getData(SensorsData &data)
{
    data.lux = getLightCoef();
    data.isDark = getIsDarkFlag();
}

/// =========== LM393 =========== ///
#if LIGHT_SENSOR == LM393
    // light sensor pins
    #define PIN_ANALOG_PHOTO_SENSOR     A0
    #define PIN_DIGITAL_PHOTO_SENSOR    A1


    LightSensorLM393::LightSensorLM393()
    {
        pinMode(PIN_ANALOG_PHOTO_SENSOR,    INPUT);          // Установим вывод A0 как вход
        //pinMode(PIN_DIGITAL_PHOTO_SENSOR,   INPUT);          // Установим вывод A1 как вход
    }

    uint16_t LightSensorLM393::getLightCoef()
    {
        return analogRead (PIN_ANALOG_PHOTO_SENSOR);
    }

    bool LightSensorLM393::getIsDarkFlag()
    {
        return false;//digitalRead(PIN_DIGITAL_PHOTO_SENSOR);
    }

    void LightSensorLM393::getData(SensorsData &data)
    {
        data.lux = getLightCoef();
        data.isDark = getIsDarkFlag();
    }
#endif