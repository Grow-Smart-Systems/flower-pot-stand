#pragma once

// Wire mock for native testing

#include <cstdint>

class TwoWireMock {
public:
    void begin() {}
    void begin(int sda, int scl) {}
    void beginTransmission(uint8_t) {}
    uint8_t endTransmission() { return 0; }
    size_t write(uint8_t) { return 1; }
    int read() { return 0; }
    int available() { return 0; }
};

extern TwoWireMock Wire;

#define SDA 21
#define SCL 22
