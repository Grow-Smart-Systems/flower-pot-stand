#include "Debug.h"

Debug* Debug::getInstance(Baudrate baudrate)
{
    static Debug* instance = nullptr;    
    if (instance == nullptr)
        instance = new Debug(baudrate);
    return instance;
}

Debug::Debug(Baudrate baudrate)
{
    Serial.begin(static_cast<uint32_t>(baudrate));
}

Debug::~Debug()
{
    Serial.end();
}

template<typename T>
Debug& Debug::operator<<(T data)
{
    checkType(data);
    Serial.print(data);
    return *this;
}

char Debug::endl()
{
    return '\n';
}

template<typename T>
void Debug::printLine(T data)
{
    checkType(data);
    *this << data << endl();
}

template<typename T>
void Debug::checkType(T data)
{
    // Ограничение на вывод только для типов данных, которые поддерживает Serial.print
    static_assert(
        is_same<T, int>::value ||
        is_same<T, long>::value ||
        is_same<T, unsigned int>::value ||
        is_same<T, unsigned long>::value ||
        is_same<T, float>::value ||
        is_same<T, double>::value ||
        is_same<T, char>::value ||
        is_same<T, const char*>::value,
        "class Debug: Type not supported by Serial.print"
    );
}
