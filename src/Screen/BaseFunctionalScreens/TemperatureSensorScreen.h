#pragma once

#include "BaseFunctionalScreen.h"


class TemperatureSensorScreen : public BaseFunctionalScreen
{

public:
    TemperatureSensorScreen() = default;
    ~TemperatureSensorScreen() = default;

    void printScreen(std::shared_ptr<Adafruit_SSD1306> display) override;
};