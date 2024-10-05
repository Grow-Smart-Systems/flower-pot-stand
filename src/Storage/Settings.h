#pragma once

#include <Arduino.h>
#include <EEPROM.h>

#include "SettingsParameters.h"


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

    /// @brief Чтение настроек сети из EEPROM
    /// @param settings - структура настроек сети
    void readNetworkSettings(NetworkSettings& settings);

    /// ============= Запись настроек ============= ///

    /// @brief Запись настроек температуры в EEPROM
    /// @param settings - структура настроек температуры
    void writeTemperatureSettings(const TemperatureParameters& settings);

    /// @brief Запись настроек влажности в EEPROM
    /// @param settings - структура настроек влажности
    void writeHumiditySettings(const HumidityParameters& settings);

    /// @brief Запись настроек освещенности в EEPROM
    /// @param settings - структура настроек освещенности
    void writeLightSettings(const LightParameters& settings);

    /// @brief Запись настроек сети в EEPROM
    /// @param settings - структура настроек сети
    void writeNetworkSettings(const NetworkSettings& settings);

    //NOTE: Возможно позже следует продумать работу с чек-суммой
//     bool writeDataWithChecksum(int address, const uint8_t* data, size_t length)
//     {
//         uint8_t checksum = calculateChecksum(data, length);
//         EEPROM.put(address, data);
//         EEPROM.put(address + length, checksum);
//         return true;
//     }

//     bool readDataWithChecksum(int address, uint8_t* data, size_t length)
//     {
//         EEPROM.get(address, data);
//         uint8_t storedChecksum;
//         EEPROM.get(address + length, storedChecksum);
//         uint8_t calculatedChecksum = calculateChecksum(data, length);
//         return storedChecksum == calculatedChecksum;
//     }

// private:
//     uint8_t calculateChecksum(const uint8_t* data, size_t length)
//     {
//         uint8_t checksum = 0;
//         for (size_t i = 0; i < length; ++i)
//         {
//             checksum ^= data[i];
//         }
//         return checksum;
//     }
};
