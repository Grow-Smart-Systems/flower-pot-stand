#include "SensorData.h"


SensorsData::SensorsData()
{
    #if LIGHT_SENSOR == SENSOR_LM393
        _lightSensor = new LightSensorLM393();
    #endif

    #if TEMPERATURE_SENSOR == SENSOR_DHT11
        _temperatureSensor = new TemperatureSensorDHT11();
    #endif

}

SensorsData::~SensorsData()
{
    if (_lightSensor)
        delete _lightSensor;

    if (_temperatureSensor)
        delete _temperatureSensor;
}

void SensorsData::update()
{
    _lightSensor->getData(*this);
    _temperatureSensor->getData(*this);
}