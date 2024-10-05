#pragma once

#include <EEPROM.h>
#include <Arduino.h>

#include "../Utils/BoolArray.h"


class MaintenanceEEPROM
{
public:
    MaintenanceEEPROM();

    ~MaintenanceEEPROM();

    BoolArray ReadWriteMemoryTest(unsigned int from = 0, unsigned int to = 0);
};