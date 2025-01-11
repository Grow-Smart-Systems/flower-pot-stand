#include "Display.h"
#include "Icons.h"
#include "fonts/Picopixel.h"
#include "BaseFunctionalScreens/TemperatureSensorScreen.h"
#include <Wire.h>


Display::Display()
{
    _display = std::shared_ptr<Adafruit_SSD1306>(new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET));
}

bool Display::init()
{
    Serial.println("Screen | Display init");
    if (!_display)
        return false;

    Serial.println("Screen | Display begin");
    if (!_display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println("Screen | Error begin code: " + String(_display->getWriteError()));
        return false;
    }
    _display->clearDisplay();
    _display->display();
    return true;
}

void Display::printMainMenu(int selectedString, bool upTriangle, bool downTriangle, const String& text0, const String& text1, const String& text2)
{
    _display->clearDisplay();

    printFrame(false);

    printMainMenuString(text0, MM_STRING_0_X, MM_STRING_0_Y, selectedString == 0 ? SELECTED : UNSELECTED);

    if (text1 != "")
        printMainMenuString(text1, MM_STRING_1_X, MM_STRING_1_Y, selectedString == 1 ? SELECTED : UNSELECTED);

    if (text2 != "")
        printMainMenuString(text2, MM_STRING_2_X, MM_STRING_2_Y, selectedString == 2 ? SELECTED : UNSELECTED);

    printMovementTriangles(upTriangle, downTriangle);

    printStatusBar();

    _display->display();
}

void Display::printSubMenu(int selectedString, const String& text0, const String& text1, const String& text2, const String& text3, const String& text4, const String& text5)
{
    _display->clearDisplay();

    printFrame(true);

    printSubMenuString(text0, SM_STRING_X, SM_STRING_0, selectedString == 0 ? SELECTED : UNSELECTED);

    if (text1 != "")
        printSubMenuString(text1, SM_STRING_X, SM_STRING_1, selectedString == 1 ? SELECTED : UNSELECTED);

    if (text2 != "")
        printSubMenuString(text2, SM_STRING_X, SM_STRING_2, selectedString == 2 ? SELECTED : UNSELECTED);

    if (text3 != "")
        printSubMenuString(text3, SM_STRING_X, SM_STRING_3, selectedString == 3 ? SELECTED : UNSELECTED);

    if (text4 != "")
        printSubMenuString(text4, SM_STRING_X, SM_STRING_4, selectedString == 4 ? SELECTED : UNSELECTED);

    if (text5 != "")
        printSubMenuString(text5, SM_STRING_X, SM_STRING_5, selectedString == 5 ? SELECTED : UNSELECTED);

    printStatusBar();

    _display->display();
}

void Display::printFunctionMenu(bool editMode)
{
    _display->clearDisplay();
    printFrame(false);

    auto& data = Data::getInstance();
    if (data.getDisplayFunctionalScreen() == Data::DisplayFunctionalScreen::TEMPERATURE_SENSOR_SCREEN)
    {
        if (!_functionalScreen)
            _functionalScreen = std::make_shared<TemperatureSensorScreen>();
        _functionalScreen->printScreen(_display);

    }

    _display->display();
}

void Display::dispayOn()
{
    _display->ssd1306_command(SSD1306_DISPLAYON);
}

void Display::displayOff()
{
    _display->ssd1306_command(SSD1306_DISPLAYOFF);
}

void Display::printStatusBar()
{
    auto& data = Data::getInstance();

    //Влажность
    if (data.getHumidityStatus() == Data::HumidityStatus::HIGH_HUMIDITY)
    {
        _display->drawBitmap(ICON_POS_1_X, ICON_POS_1_Y, iconWet, ICON_WIDTH, ICON_HEIGHT, SSD1306_WHITE);
    }
    else if (data.getHumidityStatus() == Data::HumidityStatus::LOW_HUMIDITY)
    {
        _display->drawBitmap(ICON_POS_1_X, ICON_POS_1_Y, iconDry, ICON_WIDTH, ICON_HEIGHT, SSD1306_WHITE);
    }
    //TODO: Доделать реализацию. Выводить статус бар с текущим временем и статусом сети и пр.
}

