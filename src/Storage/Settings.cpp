#include "Settings.h"

//WARNING: использовать не часто, т.к. EEPROM имеет ограниченное количество циклов записи
void Settings::cleanAll()
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, 0);
    }
}

void Settings::readAllSettings(GlobalSettings &settings)
{
    EEPROM.get(0, settings);
}

void Settings::readTemperatureSettings(TemperatureParameters& settings)
{
    EEPROM.get(TEMPERATURE_SETTINGS_ADDRESS, settings);
}

void Settings::readHumiditySettings(HumidityParameters& settings)
{
    EEPROM.get(HUMIDITY_SETTINGS_ADDRESS, settings);
}

void Settings::readLightSettings(LightParameters& settings)
{
    EEPROM.get(LIGHT_SETTINGS_ADDRESS, settings);
}

void Settings::readNetworkSettings(NetworkSettings& settings)
{
    EEPROM.get(NETWORK_SETTINGS_ADDRESS, settings);
}

void Settings::writeTemperatureSettings(const TemperatureParameters& settings)
{
    for (int i = 0; i < TEMPERATURE_SETTINGS_SIZE; i++)
    {
        EEPROM.update(TEMPERATURE_SETTINGS_ADDRESS + i, settings.data.array[i]);
    }
}

void Settings::writeHumiditySettings(const HumidityParameters& settings)
{
    for (int i = 0; i < HUMIDITY_SETTINGS_SIZE; i++)
    {
        EEPROM.update(HUMIDITY_SETTINGS_ADDRESS + i, settings.data.array[i]);
    }
}

void Settings::writeLightSettings(const LightParameters& settings)
{
    for (int i = 0; i < LIGHT_SETTINGS_SIZE; i++)
    {
        EEPROM.update(LIGHT_SETTINGS_ADDRESS + i, settings.data.array[i]);
    }
}

void Settings::writeNetworkSettings(const NetworkSettings& settings)
{
    for (int i = 0; i < NETWORK_SETTINGS_SIZE; i++)
    {
        EEPROM.update(NETWORK_SETTINGS_ADDRESS + i, settings.data.array[i]);
    }
}