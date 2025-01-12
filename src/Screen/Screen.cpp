#include "Screen.h"

Screen::Screen()
{
    _display = std::make_shared<Display>();
    _rootMenu = std::make_shared<Menu>(_display);
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

    _rootMenu = std::make_shared<Menu>();

    // MenuItem SensorsMenuItem("Sensors");
    // {
    //     MenuItem TemperatureMenuItem("Temperature", std::bind(&Screen::temperatureAction, this));
    //     {
    //         MenuItem TemperatureSensorDHT11MenuItem("DHT11");
    //         MenuItem TemperatureSensorDHT22MenuItem("DHT22");

    //         TemperatureMenuItem.addSubMenu(TemperatureSensorDHT11MenuItem);
    //         TemperatureMenuItem.addSubMenu(TemperatureSensorDHT22MenuItem);
    //     }
    //     MenuItem HumidityMenuItem("Humidity");
    //     MenuItem LuxMenuItem("Lux");

    //     SensorsMenuItem.addSubMenu(TemperatureMenuItem);
    //     SensorsMenuItem.addSubMenu(HumidityMenuItem);
    //     SensorsMenuItem.addSubMenu(LuxMenuItem);
    // }
    // _menu->addItem(SensorsMenuItem);

    // MenuItem mainMenuItem1("Item 1");
    // {
    //     MenuItem subMenuItem1("SubItem 1.1");
    //     MenuItem subMenuItem2("SubItem 1.2");
    //     MenuItem subMenuItem3("SubItem 1.3");

    //     mainMenuItem1.addSubMenu(subMenuItem1);
    //     mainMenuItem1.addSubMenu(subMenuItem2);
    //     mainMenuItem1.addSubMenu(subMenuItem3);
    // }

    // MenuItem mainMenuItem2("Item 2");
    // {
    //     MenuItem subMenuItem1("SubItem 2.1");
    //     MenuItem subMenuItem2("SubItem 2.2");
    //     MenuItem subMenuItem3("SubItem 2.3");

    //     mainMenuItem2.addSubMenu(subMenuItem1);
    //     mainMenuItem2.addSubMenu(subMenuItem2);
    //     mainMenuItem2.addSubMenu(subMenuItem3);
    // }

    // _menu->addItem(mainMenuItem1);
    // _menu->addItem(mainMenuItem2);
}

void Screen::temperatureAction()
{
    Serial.println("Screen | temperatureAction");
    Data::getInstance().setDisplayMenu(Data::DisplayMenu::FUNCTIONAL_SCREEN);
    Data::getInstance().setDisplayFunctionalScreen(Data::DisplayFunctionalScreen::TEMPERATURE_SENSOR_SCREEN);
}

void Screen::printInitializeScreen()
{
    _display->dispayOn();
    //TODO: Что-то красивое нарисовать
}

void Screen::printMenu()
{
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    std::function<std::shared_ptr<Menu>(std::shared_ptr<Menu>)> getCurrentMenu = [&](std::shared_ptr<Menu> menu) -> std::shared_ptr<Menu>
        {
            if (menu->IsExecuted())
                return menu->GetSelectedItem().GetItemMenu();
            return menu;
        };

    std::shared_ptr<Menu> currentMenu = getCurrentMenu(_rootMenu);
    while (currentMenu->IsExecuted())
    {
        currentMenu = getCurrentMenu(currentMenu);
    }

    if (currentMenu->GetDisplayMenu() == Data::DisplayMenu::MAIN_MENU)
    {
        //_display->printMainMenu(currentMenu->GetSelectedItem().GetName());
    }
    else if (currentMenu->GetDisplayMenu() == Data::DisplayMenu::SUB_MENU)
    {
        //_display->printSubMenu(currentMenu->GetSelectedItem().GetName());
    }
    else if (currentMenu->GetDisplayMenu() == Data::DisplayMenu::FUNCTIONAL_SCREEN)
    {
        //_display->printFunctionMenu();
    }
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

    _menu->SelectPreviousItem();
}

void Screen::movemenuDown()
{
    Serial.println("Screen | movemenuDown");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menu->SelectNextItem();
}

void Screen::movemenuBack()
{
    Serial.println("Screen | movemenuBack");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menu->Back();
}

void Screen::movemenuEnter()
{
    Serial.println("Screen | movemenuEnter");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menu->ExecuteMenu();
}
