#include "Settings.h"

Settings::Settings()
{
    EEPROM.begin(GLOBAL_SETTINGS_SIZE);
}

//WARNING: использовать не часто, т.к. EEPROM имеет ограниченное количество циклов записи
void Settings::cleanAll()
{
    for (int i = 0; i < EEPROM.length(); i++)
    {
        EEPROM.write(i, ZERO_BYTE);
    }
}

void Settings::readAllSettings(GlobalSettings& settings)
{
    EEPROM.get(START_ADDRESS_POSITION, settings);
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

void Settings::readScreenSettings(ScreenSettings& settings)
{
    EEPROM.get(SCREEN_SETTINGS_ADDRESS, settings);
}

void Settings::readNetworkSettings(NetworkSettings& settings)
{
    EEPROM.get(NETWORK_SETTINGS_ADDRESS, settings);
}

void Settings::writeAllSettings(const GlobalSettings& settings)
{
    EEPROM.put(0, settings);
    EEPROM.commit();
}

void Settings::writeTemperatureSettings(const TemperatureParameters& settings)
{
    EEPROM.put(TEMPERATURE_SETTINGS_ADDRESS, settings);
    EEPROM.commit();
}

void Settings::writeHumiditySettings(const HumidityParameters& settings)
{
    EEPROM.put(HUMIDITY_SETTINGS_ADDRESS, settings);
    EEPROM.commit();
}

void Settings::writeLightSettings(const LightParameters& settings)
{
    EEPROM.put(LIGHT_SETTINGS_ADDRESS, settings);
    EEPROM.commit();
}

void Settings::writeScreenSettings(const ScreenSettings& settings)
{
    EEPROM.put(SCREEN_SETTINGS_ADDRESS, settings);
    EEPROM.commit();
}

void Settings::writeNetworkSettings(const NetworkSettings& settings)
{
    EEPROM.put(NETWORK_SETTINGS_ADDRESS, settings);
    EEPROM.commit();
}