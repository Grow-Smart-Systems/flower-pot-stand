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