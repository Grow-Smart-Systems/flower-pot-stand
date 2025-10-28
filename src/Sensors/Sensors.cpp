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
    _lightSensor = std::make_unique<LightSensorLM393>();
#endif

#if TEMPERATURE_SENSOR == SENSOR_DHT11
    _temperatureSensor = std::make_unique<TemperatureSensorDHT11>();
#endif
}

Sensors::~Sensors() = default;

void Sensors::LoopIteration()
{
    if (_sensorsTimer.ready())
    {
        update();
    }
}

void Sensors::StartTimers()
{
    _sensorsTimer.start(2000);
}

const SensorsDataContainer& Sensors::GetSensorInfo()
{
    return _dataContainer;
}

void Sensors::update()
{
    if (_temperatureSensor)
    {
        _temperatureSensor->SetDataIn(_dataContainer);
    }
    
    if (_lightSensor)
    {
        _lightSensor->SetDataIn(_dataContainer);
    }
}