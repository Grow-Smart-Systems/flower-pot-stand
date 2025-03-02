#pragma once

#include <Arduino.h>
#include <memory>

#include "EnumClasses.h"
#include "../Screen/Screen.h"
#include "../Sensors/Sensors.h"
#include "../ControlDevices/ControlDevices.h"

class Screen;
class SensorsData;

class Data final
{
public:
    static Data& GetInstance();

    //Setters
    void SetTemperatureStatus(TemperatureStatus status);
    void SetHumidityStatus(HumidityStatus status);
    void SetLuxStatus(LuxStatus status);

    void SetDisplayStatus(DisplayStatus status);
    void SetDisplayMode(DisplayMode mode);
    void SetDisplayMenu(DisplayMenu menu);
    void SetDisplayFunctionalScreen(DisplayFunctionalScreen screen);

    void SetScreen(std::shared_ptr<Screen> screen);
    void SetSensors(std::shared_ptr<Sensors> sensors);
    void SetControlDevices(std::shared_ptr<ControlDevices> controlDevices);
    //

    //Getters
    TemperatureStatus GetTemperatureStatus() const;
    HumidityStatus GetHumidityStatus() const;
    LuxStatus GetLuxStatus() const;

    DisplayStatus GetDisplayStatus() const;
    DisplayMode GetDisplayMode() const;
    DisplayMenu GetDisplayMenu() const;
    DisplayFunctionalScreen GetDisplayFunctionalScreen() const;

    std::shared_ptr<Screen> GetScreen() const;
    std::shared_ptr<Sensors> GetSensors() const;
    std::shared_ptr<ControlDevices> GetControlDevices() const;
    //

private:
    Data() = default;
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
    std::shared_ptr<Sensors> _sensors {nullptr};
    std::shared_ptr<ControlDevices> _controlDevices {nullptr};
};