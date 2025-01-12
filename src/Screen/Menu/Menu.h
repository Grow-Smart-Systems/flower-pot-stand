#pragma once

#include <Arduino.h>
#include <memory>

#include "../Display/Display.h"
#include "MenuItem.h"

class Display;
class MenuItem;

class Menu
{
    using DisplayMenu = Data::DisplayMenu;

public:
    Menu();

    ~Menu() = default;

    void ShowMenu() const;

    MenuItem& GetSelectedItem();

    DisplayMenu GetDisplayMenu() const;

    bool IsExecuted() const;

    void SetDisplayMenu(DisplayMenu displayMenu);

    // Movement section //

    /// @brief Перемещение вниз по меню
    void ExecuteMenu();

    void Back();

    void SelectNextItem();

    void SelectPreviousItem();

    // Movement section end//

private:
    std::vector<MenuItem> _menuItems;

    int _selectedItem{ 0 };

    bool _isExecuted{ false };

    Data::DisplayMenu _displayMenu{ Data::DisplayMenu::MAIN_MENU };
};
