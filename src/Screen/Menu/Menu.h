#pragma once

#include <Arduino.h>
#include <memory>
#include <vector>

#include "../../Common/Data.h"
#include "../Display/Display.h"
#include "MenuItem.h"


class Display;
class MenuItem;

class Menu
{
    using DisplayMenu = Data::DisplayMenu;

public:
    /// @brief Конструктор
    /// @param parentMenu Родительское меню
    /// @param displayMenu Тип отображения меню
    Menu(std::shared_ptr<Menu> parentMenu = nullptr, DisplayMenu displayMenu = DisplayMenu::SUB_MENU);

    ~Menu();

    const MenuItem& GetSelectedItem();

    const MenuItem& GetMenuItemAt(int index);

    void SetMenuItems(const std::vector<MenuItem>& menuItems);

    void AddMenuItem(const MenuItem menuItem);

    void SetDisplayMenu(DisplayMenu displayMenu);

    DisplayMenu GetDisplayMenu() const;

    int GetMenuItemsSize() const;

    int GetCurrentIndex() const;

    // Movement section //

    /// @brief Перемещение по меню в глубь
    std::shared_ptr<Menu> ExecuteMenu();

    /// @brief Перемещение по меню назад
    std::shared_ptr<Menu> Back();

    /// @brief Перемещение по меню вниз
    void SelectNextItem();

    /// @brief Перемещение по меню вверх
    void SelectPreviousItem();

    // Movement section end//

private:
    std::shared_ptr<Menu> _parentMenu {nullptr};

    std::vector<MenuItem> _menuItems;

    int _selectedItem {0};

    DisplayMenu _displayMenu {Data::DisplayMenu::SUB_MENU};
};
