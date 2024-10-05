#include "MaintenanceEEPROM.h"

#define ZERO_BYTE 0x00
#define MAX_BYTE 0xFF

MaintenanceEEPROM::MaintenanceEEPROM()
{
}

MaintenanceEEPROM::~MaintenanceEEPROM()
{
}

BoolArray MaintenanceEEPROM::ReadWriteMemoryTest(unsigned int from, unsigned int to)
{
    // Байт для сохранения данных из EEPROM.
    byte savedByte{0x00};
    byte testByte{0x00};

    BoolArray resArray(EEPROM.length());

    // Определяем диапазон тестирования если он превышает размер EEPROM
    to = constrain(to, 0, EEPROM.length());
    to == 0 ? to = EEPROM.length() : to;

    // Проходим в цикле всю память EEPROM.
    for (int i = from; i < to; i++)
    {
        // Запоминаем то, что записано в ячейке
        savedByte = EEPROM.read(i);
        
        // Записываем в ячейку нули
        EEPROM.write(i, ZERO_BYTE);
        testByte = EEPROM.read(i);
        if (testByte != ZERO_BYTE)
        {
            Serial.println(("Cell " + String(i) + " is corrupted (Test 1)"));
            continue;
        }
        // Записываем в ячейку единицы
        EEPROM.write(i, MAX_BYTE);
        testByte = EEPROM.read(i);
        if (testByte != MAX_BYTE)
        {
            Serial.println(("Cell " + String(i) + " is corrupted (Test 2)"));
            continue;
        }
        // Восстанавливаем данные
        EEPROM.write(i, savedByte);
        testByte = EEPROM.read(i);
        if (testByte != savedByte)
        {
            Serial.println(("Cell " + String(i) + " is corrupted (Test 3)"));
            continue;
        }

        resArray.set(i, true);
    }
    Serial.println("The test is completed.");
    return resArray;
}

