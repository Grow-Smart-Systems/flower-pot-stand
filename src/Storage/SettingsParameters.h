#pragma once


// Temperature Settings
#pragma pack(push, 1)
#define TEMPERATURE_SETTINGS_SIZE 2
#define TEMPERATURE_SETTINGS_ADDRESS 0
struct TemperatureParameters
{
    union Data
    {
        struct
        {
            uint8_t maxTemperature;
            uint8_t minTemperature;
        };
        uint8_t array[TEMPERATURE_SETTINGS_SIZE];
    } data;
};
#pragma pack(pop)


// Humidity Settings
#pragma pack(push, 1)
#define HUMIDITY_SETTINGS_SIZE 2
#define HUMIDITY_SETTINGS_ADDRESS (TEMPERATURE_SETTINGS_SIZE - 1)
struct HumidityParameters
{
    union Data
    {
        struct
        {
            uint8_t maxHumidity;
            uint8_t minHumidity;
        };
        uint8_t array[HUMIDITY_SETTINGS_SIZE];
    } data; 
};
#pragma pack(pop)


// Light Settings
#pragma pack(push, 1)
#define LIGHT_SETTINGS_SIZE 6
#define LIGHT_SETTINGS_ADDRESS (TEMPERATURE_SETTINGS_SIZE + HUMIDITY_SETTINGS_SIZE - 1)
struct LightParameters
{
    union Data
    {
        struct
        {
            uint16_t maxLight;
            uint16_t minLight;
            uint16_t borderLight;
        };
        uint8_t array[LIGHT_SETTINGS_SIZE];
    } data;
};
#pragma pack(pop)


// Network Settings
#pragma pack(push, 1)
#define NETWORK_SETTINGS_SIZE 64
#define NETWORK_SETTINGS_ADDRESS (TEMPERATURE_SETTINGS_SIZE + HUMIDITY_SETTINGS_SIZE + LIGHT_SETTINGS_SIZE - 1)
struct NetworkSettings
{
    union Data
    {
        struct
        {
            char ssid[32];
            char password[32];
        };
        uint8_t array[NETWORK_SETTINGS_SIZE];
    } data;
};
#pragma pack(pop)


// Global Settings
#pragma pack(push, 1)
#define GLOBAL_SETTINGS_SIZE (TEMPERATURE_SETTINGS_SIZE + HUMIDITY_SETTINGS_SIZE + LIGHT_SETTINGS_SIZE + NETWORK_SETTINGS_SIZE)
struct GlobalSettings
{
    //NOTE: порядок структур ниже очень важен!
    union Data
    {
        struct
        {
            TemperatureParameters temperature;
            HumidityParameters humidity;
            LightParameters light;
            NetworkSettings network;
        };
        uint8_t array[GLOBAL_SETTINGS_SIZE];
    } data;
};
#pragma pack(pop)

