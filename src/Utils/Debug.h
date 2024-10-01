#pragma once

#include <Arduino.h>

/// @brief Класс для вывода отладочной информации через Serial
class  Debug
{
public:
    /// @brief Перечисление скоростей передачи данных
    /// @note Поддерживаются скорости: 9600, 19200, 38400, 57600, 115200
    enum class Baudrate : uint32_t 
    {
        Baud9600 = 9600,
        Baud19200 = 19200,
        Baud38400 = 38400,
        Baud57600 = 57600,
        Baud115200 = 115200
    };

    /// @brief Получение экземпляра класса
    /// @param baudrate Скорость передачи данных
    /// @return  Указатель на экземпляр класса
    static Debug* getInstance(Baudrate baudrate = Baudrate::Baud9600);

    /// @brief Оператор вывода
    /// @tparam T Тип данных
    /// @param data Данные для вывода
    /// @note Поддерживаются типы данных: int, long, unsigned int, unsigned long, float, double, char, const char*
    template <typename T>
    Debug& operator<<(T data);

    /// @brief Оператор вывода перевода строки
    char endl();

    /// @brief Функция для вывода строки сразу с переводом строки в конце
    /// @tparam T Тип данных
    /// @param data Данные для вывода
    template <typename T>
    void printLine(T data);

private:
    /// @brief Конструктор копирования
    Debug(const Debug&) = delete;

    /// @brief Оператор присваивания
    Debug& operator=(const Debug&) = delete;

    /// @brief Конструктор
    /// @param baudrate Скорость передачи данных
    Debug(Baudrate baudrate = Baudrate::Baud9600);
    ~Debug();

    /// @brief Шаблонная структура для проверки типа данных
    /// @tparam T тип данных 1
    /// @tparam U тип данных 2
    /// @return false - типы данных не совпадают, true - типы данных совпадают
    /// @note Используються 2 структуры, чтобы сделать специализацию шаблона
    template<typename T, typename U>
    struct is_same
    {
        static const bool value = false;
    };
    template<typename T>
    struct is_same<T, T>
    {
        static const bool value = true;
    };

    /// @brief Функция проверки типа данных
    /// @tparam T Тип данных
    /// @param data Данные для проверки    
    template<typename T>
    void checkType(T data);
};

// Explicit template instantiation
template Debug& Debug::operator<< <int>(int data);
template Debug& Debug::operator<< <long>(long data);
template Debug& Debug::operator<< <unsigned int>(unsigned int data);
template Debug& Debug::operator<< <unsigned long>(unsigned long data);
template Debug& Debug::operator<< <float>(float data);
template Debug& Debug::operator<< <double>(double data);
template Debug& Debug::operator<< <char>(char data);
template Debug& Debug::operator<< <const char*>(const char* data);

template void Debug::printLine<int>(int data);
template void Debug::printLine<long>(long data);
template void Debug::printLine<unsigned int>(unsigned int data);
template void Debug::printLine<unsigned long>(unsigned long data);
template void Debug::printLine<float>(float data);
template void Debug::printLine<double>(double data);
template void Debug::printLine<char>(char data);
template void Debug::printLine<const char*>(const char* data);