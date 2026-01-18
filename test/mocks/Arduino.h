#pragma once

// Arduino mock for native testing

#include <cstdint>
#include <cstddef>
#include <string>
#include <functional>

// Arduino types
using byte = uint8_t;
using word = uint16_t;

// String class mock
class String {
public:
    String() = default;
    String(const char* str) : _str(str ? str : "") {}
    String(const std::string& str) : _str(str) {}
    
    const char* c_str() const { return _str.c_str(); }
    size_t length() const { return _str.length(); }
    bool isEmpty() const { return _str.empty(); }
    
    bool operator==(const String& other) const { return _str == other._str; }
    bool operator==(const char* other) const { return _str == other; }
    String operator+(const String& other) const { return String(_str + other._str); }
    
private:
    std::string _str;
};

// Serial mock
class SerialMock {
public:
    void begin(unsigned long) {}
    void println(const char*) {}
    void println(const String&) {}
    void print(const char*) {}
    void print(const String&) {}
    void println(int) {}
    void print(int) {}
    void println(float) {}
    void print(float) {}
};

extern SerialMock Serial;

// Time functions mock
extern unsigned long _mockMillis;
inline unsigned long millis() { return _mockMillis; }
inline void delay(unsigned long) {}

// F() macro mock
#define F(string_literal) (string_literal)

// PROGMEM mock
#define PROGMEM

// Pin modes
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2

// Digital values
#define HIGH 1
#define LOW 0

// Mock GPIO functions
inline void pinMode(uint8_t, uint8_t) {}
inline void digitalWrite(uint8_t, uint8_t) {}
inline int digitalRead(uint8_t) { return LOW; }
inline int analogRead(uint8_t) { return 0; }
