#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <memory>

class BaseFunctionalScreen
{

public:
    BaseFunctionalScreen(std::shared_ptr<Adafruit_SSD1306> display);
    ~BaseFunctionalScreen() = default;

    virtual void printScreen();

    virtual void printFooter();

    virtual void printHeader();

protected:
    std::shared_ptr<Adafruit_SSD1306> _display{ nullptr };
};


