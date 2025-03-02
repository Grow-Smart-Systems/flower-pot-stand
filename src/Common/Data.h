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
    enum class TemperatureStatus
    {
        UNDEFINED_TEMPERATURE,
        NORMAL_TEMPERATURE,
        WARM_TEMPERATURE,
        COLD_TEMPERATURE
    };

    enum class HumidityStatus
    {
        UNDEFINED_HUMIDITY,
        NORMAL_HUMIDITY,
        HIGH_HUMIDITY,
        LOW_HUMIDITY
    };

    enum class LuxStatus
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
    enum class DisplayStatus
    {
        UNDEFINED_DISPLAY,
        DISPLAY_ON,
        DISPLAY_OFF
    };

    enum class DisplayMode
    {
        UNDEFINED_MODE,
        AWAIT_MODE,
        MENU_MODE
    };

    enum class DisplayMenu
    {
        MAIN_MENU,
        SUB_MENU,
        FUNCTIONAL_MENU
    };
    enum class DisplayFunctionalScreen
    {
        UNDEFINED_FUNCTIONAL_SCREEN,
        TEMPERATURE_SENSOR_SCREEN,
        HUMIDITY_SENSOR_SCREEN,
        LUX_SENSOR_SCREEN
    };
    //

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

    TemperatureStatus _temperatureStatus {TemperatureStatus::UNDEFINED_TEMPERATURE};
    HumidityStatus _humidityStatus {HumidityStatus::UNDEFINED_HUMIDITY};
    LuxStatus _luxStatus {LuxStatus::UNDEFINED_LUX};

    DisplayStatus _displayStatus {DisplayStatus::UNDEFINED_DISPLAY};
    DisplayMode _displayMode {DisplayMode::UNDEFINED_MODE};
    DisplayMenu _displayMenu {DisplayMenu::MAIN_MENU};
    DisplayFunctionalScreen _displayFunctionalScreen {DisplayFunctionalScreen::UNDEFINED_FUNCTIONAL_SCREEN};

    std::shared_ptr<Screen> _screen {nullptr};
    std::shared_ptr<SensorsData> _sensorsData {nullptr};
};