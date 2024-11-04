#include "Menu.h"

Menu::Menu(std::shared_ptr<Display>& display)
    : _display(display)
{
}

void Menu::addItem(const MenuItem& item)
{
    _menu.push_back(item);
}

void Menu::showMenu() const
{
    // slider  menu
    int currentMenuPosition = 0;
    int menuSize = _menu.size();

    if (_selectedItem == 0)
        currentMenuPosition = 0;
    if (_selectedItem > 0 && _selectedItem < menuSize - 1)
        currentMenuPosition = 1;
    if (_selectedItem == menuSize - 1)
        currentMenuPosition = 2;

    bool upTriangle = false;
    if (_selectedItem > 1 && menuSize > 2)
        upTriangle = true;

    bool downTriangle = false;
    if (_selectedItem < menuSize - 2 && menuSize > 2)
        downTriangle = true;

    String text0 = "";
    String text1 = "";
    String text2 = "";

    if (menuSize == 1)
    {
        text0 = _menu[_selectedItem].getName();
    }
    else if (menuSize == 2)
    {
        if (_selectedItem == 0)
        {
            text0 = _menu[_selectedItem].getName();
            text1 = _menu[_selectedItem + 1].getName();
        }
        else
        {
            text0 = _menu[_selectedItem - 1].getName();
            text1 = _menu[_selectedItem].getName();
        }
    }
    else
        if (currentMenuPosition == 0)
        {
            text0 = _menu[_selectedItem].getName();
            text1 = _menu[_selectedItem + 1].getName();
            text2 = _menu[_selectedItem + 2].getName();
        }
        else if (currentMenuPosition == 1)
        {
            text0 = _menu[_selectedItem - 1].getName();
            text1 = _menu[_selectedItem].getName();
            text2 = _menu[_selectedItem + 1].getName();
        }
        else if (currentMenuPosition == 2)
        {
            text0 = _menu[_selectedItem - 2].getName();
            text1 = _menu[_selectedItem - 1].getName();
            text2 = _menu[_selectedItem].getName();
        }

    _display->printMainMenu(currentMenuPosition, upTriangle, downTriangle, text0, text1, text2);
}

void Menu::showSubMenu() const
{
    _menu[_selectedItem].displaySubMenu();
}

void Menu::executeMenu()
{
    _menu[_selectedItem].execute();
}

void Menu::selectNextItem()
{
    auto status = Data::getInstance().getDisplayMenu();
    if (status == Data::DisplayMenu::MAIN_MENU)
    {
        if (_selectedItem < _menu.size() - 1)
            ++_selectedItem;
    }
    else if (status == Data::DisplayMenu::SUB_MENU)
    {
        _menu[_selectedItem].selectNextItem();
    }
}

void Menu::selectPreviousItem()
{
    auto status = Data::getInstance().getDisplayMenu();
    if (status == Data::DisplayMenu::MAIN_MENU)
    {
        if (_selectedItem > 0)
            --_selectedItem;
    }
    else if (status == Data::DisplayMenu::SUB_MENU)
    {
        _menu[_selectedItem].selectPreviousItem();
    }
}
