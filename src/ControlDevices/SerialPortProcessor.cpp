#include "SerialPortProcessor.h"
#include "../Common/Data.h"


void SerialPortProcessor::process(const String& command)
{
    if (processMovementCommands(command))
        return;

    // do something else
}

bool SerialPortProcessor::processMovementCommands(const String& command)
{
    if (command == "UP" || command == "1")
    {
        Data::getInstance().getScreen()->movemenuUp();
        return true;
    }
    else if (command == "DOWN" || command == "2")
    {
        Data::getInstance().getScreen()->movemenuDown();
        return true;
    }
    else if (command == "BACK" || command == "3")
    {
        Data::getInstance().getScreen()->movemenuBack();
        return true;
    }
    else if (command == "ENTER" || command == "4")
    {
        Data::getInstance().getScreen()->movemenuEnter();
        return true;
    }
    return false;
}