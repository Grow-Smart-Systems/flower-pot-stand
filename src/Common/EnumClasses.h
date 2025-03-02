#pragma once

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
