#pragma once

#include "Common.h"

class Data
{
public:

    // Sensors statuses
    enum TemperatureStatus
    {
        UNDEFINED_TEMPERATURE,
        NORMAL_TEMPERATURE,
        WARM_TEMPERATURE,
        COLD_TEMPERATURE
    };

    enum HumidityStatus
    {
        UNDEFINED_HUMIDITY,
        NORMAL_HUMIDITY,
        HIGH_HUMIDITY,
        LOW_HUMIDITY
    };

    enum LuxStatus
    {
        UNDEFINED_LUX,
        NORMAL_LUX,
        HIGH_LUX,
        LOW_LUX
    };
    // 

    // Network statuses

    //

    //Display statuses
    enum DisplayStatus
    {
        UNDEFINED_DISPLAY,
        DISPLAY_ON,
        DISPLAY_OFF
    };

    enum DisplayMode
    {
        UNDEFINED_MODE,
        AWAIT_MODE,
        MENU_MODE
    };

    enum DisplayMenu
    {
        MAIN_MENU,
        SUB_MENU,
        FUCTIONAL_MENU
    };
    //


public:
    static Data& getInstance();

    //Setters
    void setTemperatureStatus(TemperatureStatus status);
    void setHumidityStatus(HumidityStatus status);
    void setLuxStatus(LuxStatus status);

    void setDisplayStatus(DisplayStatus status);
    void setDisplayMode(DisplayMode mode);
    void setDisplayMenu(DisplayMenu menu);
    //

    //Getters
    TemperatureStatus getTemperatureStatus() const;
    HumidityStatus getHumidityStatus() const;
    LuxStatus getLuxStatus() const;

    DisplayStatus getDisplayStatus() const;
    DisplayMode getDisplayMode() const;
    DisplayMenu getDisplayMenu() const;
    //

private:
    Data();
    ~Data() = default;

    TemperatureStatus _temperatureStatus{ UNDEFINED_TEMPERATURE };
    HumidityStatus _humidityStatus{ UNDEFINED_HUMIDITY };
    LuxStatus _luxStatus{ UNDEFINED_LUX };

    DisplayStatus _displayStatus{ UNDEFINED_DISPLAY };
    DisplayMode _displayMode{ UNDEFINED_MODE };
    DisplayMenu _displayMenu{ MAIN_MENU };
};