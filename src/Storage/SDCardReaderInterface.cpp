#include "SDCardReaderInterface.h"

SDCardReaderInterface::SDCardReaderInterface()
{}

bool SDCardReaderInterface::init() 
{
    return SD.begin(PIN_SD_CS);
}

bool SDCardReaderInterface::writeFile(const char* filename, const char* data) 
{
    File file = SD.open(filename, FILE_WRITE);
    if (!file) 
    {
        return false;
    }
    file.println(data);
    file.close();
    return true;
}

String SDCardReaderInterface::readFile(const char* filename) 
{
    File file = SD.open(filename);
    if (!file) 
    {
        return "";
    }
    String data = "";
    while (file.available()) 
    {
        data += (char)file.read();
    }
    file.close();
    return data;
}

bool SDCardReaderInterface::deleteFile(const char* filename) 
{
    return SD.remove(filename);
}