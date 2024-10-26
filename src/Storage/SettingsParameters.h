#pragma once

#include <Arduino.h>

#define START_ADDRESS_POSITION 0

// Temperature Settings
#pragma pack(push, 1)
#define TEMPERATURE_SETTINGS_SIZE sizeof(TemperatureParameters)
#define TEMPERATURE_SETTINGS_ADDRESS START_ADDRESS_POSITION
struct TemperatureParameters
{
    uint8_t maxTemperature;
    uint8_t minTemperature;

};
#pragma pack(pop)


// Humidity Settings
#pragma pack(push, 1)
#define HUMIDITY_SETTINGS_SIZE sizeof(HumidityParameters)
#define HUMIDITY_SETTINGS_ADDRESS (TEMPERATURE_SETTINGS_SIZE - 1)
struct HumidityParameters
{
    uint8_t maxHumidity;
    uint8_t minHumidity;
};
#pragma pack(pop)


// Light Settings
#pragma pack(push, 1)
#define LIGHT_SETTINGS_SIZE sizeof(LightParameters)
#define LIGHT_SETTINGS_ADDRESS (TEMPERATURE_SETTINGS_SIZE + HUMIDITY_SETTINGS_SIZE - 1)
struct LightParameters
{
    uint16_t maxLight;
    uint16_t minLight;
    uint16_t borderLight;
};
#pragma pack(pop)


// Network Settings
#pragma pack(push, 1)
#define NETWORK_SETTINGS_SIZE sizeof(NetworkSettings)
#define NETWORK_SETTINGS_ADDRESS (TEMPERATURE_SETTINGS_SIZE + HUMIDITY_SETTINGS_SIZE + LIGHT_SETTINGS_SIZE - 1)
struct NetworkSettings
{
    char ssid[32];
    char password[32];
};
#pragma pack(pop)


// Screen Settings
#pragma pack(push, 1)
#define SCREEN_SETTINGS_SIZE sizeof(ScreenSettings)
#define SCREEN_SETTINGS_ADDRESS (TEMPERATURE_SETTINGS_SIZE + HUMIDITY_SETTINGS_SIZE + LIGHT_SETTINGS_SIZE + NETWORK_SETTINGS_SIZE - 1)
struct ScreenSettings
{
    uint8_t awaitTimeout;
    uint8_t sleepTimeout;
};
#pragma pack(pop)


// Global Settings
#pragma pack(push, 1)
#define GLOBAL_SETTINGS_SIZE (TEMPERATURE_SETTINGS_SIZE + HUMIDITY_SETTINGS_SIZE + LIGHT_SETTINGS_SIZE + NETWORK_SETTINGS_SIZE + SCREEN_SETTINGS_SIZE)
struct GlobalSettings
{
    //NOTE: Порядок следования параметров крайне важен!
    TemperatureParameters temperature;
    HumidityParameters humidity;
    LightParameters light;
    ScreenSettings screen;
    NetworkSettings network;
};
#pragma pack(pop)

