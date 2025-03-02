#include "Data.h"

Data& Data::GetInstance()
{
    static Data instance;
    return instance;
}

void Data::SetTemperatureStatus(TemperatureStatus status)
{
    _temperatureStatus = status;
}

void Data::SetHumidityStatus(HumidityStatus status)
{
    _humidityStatus = status;
}

void Data::SetLuxStatus(LuxStatus status)
{
    _luxStatus = status;
}

TemperatureStatus Data::GetTemperatureStatus() const
{
    return _temperatureStatus;
}

HumidityStatus Data::GetHumidityStatus() const
{
    return _humidityStatus;
}

LuxStatus Data::GetLuxStatus() const
{
    return _luxStatus;
}

void Data::SetDisplayStatus(DisplayStatus status)
{
    _displayStatus = status;
}

void Data::SetDisplayMode(DisplayMode mode)
{
    _displayMode = mode;
}

void Data::SetDisplayMenu(DisplayMenu menu)
{
    _displayMenu = menu;
}

void Data::SetDisplayFunctionalScreen(DisplayFunctionalScreen screen)
{
    _displayFunctionalScreen = screen;
}

void Data::SetScreen(std::shared_ptr<Screen> screen)
{
    _screen = screen;
}

void Data::SetSensors(std::shared_ptr<Sensors> sensors)
{
    _sensors = sensors;
}

void Data::SetControlDevices(std::shared_ptr<ControlDevices> controlDevices)
{
    _controlDevices = controlDevices;
}

DisplayStatus Data::GetDisplayStatus() const
{
    return _displayStatus;
}

DisplayMode Data::GetDisplayMode() const
{
    return _displayMode;
}

DisplayMenu Data::GetDisplayMenu() const
{
    return _displayMenu;
}

DisplayFunctionalScreen Data::GetDisplayFunctionalScreen() const
{
    return _displayFunctionalScreen;
}

std::shared_ptr<Screen> Data::GetScreen() const
{
    return _screen;
}

std::shared_ptr<Sensors> Data::GetSensors() const
{
    return _sensors;
}

std::shared_ptr<ControlDevices> Data::GetControlDevices() const
{
    return _controlDevices;
}
