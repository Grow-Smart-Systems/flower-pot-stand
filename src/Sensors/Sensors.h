#pragma once

#include "SensorsConfiguration.h"
#include "LightSensors/LightSensor.h"
#include "TemperatureSensors/TemperatureSensor.h"
#include "../Common/Containers/SensorsDataContainer.h"

class LightSensor;
class TemperatureSensor;

class Sensors final
{

public:
    Sensors();
    ~Sensors();

    void Update();

    const SensorsDataContainer& GetSensorInfo();

private:

    SensorsDataContainer _dataContainer;

    LightSensor* _lightSensor;
    TemperatureSensor* _temperatureSensor;

};