#pragma once

#include <Arduino.h>
#include <memory>
#include <vector>

#include "EnumClasses.h"
#include "DeviceInterface/DeviceInterfaceController.h"
#include "../Screen/Screen.h"
#include "../Sensors/Sensors.h"
#include "../ControlDevices/ControlDevices.h"

class Screen;
class SensorsData;


/// @brief Класс для хранения данных
class Data final
{
public:
    /// @brief Получение экземпляра класса
    /// @return Экземпляр класса
    static Data& GetInstance();

    //Setters
    void SetTemperatureStatus(TemperatureStatus status);
    void SetHumidityStatus(HumidityStatus status);
    void SetLuxStatus(LuxStatus status);

    void SetDisplayStatus(DisplayStatus status);
    void SetDisplayMode(DisplayMode mode);
    void SetDisplayMenu(DisplayMenu menu);
    void SetDisplayFunctionalScreen(DisplayFunctionalScreen screen);

    void SetDeviceController(std::shared_ptr<DeviceInterfaceController> deviceInterfaceController);
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

    std::shared_ptr<DeviceInterfaceController> GetDeviceController() const;
    std::shared_ptr<Screen> GetScreen() const;
    std::shared_ptr<Sensors> GetSensors() const;
    std::shared_ptr<ControlDevices> GetControlDevices() const;
    //

private:
    /// @brief Конструктор по умолчанию
    Data() = default;

    /// @brief Деструктор по умолчанию
    ~Data() = default;

    /// @brief Конструктор копирования
    /// @param other Другой объект
    Data(const Data&) = delete;

    /// @brief Оператор присваивания
    /// @param other Другой объект
    Data& operator=(const Data&) = delete;

    /// @brief Статусы температуры
    TemperatureStatus _temperatureStatus {TemperatureStatus::UNDEFINED_TEMPERATURE};

    /// @brief Статусы влажности
    HumidityStatus _humidityStatus {HumidityStatus::UNDEFINED_HUMIDITY};

    /// @brief Статусы освещенности
    LuxStatus _luxStatus {LuxStatus::UNDEFINED_LUX};

    /// @brief Статус дисплея
    DisplayStatus _displayStatus {DisplayStatus::UNDEFINED_DISPLAY};

    /// @brief Режим дисплея
    DisplayMode _displayMode {DisplayMode::UNDEFINED_MODE};

    /// @brief Меню дисплея
    DisplayMenu _displayMenu {DisplayMenu::MAIN_MENU};

    /// @brief Тип функционального экрана дисплея
    DisplayFunctionalScreen _displayFunctionalScreen {DisplayFunctionalScreen::UNDEFINED_FUNCTIONAL_SCREEN};

    /* Devices */

    /// @brief Контроллер устройств
    std::shared_ptr<DeviceInterfaceController> _deviceInterfaceController {nullptr};

    /// @brief Устройство - экран
    std::shared_ptr<Screen> _screen {nullptr};

    /// @brief Устройство - датчики
    std::shared_ptr<Sensors> _sensors {nullptr};

    /// @brief Устройство - внешнее управление
    std::shared_ptr<ControlDevices> _controlDevices {nullptr};
};