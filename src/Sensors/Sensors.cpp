#include "Sensors.h"

#if TEMPERATURE_SENSOR == SENSOR_DHT11
#include "TemperatureSensors/TemperatureSensorDHT11.h"
#endif

#if LIGHT_SENSOR == SENSOR_LM393
#include "LightSensors/LightSensorLM393.h"
#endif


Sensors::Sensors()
{

#if LIGHT_SENSOR == SENSOR_LM393
    _lightSensor = new LightSensorLM393();
#endif

#if TEMPERATURE_SENSOR == SENSOR_DHT11
    _temperatureSensor = new TemperatureSensorDHT11();
#endif
}

Sensors::~Sensors()
{
    if (_lightSensor)
        delete _lightSensor;

    if (_temperatureSensor)
        delete _temperatureSensor;
}

const SensorsDataContainer& Sensors::GetSensorInfo()
{
    return _dataContainer;
}

void Sensors::Update()
{
    _temperatureSensor->SetDataIn(_dataContainer);
    _lightSensor->SetDataIn(_dataContainer);
}