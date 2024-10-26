#include "Data.h"

Data& Data::getInstance()
{
    static Data instance;
    return instance;
}

Data::Data()
{
}

void Data::setTemperatureStatus(TemperatureStatus status)
{
    _temperatureStatus = status;
}

void Data::setHumidityStatus(HumidityStatus status)
{
    _humidityStatus = status;
}

void Data::setLuxStatus(LuxStatus status)
{
    _luxStatus = status;
}

Data::TemperatureStatus Data::getTemperatureStatus() const
{
    return _temperatureStatus;
}

Data::HumidityStatus Data::getHumidityStatus() const
{
    return _humidityStatus;
}

Data::LuxStatus Data::getLuxStatus() const
{
    return _luxStatus;
}

void Data::setDisplayStatus(DisplayStatus status)
{
    _displayStatus = status;
}

void Data::setDisplayMode(DisplayMode mode)
{
    _displayMode = mode;
}

void Data::setDisplayMenu(DisplayMenu menu)
{
    _displayMenu = menu;
}

void Data::setScreen(std::shared_ptr<Screen> screen)
{
    _screen = screen;
}

void Data::setSensorsData(std::shared_ptr<SensorsData> sensorsData)
{
    _sensorsData = sensorsData;
}

Data::DisplayStatus Data::getDisplayStatus() const
{
    return _displayStatus;
}

Data::DisplayMode Data::getDisplayMode() const
{
    return _displayMode;
}

Data::DisplayMenu Data::getDisplayMenu() const
{
    return _displayMenu;
}

std::shared_ptr<Screen> Data::getScreen() const
{
    return _screen;
}

std::shared_ptr<SensorsData> Data::getSensorsData() const
{
    return _sensorsData;
}
