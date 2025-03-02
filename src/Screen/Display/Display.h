#pragma once

#include <Arduino.h>
#include <memory>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "DisplayDefines.h"
#include "FunctionalScreens/BaseFunctionalScreen.h"
#include "FunctionalScreens/TemperatureSensorScreen.h"
#include "../../Common/Data.h"

class Display final
{
public:
    Display();

    ~Display() = default;

    /// @brief Инициализация экрана
    /// @return true - успешно, false - ошибка
    bool Init();

    /// @brief Печать начального меню на экране
    /// @param selectedString Выбранная строка
    /// @param upTriangle Нарисовать треугольник "вверх"
    /// @param downTriangle Нарисовать треугольник "вниз"
    /// @param text0 Текст строки 0 меню
    /// @param text1 Текст строки 1 меню
    /// @param text2 Текст строки 2 меню
    void PrintMainMenu(int selectedString,
                       bool upTriangle,
                       bool downTriangle,
                       const std::string& text0,
                       const std::string& text1 = "",
                       const std::string& text2 = "");

    /// @brief Печать подменю на экране
    /// @param selectedString Выбранная строка
    /// @param text0 Текст строки 0 меню
    /// @param text1 Текст строки 1 меню
    /// @param text2 Текст строки 2 меню
    /// @param text3 Текст строки 3 меню
    /// @param text4 Текст строки 4 меню
    /// @param text5 Текст строки 5 меню
    void PrintSubMenu(int selectedString,
                      const std::string& text0,
                      const std::string& text1 = "",
                      const std::string& text2 = "",
                      const std::string& text3 = "",
                      const std::string& text4 = "",
                      const std::string& text5 = "");

    //
    void PrintFunctionMenu(bool editMode = false);

    void PrintInitializeScreen();

    void DispayOn();

    void DisplayOff();

protected:
    enum class SELECTED_STATUS
    {
        SELECTED,
        UNSELECTED
    };

    void printStatusBar();

    void printFrame(bool menuFrame = false);

    void printMainMenuString(const std::string& text, uint8_t x, uint8_t y, SELECTED_STATUS status);

    void printSubMenuString(const std::string& text, uint8_t x, uint8_t y, SELECTED_STATUS status);

    void printMovementTriangles(bool upTriangle = false, bool downTriangle = false);

    void printFooter(bool editMode = false);

    void printHeader(const std::string& textHeader);

private:
    /// @brief Экземпляр дисплея объекта для SSD1306 с разрешением 128x64, с использованием аппаратного I2C.
    std::shared_ptr<Adafruit_SSD1306> _display {nullptr};

    std::shared_ptr<BaseFunctionalScreen> _functionalScreen {nullptr};
};