#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define PIN_SD_CS 10

class SDCardReaderInterface
{
public:
    SDCardReaderInterface();

    bool init();

    bool writeFile(const char* filename, const char* data);

    String readFile(const char* filename);

    bool deleteFile(const char* filename);

};
