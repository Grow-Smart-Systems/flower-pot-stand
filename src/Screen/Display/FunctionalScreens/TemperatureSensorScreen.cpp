#include "TemperatureSensorScreen.h"


TemperatureSensorScreen::TemperatureSensorScreen(std::shared_ptr<Adafruit_SSD1306> display)
    : BaseFunctionalScreen(display)
{
}


void TemperatureSensorScreen::printScreen()
{
    _display->setTextSize(1);
    _display->setTextColor(SSD1306_WHITE);
    _display->setCursor(0, 10);
    _display->println("Temperature Sensor screen");
}

void TemperatureSensorScreen::printFooter()
{
}

void TemperatureSensorScreen::printHeader()
{
}