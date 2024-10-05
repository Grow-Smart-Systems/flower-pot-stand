#pragma once

#include <Arduino.h>


class BoolArray 
    {
public:
    BoolArray(size_t size) : _size(size) 
    {
        _data = new uint8_t[(size + 7) / 8](); // Выделяем память для массива байтов

        // Заполняем массив нулями
        for (size_t i = 0; i < (size + 7) / 8; i++) {
            _data[i] = 0;
        }
    }

    ~BoolArray() 
    {
        delete[] _data;
    }

    bool get(size_t index) const {
        if (index >= _size) return false;
        return _data[index / 8] & (1 << (index % 8));
    }

    void set(size_t index, bool value) {
        if (index >= _size) return;
        if (value) {
            _data[index / 8] |= (1 << (index % 8));
        } else {
            _data[index / 8] &= ~(1 << (index % 8));
        }
    }

private:
    size_t _size;
    uint8_t* _data;
};