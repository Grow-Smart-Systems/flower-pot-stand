#pragma once

#include <Arduino.h>
#include <memory>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "DisplayDefines.h"
#include "BaseFunctionalScreen.h"
#include "../Common/Data.h"

class Display
{
public:
    Display();

    ~Display() = default;

    /// @brief Инициализация экрана
    /// @return true - успешно, false - ошибка
    bool init();

    /// @brief Печать начального меню на экране
    /// @param selectedString Выбранная строка
    /// @param upTriangle Нарисовать треугольник "вверх"
    /// @param downTriangle Нарисовать треугольник "вниз"
    /// @param text0 Текст строки 0 меню
    /// @param text1 Текст строки 1 меню
    /// @param text2 Текст строки 2 меню
    void printMainMenu(int selectedString, bool upTriangle, bool downTriangle, const String& text0, const String& text1 = "", const String& text2 = "");

    /// @brief Печать подменю на экране
    /// @param selectedString Выбранная строка
    /// @param text0 Текст строки 0 меню
    /// @param text1 Текст строки 1 меню
    /// @param text2 Текст строки 2 меню
    /// @param text3 Текст строки 3 меню
    /// @param text4 Текст строки 4 меню
    /// @param text5 Текст строки 5 меню
    void printSubMenu(int selectedString, const String& text0, const String& text1 = "", const String& text2 = "", const String& text3 = "", const String& text4 = "", const String& text5 = "");

    void printFunctionMenu(bool editMode = false);

    void dispayOn();

    void displayOff();

private:
    enum SELECTED_STATUS
    {
        SELECTED,
        UNSELECTED
    };

    void printStatusBar();

    void printFrame(bool menuFrame = false);

    void printMainMenuString(String text, uint8_t x, uint8_t y, SELECTED_STATUS status);

    void printSubMenuString(String text, uint8_t x, uint8_t y, SELECTED_STATUS status);

    void printMovementTriangles(bool upTriangle = false, bool downTriangle = false);

    void printFooter(bool editMode = false);

    void printHeader(String textHeader);

    /// @brief Экземпляр дисплея объекта для SSD1306 с разрешением 128x64, с использованием аппаратного I2C.
    std::shared_ptr<Adafruit_SSD1306> _display{ nullptr };

    std::unique_ptr<BaseFunctionalScreen> _functionalScreen{ nullptr };
};