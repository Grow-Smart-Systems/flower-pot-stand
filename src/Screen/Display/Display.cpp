#include "Display.h"
#include "Icons.h"
#include <Fonts/Picopixel.h>
#include <Wire.h>


Display::Display()
{
    _display = std::shared_ptr<Adafruit_SSD1306>(new Adafruit_SSD1306(SCREEN_WIDTH,
                                                                      SCREEN_HEIGHT,
                                                                      &Wire,
                                                                      OLED_RESET));
}

bool Display::Init()
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

void Display::PrintMainMenu(int selectedString,
                            bool upTriangle,
                            bool downTriangle,
                            const std::string& text0,
                            const std::string& text1,
                            const std::string& text2)
{
    _display->clearDisplay();

    printFrame(false);

    printMainMenuString(text0,
                        MM_STRING_0_X,
                        MM_STRING_0_Y,
                        selectedString == 0 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    if (!text1.empty())
        printMainMenuString(text1,
                            MM_STRING_1_X,
                            MM_STRING_1_Y,
                            selectedString == 1 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    if (!text2.empty())
        printMainMenuString(text2,
                            MM_STRING_2_X,
                            MM_STRING_2_Y,
                            selectedString == 2 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    printMovementTriangles(upTriangle, downTriangle);

    printStatusBar();

    _display->display();
}

void Display::PrintSubMenu(int selectedString,
                           const std::string& text0,
                           const std::string& text1,
                           const std::string& text2,
                           const std::string& text3,
                           const std::string& text4,
                           const std::string& text5)
{
    _display->clearDisplay();

    printFrame(true);

    printSubMenuString(text0, SM_STRING_X, SM_STRING_0,
        selectedString == 0 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    if (!text1.empty())
        printSubMenuString(text1, SM_STRING_X, SM_STRING_1,
            selectedString == 1 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    if (!text2.empty())
        printSubMenuString(text2, SM_STRING_X, SM_STRING_2,
            selectedString == 2 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    if (!text3.empty())
        printSubMenuString(text3, SM_STRING_X, SM_STRING_3,
            selectedString == 3 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    if (!text4.empty())
        printSubMenuString(text4, SM_STRING_X, SM_STRING_4,
            selectedString == 4 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    if (!text5.empty())
        printSubMenuString(text5, SM_STRING_X, SM_STRING_5,
            selectedString == 5 ? SELECTED_STATUS::SELECTED : SELECTED_STATUS::UNSELECTED);

    printStatusBar();

    _display->display();
}

void Display::PrintFunctionMenu(bool editMode)
{
    _display->clearDisplay();
    printFrame(false);

    auto& data = Data::GetInstance();
    if (data.GetDisplayFunctionalScreen() == DisplayFunctionalScreen::TEMPERATURE_SENSOR_SCREEN)
        _functionalScreen = std::make_shared<TemperatureSensorScreen>(_display);
    else
        _functionalScreen = std::make_shared<BaseFunctionalScreen>(_display);

    _functionalScreen->printScreen();
    _functionalScreen->printFooter();
    _functionalScreen->printHeader();

    _display->display();
}

void Display::PrintInitializeScreen()
{
    _display->clearDisplay();
    _display->setFont(&Picopixel);
    _display->setTextColor(SSD1306_WHITE);

    // Логотип
    _display->setTextSize(2);
    _display->setCursor(20, 30);
    _display->println("LOADING...");

    // Версия
    _display->setTextSize(1);
    _display->setCursor(0, 60);
    _display->println("build: v." + String(BUILD_TIME));

    _display->display();
}

void Display::DispayOn()
{
    _display->ssd1306_command(SSD1306_DISPLAYON);
}

void Display::DisplayOff()
{
    _display->ssd1306_command(SSD1306_DISPLAYOFF);
}

void Display::printStatusBar()
{
    auto& data = Data::GetInstance();

    //Влажность
    if (data.GetHumidityStatus() == HumidityStatus::HIGH_HUMIDITY)
    {
        _display->drawBitmap(ICON_POS_1_X, ICON_POS_1_Y, iconWet, ICON_WIDTH, ICON_HEIGHT, SSD1306_WHITE);
    }
    else if (data.GetHumidityStatus() == HumidityStatus::LOW_HUMIDITY)
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

void Display::printMainMenuString(const std::string& text, uint8_t x, uint8_t y, SELECTED_STATUS status)
{
    if (status == SELECTED_STATUS::UNSELECTED)
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
    _display->setTextColor(status == SELECTED_STATUS::SELECTED ? SSD1306_BLACK : SSD1306_WHITE);
    _display->print(text.c_str());
}


void Display::printSubMenuString(const std::string& text, uint8_t x, uint8_t y, SELECTED_STATUS status)
{
    //Общая рамка
    if (status == SELECTED_STATUS::SELECTED)
    {
        _display->fillRoundRect(x - SM_FRAME_X_OFFSET, y - SM_FRAME_Y_OFFSET, SM_STRING_FRAME_WIDTH, SM_STRING_FRAME_HEIGHT, FRAME_SUB_MENU_RADIUS, SSD1306_WHITE);
    }

    //Текст
    _display->setCursor(x, y);
    _display->setFont(&Picopixel);
    _display->setTextSize(1);
    _display->setTextColor(status == SELECTED_STATUS::SELECTED ? SSD1306_BLACK : SSD1306_WHITE);
    _display->print(text.c_str());
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

void Display::printHeader(const std::string& textHeader)
{

}

void Display::printFooter(bool editMode)
{
    
}
