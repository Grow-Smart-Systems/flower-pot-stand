#pragma once

#include <Arduino.h>
#include <memory>
#include "../Screen/Screen.h"
#include "../Sensors/SensorData.h"

class Screen;
class SensorsData;

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
        FUNCTIONAL_SCREEN
    };
    enum DisplayFunctionalScreen
    {
        UNDEFINED_FUNCTIONAL_SCREEN,
        TEMPERATURE_SENSOR_SCREEN,
        HUMIDITY_SENSOR_SCREEN,
        LUX_SENSOR_SCREEN
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
    void setDisplayFunctionalScreen(DisplayFunctionalScreen screen);

    void setScreen(std::shared_ptr<Screen> screen);
    void setSensorsData(std::shared_ptr<SensorsData> sensorsData);
    //

    //Getters
    TemperatureStatus getTemperatureStatus() const;
    HumidityStatus getHumidityStatus() const;
    LuxStatus getLuxStatus() const;

    DisplayStatus getDisplayStatus() const;
    DisplayMode getDisplayMode() const;
    DisplayMenu getDisplayMenu() const;
    DisplayFunctionalScreen getDisplayFunctionalScreen() const;

    std::shared_ptr<Screen> getScreen() const;
    std::shared_ptr<SensorsData> getSensorsData() const;
    //

private:
    Data();
    ~Data() = default;
    Data(const Data&) = delete;
    Data& operator=(const Data&) = delete;

    TemperatureStatus _temperatureStatus{ UNDEFINED_TEMPERATURE };
    HumidityStatus _humidityStatus{ UNDEFINED_HUMIDITY };
    LuxStatus _luxStatus{ UNDEFINED_LUX };

    DisplayStatus _displayStatus{ UNDEFINED_DISPLAY };
    DisplayMode _displayMode{ UNDEFINED_MODE };
    DisplayMenu _displayMenu{ MAIN_MENU };
    DisplayFunctionalScreen _displayFunctionalScreen{ UNDEFINED_FUNCTIONAL_SCREEN };

    std::shared_ptr<Screen> _screen{ nullptr };
    std::shared_ptr<SensorsData> _sensorsData{ nullptr };
};