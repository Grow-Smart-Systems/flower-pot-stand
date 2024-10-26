#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#include "SettingsParameters.h"

#define ZERO_BYTE 0x00

class Settings
{
public:
    Settings();
    ~Settings() = default;

    void cleanAll();

    /// ============= Чтение настроек ============= ///

    /// @brief Чтение всех настроек из EEPROM
    /// @param settings - общая структура всех настроек
    void readAllSettings(GlobalSettings& settings);

    /// @brief Чтение настроек температуры из EEPROM
    /// @param settings - структура настроек температуры
    void readTemperatureSettings(TemperatureParameters& settings);

    /// @brief Чтение настроек влажности из EEPROM
    /// @param settings - структура настроек влажности
    void readHumiditySettings(HumidityParameters& settings);

    /// @brief Чтение настроек освещенности из EEPROM
    /// @param settings - структура настроек освещенности
    void readLightSettings(LightParameters& settings);

    /// @brief Чтение настроек экрана из EEPROM
    /// @param settings - структура настроек экрана
    void readScreenSettings(ScreenSettings& settings);

    /// @brief Чтение настроек сети из EEPROM
    /// @param settings - структура настроек сети
    void readNetworkSettings(NetworkSettings& settings);

    /// ============= Запись настроек ============= ///

    /// @brief Запись всех настроек в EEPROM
    /// @param settings - общая структура всех настроек
    void writeAllSettings(const GlobalSettings& settings);

    /// @brief Запись настроек температуры в EEPROM
    /// @param settings - структура настроек температуры
    void writeTemperatureSettings(const TemperatureParameters& settings);

    /// @brief Запись настроек влажности в EEPROM
    /// @param settings - структура настроек влажности
    void writeHumiditySettings(const HumidityParameters& settings);

    /// @brief Запись настроек освещенности в EEPROM
    /// @param settings - структура настроек освещенности
    void writeLightSettings(const LightParameters& settings);

    /// @brief Запись настроек экрана в EEPROM
    /// @param settings - структура настроек экрана
    void writeScreenSettings(const ScreenSettings& settings);

    /// @brief Запись настроек сети в EEPROM
    /// @param settings - структура настроек сети
    void writeNetworkSettings(const NetworkSettings& settings);
};
