#pragma once

#include "BaseFunctionalScreen.h"


class TemperatureSensorScreen : public BaseFunctionalScreen
{

public:
    TemperatureSensorScreen(std::shared_ptr<Adafruit_SSD1306> display);
    ~TemperatureSensorScreen() = default;

    void printScreen() override;

    void printFooter() override;

    void printHeader() override;

};