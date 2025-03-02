#include "Screen.h"
#include "Menu/Menu.h"

Screen::Screen()
{
    _display = std::make_shared<Display>();
    _menuController = std::make_shared<MenuController>();
}

bool Screen::init()
{
    bool result = _display->init();
    if (!result)
    {
        Serial.println("Screen | Error: Display initialization failed");
        return false;
    }
    initMenu();
    return true;
}

void Screen::initMenu()
{
    Data::getInstance().setDisplayMode(Data::DisplayMode::MENU_MODE);
    Data::getInstance().setDisplayMenu(Data::DisplayMenu::MAIN_MENU);

    auto rootMenu = _menuController->GetRootMenu();
    auto sensorsMenu = _menuController->CreateMenuItem("Sensors", rootMenu, nullptr);
    {
        auto tempMenuItem = _menuController->CreateMenuItem("Temperature", sensorsMenu, std::bind(&Screen::temperatureAction, this));
        tempMenuItem->SetDisplayMenu(Data::DisplayMenu::FUNCTIONAL_MENU);

        auto humidityMenuItem = _menuController->CreateMenuItem("Humidity", sensorsMenu, nullptr);
        humidityMenuItem->SetDisplayMenu(Data::DisplayMenu::FUNCTIONAL_MENU);

        auto luxMenuItem = _menuController->CreateMenuItem("Lux", sensorsMenu, nullptr);
        luxMenuItem->SetDisplayMenu(Data::DisplayMenu::FUNCTIONAL_MENU);
    }

    auto settingsMenu = _menuController->CreateMenuItem("Settings", rootMenu, nullptr);
    {
        auto wifiMenuItem = _menuController->CreateMenuItem("WiFi", settingsMenu, nullptr);
        wifiMenuItem->SetDisplayMenu(Data::DisplayMenu::FUNCTIONAL_MENU);

        auto serviceMenuItem = _menuController->CreateMenuItem("Service connection", settingsMenu, nullptr);
        serviceMenuItem->SetDisplayMenu(Data::DisplayMenu::FUNCTIONAL_MENU);
    }

    auto aboutMenu = _menuController->CreateMenuItem("About", rootMenu, nullptr);
    {
        auto versionMenuItem = _menuController->CreateMenuItem("Version", aboutMenu, nullptr);
        versionMenuItem->SetDisplayMenu(Data::DisplayMenu::FUNCTIONAL_MENU);

        auto authorMenuItem = _menuController->CreateMenuItem("Author", aboutMenu, nullptr);
        authorMenuItem->SetDisplayMenu(Data::DisplayMenu::FUNCTIONAL_MENU);
    }
}

void Screen::temperatureAction()
{
    Serial.println("Screen | temperatureAction");
    Data::getInstance().setDisplayMenu(Data::DisplayMenu::FUNCTIONAL_MENU);
    Data::getInstance().setDisplayFunctionalScreen(Data::DisplayFunctionalScreen::TEMPERATURE_SENSOR_SCREEN);
}

void Screen::printInitializeScreen()
{
    _display->dispayOn();
    _display->printInitializeScreen();
}

void Screen::printMenu()
{
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menuController->DisplayMenu();
}

void Screen::showMenu()
{
    auto& data = Data::getInstance();
    data.setDisplayMode(Data::DisplayMode::MENU_MODE);
    data.setDisplayMenu(Data::DisplayMenu::MAIN_MENU);
}

void Screen::movemenuUp()
{
    Serial.println("Screen | movemenuUp");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menuController->NavigateUp();
}

void Screen::movemenuDown()
{
    Serial.println("Screen | movemenuDown");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menuController->NavigateDown();
}

void Screen::movemenuBack()
{
    Serial.println("Screen | movemenuBack");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menuController->Back();
}

void Screen::movemenuEnter()
{
    Serial.println("Screen | movemenuEnter");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menuController->SelectOption();
}
