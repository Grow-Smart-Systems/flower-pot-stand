#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <memory>



class BaseFunctionalScreen
{


public:
    BaseFunctionalScreen() = default;
    ~BaseFunctionalScreen() = default;

    virtual void printScreen(std::shared_ptr<Adafruit_SSD1306> display) = 0;
};


