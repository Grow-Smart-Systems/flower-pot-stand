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
        Data::GetInstance().GetScreen()->MovemenuUp();
        return true;
    }
    else if (command == "DOWN" || command == "2")
    {
        Data::GetInstance().GetScreen()->MovemenuDown();
        return true;
    }
    else if (command == "BACK" || command == "3")
    {
        Data::GetInstance().GetScreen()->MovemenuBack();
        return true;
    }
    else if (command == "ENTER" || command == "4")
    {
        Data::GetInstance().GetScreen()->MovemenuEnter();
        return true;
    }
    return false;
}