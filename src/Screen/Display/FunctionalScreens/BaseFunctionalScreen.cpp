#include "BaseFunctionalScreen.h"

BaseFunctionalScreen::BaseFunctionalScreen(std::shared_ptr<Adafruit_SSD1306> display)
    : _display(display)
{
}

void BaseFunctionalScreen::printScreen()
{
    _display->setTextSize(2);
    _display->setTextColor(SSD1306_WHITE);
    _display->setCursor(0, 30);
    _display->println("Empty functional screen!");
}

void BaseFunctionalScreen::printFooter()
{
}

void BaseFunctionalScreen::printHeader()
{
}
