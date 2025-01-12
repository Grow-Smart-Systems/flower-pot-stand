#include "Menu.h"

Menu::Menu()
{
}


void Menu::ShowMenu() const
{
    // // slider  menu
    // int currentMenuPosition = 0;
    // int menuSize = _menu.size();

    // if (_selectedItem == 0)
    //     currentMenuPosition = 0;
    // if (_selectedItem > 0 && _selectedItem < menuSize - 1)
    //     currentMenuPosition = 1;
    // if (_selectedItem == menuSize - 1)
    //     currentMenuPosition = 2;

    // bool upTriangle = false;
    // if (_selectedItem > 1 && menuSize > 2)
    //     upTriangle = true;

    // bool downTriangle = false;
    // if (_selectedItem < menuSize - 2 && menuSize > 2)
    //     downTriangle = true;

    // String text0{ "" }, text1{ "" }, text2{ "" };
    // switch (menuSize)
    // {
    // case 1:
    //     text0 = _menu[_selectedItem].GetName();
    //     break;
    // case 2:
    //     if (_selectedItem == 0)
    //     {
    //         text0 = _menu[_selectedItem].GetName();
    //         text1 = _menu[_selectedItem + 1].GetName();
    //     }
    //     else
    //     {
    //         text0 = _menu[_selectedItem - 1].GetName();
    //         text1 = _menu[_selectedItem].GetName();
    //     }
    //     break;
    // default:
    //     if (currentMenuPosition == 0)
    //     {
    //         text0 = _menu[_selectedItem].GetName();
    //         text1 = _menu[_selectedItem + 1].GetName();
    //         text2 = _menu[_selectedItem + 2].GetName();
    //     }
    //     else if (currentMenuPosition == 1)
    //     {
    //         text0 = _menu[_selectedItem - 1].GetName();
    //         text1 = _menu[_selectedItem].GetName();
    //         text2 = _menu[_selectedItem + 1].GetName();
    //     }
    //     else if (currentMenuPosition == 2)
    //     {
    //         text0 = _menu[_selectedItem - 2].GetName();
    //         text1 = _menu[_selectedItem - 1].GetName();
    //         text2 = _menu[_selectedItem].GetName();
    //     }
    //     break;
    // }

    // _display->printMainMenu(currentMenuPosition, upTriangle, downTriangle, text0, text1, text2);
}

MenuItem& Menu::GetSelectedItem()
{
    return _menuItems[_selectedItem];
}

Data::DisplayMenu Menu::GetDisplayMenu() const
{
    return _displayMenu;
}

bool Menu::IsExecuted() const
{
    return _isExecuted;
}

void Menu::SetDisplayMenu(DisplayMenu displayMenu)
{
    _displayMenu = displayMenu;
}

// void Menu::ShowSubMenu() const
// {
//     _menu[_selectedItem].DisplaySubMenu();
// }

// void Menu::ShowFunctionalScreen() const
// {
//     _display->printFunctionMenu();
// }

void Menu::ExecuteMenu()
{
    _isExecuted = true;

    auto& data = Data::getInstance();
    if (data.getDisplayMenu() == Data::DisplayMenu::MAIN_MENU)
        _menu[_selectedItem].Execute();
    else if (data.getDisplayMenu() == Data::DisplayMenu::SUB_MENU)
        _menu[_selectedItem].SelectedItemExecute();
}

void Menu::Back()
{
    _isExecuted = false;

    auto& data = Data::getInstance();
    if (data.getDisplayMenu() == Data::DisplayMenu::SUB_MENU)
        data.setDisplayMenu(Data::DisplayMenu::MAIN_MENU);
    else if (data.getDisplayMenu() == Data::DisplayMenu::FUNCTIONAL_SCREEN)
        data.setDisplayMenu(Data::DisplayMenu::SUB_MENU);
}

void Menu::SelectNextItem()
{
    auto status = Data::getInstance().getDisplayMenu();

    if (_selectedItem < _menuItems.size() - 1)
        ++_selectedItem;
}

void Menu::SelectPreviousItem()
{
    auto status = Data::getInstance().getDisplayMenu();
    if (status == Data::DisplayMenu::MAIN_MENU)
    {
        if (_selectedItem > 0)
            --_selectedItem;
    }
    else if (status == Data::DisplayMenu::SUB_MENU)
    {
        _menu[_selectedItem].SelectPreviousItem();
    }
}
