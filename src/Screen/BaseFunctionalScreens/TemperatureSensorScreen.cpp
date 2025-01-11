#include "TemperatureSensorScreen.h"


void TemperatureSensorScreen::printScreen(std::shared_ptr<Adafruit_SSD1306> display)
{
    display->clearDisplay();
    display->setTextSize(1);
    display->setTextColor(SSD1306_WHITE);
    display->setCursor(0, 0);
    display->println("Temperature Sensor functional screen");
    display->display();
}