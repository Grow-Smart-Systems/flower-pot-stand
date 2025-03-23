#pragma once

// Sensors statuses

// @brief Статус температуры
enum class TemperatureStatus
{
    UNDEFINED_TEMPERATURE,  // Неопределенная температура
    NORMAL_TEMPERATURE,     // Нормальная температура
    WARM_TEMPERATURE,       // Теплая температура
    COLD_TEMPERATURE        // Холодная температура
};

// @brief Статус влажности
enum class HumidityStatus
{
    UNDEFINED_HUMIDITY, // Неопределенная влажность
    NORMAL_HUMIDITY,    // Нормальная влажность
    HIGH_HUMIDITY,      // Высокая влажность
    LOW_HUMIDITY        // Низкая влажность
};

// @brief Статус освещенности
enum class LuxStatus
{
    UNDEFINED_LUX,  // Неопределенная освещенность
    NORMAL_LUX,     // Нормальная освещенность
    HIGH_LUX,       // Высокая освещенность
    LOW_LUX         // Низкая освещенность
};
// 

// Network statuses

//

//Display statuses

// @brief Статус дисплея
enum class DisplayStatus
{
    UNDEFINED_DISPLAY,  // Неопределенный статус дисплея
    DISPLAY_ON,         // Дисплей включен
    DISPLAY_OFF         // Дисплей выключен
};

// @brief Статус режима дисплея
enum class DisplayMode
{
    UNDEFINED_MODE, // Неопределенный режим
    AWAIT_MODE,     // Режим ожидания
    MENU_MODE       // Режим меню
};

// @brief Статус меню
enum class DisplayMenu
{
    MAIN_MENU,      // Главное меню
    SUB_MENU,       // Подменю
    FUNCTIONAL_MENU // Функциональное меню
};

// @brief Статус функционального экрана
enum class DisplayFunctionalScreen
{
    UNDEFINED_FUNCTIONAL_SCREEN,    // Неопределенный функциональный экран
    TEMPERATURE_SENSOR_SCREEN,      // Экран температурного датчика
    HUMIDITY_SENSOR_SCREEN,         // Экран влажностного датчика
    LUX_SENSOR_SCREEN               // Экран освещенности
};
//
