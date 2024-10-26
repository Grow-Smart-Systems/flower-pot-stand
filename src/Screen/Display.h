#pragma once

#include <Arduino.h>
#include <memory>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "../Common/Data.h"

// Common defines for OLED display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
//

// Sub-menu defines
#define SM_STRING_0 10
#define SM_STRING_1 20
#define SM_STRING_2 30
#define SM_STRING_3 40
#define SM_STRING_4 50
#define SM_STRING_5 60

#define SM_STRING_X 36

#define SM_FRAME_X 34
#define SM_FRAME_WIDTH 92
#define SM_FRAME_HEIGHT 10
#define SM_FRAME_RADIUS 4
#define SM_FRAME_X_OFFSET 2
#define SM_FRAME_Y_OFFSET 6
//

// statusbar defines
#define CLOCK_POS_X 0
#define CLOCK_POS_Y 0

#define ICON_POS_1_X 0
#define ICON_POS_1_Y 16

#define ICON_POS_2_X 16
#define ICON_POS_2_Y 16

#define ICON_POS_3_X 0
#define ICON_POS_3_Y 32

#define ICON_POS_4_X 16
#define ICON_POS_4_Y 32

#define ICON_POS_5_X 0
#define ICON_POS_5_Y 48

#define ICON_POS_6_X 16
#define ICON_POS_6_Y 48
//

// Frame defines for main menu
#define MM_FRAME_HEIGHT 14
#define MM_COMMON_FRAME_WIDTH 85
#define MM_COMMON_FRAME_RADIUS 3

#define MM_ICON_FRAME_WIDTH 14
#define MM_ICON_FRAME_RADIUS 4

#define MM_TEXT_FRAME_WIDTH 72
#define MM_TEXT_FRAME_RADIUS 4

#define MM_TEXT_X_OFFSET 18
#define MM_TEXT_Y_OFFSET 9

#define MM_STRING_0_X 34
#define MM_STRING_0_Y 9

#define MM_STRING_1_X 34
#define MM_STRING_1_Y 25

#define MM_STRING_2_X 34
#define MM_STRING_2_Y 41
//

// defines movement triangles position
#define MT_DOWN_X0 64
#define MT_DOWN_Y0 58
#define MT_DOWN_X1 78
#define MT_DOWN_Y1 58
#define MT_DOWN_X2 71
#define MT_DOWN_Y2 62

#define MT_UP_X0 64
#define MT_UP_Y0 5
#define MT_UP_X1 78
#define MT_UP_Y1 5
#define MT_UP_X2 71
#define MT_UP_Y2 2
//

// Frame defines
#define FRAME_SUB_MENU_WIDTH 96
#define FRAME_SUB_MENU_HEIGHT 64
#define FRAME_SUB_MENU_RADIUS 4

#define FRAME_SUB_MENU_POS_X 32
#define FRAME_SUB_MENU_POS_Y 0

#define FRAME_RADIUS 3

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

    void printFunctionMenu();

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

    /// @brief Экземпляр дисплея объекта для SSD1306 с разрешением 128x64, с использованием аппаратного I2C.
    std::shared_ptr<Adafruit_SSD1306> _display = nullptr;
};