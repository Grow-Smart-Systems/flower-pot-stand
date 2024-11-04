#include "Screen.h"

Screen::Screen()
{
    _display = std::make_shared<Display>();
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

    _menu = std::make_shared<Menu>(_display);

    MenuItem mainMenuItem1("Item 1");
    {
        MenuItem subMenuItem1("SubItem 1.1");
        MenuItem subMenuItem2("SubItem 1.2");
        MenuItem subMenuItem3("SubItem 1.3");

        mainMenuItem1.addSubMenu(subMenuItem1);
        mainMenuItem1.addSubMenu(subMenuItem2);
        mainMenuItem1.addSubMenu(subMenuItem3);
    }

    MenuItem mainMenuItem2("Item 2");
    {
        MenuItem subMenuItem1("SubItem 2.1");
        MenuItem subMenuItem2("SubItem 2.2");
        MenuItem subMenuItem3("SubItem 2.3");

        mainMenuItem2.addSubMenu(subMenuItem1);
        mainMenuItem2.addSubMenu(subMenuItem2);
        mainMenuItem2.addSubMenu(subMenuItem3);
    }

    MenuItem mainMenuItem3("Строка 3");
    {
        MenuItem subMenuItem1("SubItem 3.1");
        MenuItem subMenuItem2("SubItem 3.2");
        MenuItem subMenuItem3("SubItem 3.3");

        mainMenuItem3.addSubMenu(subMenuItem1);
        mainMenuItem3.addSubMenu(subMenuItem2);
        mainMenuItem3.addSubMenu(subMenuItem3);
    }

    MenuItem mainMenuItem4("СТРОКА 4");
    {
        MenuItem subMenuItem1("подменю 4.1");
        MenuItem subMenuItem2("Подменю 4.2");
        MenuItem subMenuItem3("ПОДМЕНЮ 4.3");

        mainMenuItem4.addSubMenu(subMenuItem1);
        mainMenuItem4.addSubMenu(subMenuItem2);
        mainMenuItem4.addSubMenu(subMenuItem3);
    }

    MenuItem mainMenuItem5(String("Строка 5"));
    {
        MenuItem subMenuItem1(String("строка 5.1"));
        MenuItem subMenuItem2(String("Строка 5.2"));
        MenuItem subMenuItem3(String("СТРОКА 5.3"));

        mainMenuItem5.addSubMenu(subMenuItem1);
        mainMenuItem5.addSubMenu(subMenuItem2);
        mainMenuItem5.addSubMenu(subMenuItem3);
    }

    _menu->addItem(mainMenuItem1);
    _menu->addItem(mainMenuItem2);
    _menu->addItem(mainMenuItem3);
    _menu->addItem(mainMenuItem4);
    _menu->addItem(mainMenuItem5);
}

void Screen::printInitializeScreen()
{
    _display->dispayOn();
}

void Screen::printMenu()
{
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    if (Data::getInstance().getDisplayMenu() == Data::DisplayMenu::MAIN_MENU)
        _menu->showMenu();
    else if (Data::getInstance().getDisplayMenu() == Data::DisplayMenu::SUB_MENU)
        _menu->showSubMenu();
    // else if (Data::getInstance().getDisplayMenu() == Data::DisplayMenu::FUCTIONAL_MENU)
    //     _menu->executeMenu();
    // else
    //     _menu->showMenu();
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

    _menu->selectPreviousItem();
}

void Screen::movemenuDown()
{
    Serial.println("Screen | movemenuDown");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menu->selectNextItem();
}

void Screen::movemenuBack()
{
    Serial.println("Screen | movemenuBack");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    Data::getInstance().setDisplayMenu(Data::DisplayMenu::MAIN_MENU);
}

void Screen::movemenuEnter()
{
    Serial.println("Screen | movemenuEnter");
    if (Data::getInstance().getDisplayMode() != Data::DisplayMode::MENU_MODE)
        return;

    _menu->executeMenu();
}