void Display::printFrame(bool menuFrame)
{
    _display->drawRoundRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, FRAME_RADIUS, SSD1306_WHITE);

    if (menuFrame)
        _display->drawRoundRect(SM_FRAME_X, 0, SM_FRAME_WIDTH, SM_FRAME_HEIGHT, SM_FRAME_RADIUS, SSD1306_WHITE);
}

void Display::printMainMenuString(String text, uint8_t x, uint8_t y, SELECTED_STATUS status = UNSELECTED)
{
    if (status == UNSELECTED)
    {
        //Общая рамка
        _display->drawRoundRect(x, y, MM_COMMON_FRAME_WIDTH, MM_FRAME_HEIGHT, MM_COMMON_FRAME_RADIUS, SSD1306_WHITE);

        //Рамка иконки
        _display->drawRoundRect(x, y, MM_ICON_FRAME_WIDTH, MM_FRAME_HEIGHT, MM_ICON_FRAME_RADIUS, SSD1306_WHITE);

        //Рамка текста
        _display->drawRoundRect(x + MM_ICON_FRAME_WIDTH - 1, y, MM_TEXT_FRAME_WIDTH, MM_FRAME_HEIGHT, MM_TEXT_FRAME_RADIUS, SSD1306_WHITE);
    }
    else
    {
        //Общая рамка
        _display->fillRoundRect(x, y, MM_COMMON_FRAME_WIDTH, MM_FRAME_HEIGHT, MM_COMMON_FRAME_RADIUS, SSD1306_WHITE);

        //Рамка иконки
        _display->drawRoundRect(x + 1, y + 1, MM_ICON_FRAME_WIDTH - 2, MM_FRAME_HEIGHT - 2, MM_COMMON_FRAME_RADIUS, SSD1306_BLACK);

        //Рамка текста
        _display->drawRoundRect(x + MM_ICON_FRAME_WIDTH, y + 1, MM_TEXT_FRAME_WIDTH - 2, MM_FRAME_HEIGHT - 2, MM_COMMON_FRAME_RADIUS, SSD1306_BLACK);
    }

    // Текст
    _display->setCursor(x + MM_TEXT_X_OFFSET, y + MM_TEXT_Y_OFFSET);
    _display->setFont(&Picopixel);
    _display->setTextSize(1);
    _display->setTextColor(status == SELECTED ? SSD1306_BLACK : SSD1306_WHITE);
    _display->print(text);
}

void Display::printSubMenuString(String text, uint8_t x, uint8_t y, SELECTED_STATUS status)
{
    //Общая рамка
    if (status == SELECTED)
    {
        _display->fillRoundRect(x - SM_FRAME_X_OFFSET, y - SM_FRAME_Y_OFFSET, SM_STRING_FRAME_WIDTH, SM_STRING_FRAME_HEIGHT, FRAME_SUB_MENU_RADIUS, SSD1306_WHITE);
    }

    //Текст
    _display->setCursor(x, y);
    _display->setFont(&Picopixel);
    _display->setTextSize(1);
    _display->setTextColor(status == SELECTED ? SSD1306_BLACK : SSD1306_WHITE);
    _display->print(text);
}

void Display::printMovementTriangles(bool upTriangle, bool downTriangle)
{
    // Треуголньик "вверх"
    if (upTriangle)
        _display->fillTriangle(MT_UP_X0, MT_UP_Y0, MT_UP_X1, MT_UP_Y1, MT_UP_X2, MT_UP_Y2, SSD1306_WHITE);

    // Треугольник "вниз"
    if (downTriangle)
        _display->fillTriangle(MT_DOWN_X0, MT_DOWN_Y0, MT_DOWN_X1, MT_DOWN_Y1, MT_DOWN_X2, MT_DOWN_Y2, SSD1306_WHITE);
}

void Display::printFooter(bool editMode)
{
    //TODO: Доделать реализацию. Выводить подвал экрана
    // режим редактирования меняет оттображаемые кнопки 
}

void Display::printHeader(String textHeader)
{
    //TODO: Доделать реализацию. Выводить заголовок экрана
}
