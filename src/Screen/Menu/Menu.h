#pragma once

#include <Arduino.h>
#include <memory>
#include <vector>

#include "../../Common/EnumClasses.h"
#include "../../Common/Data.h"
#include "../Display/Display.h"
#include "MenuItem.h"


class Display;
class MenuItem;

/// @brief Класс меню
class Menu final
{

public:
    /// @brief Конструктор
    /// @param parentMenu Родительское меню
    /// @param displayMenu Тип отображения меню
    Menu(std::shared_ptr<Menu> parentMenu = nullptr, DisplayMenu displayMenu = DisplayMenu::SUB_MENU);

    /// @brief Деструктор
    ~Menu();

    /// @brief Получает выбранный пункта меню
    /// @return Выбранный пункт меню
    const MenuItem& GetSelectedItem();

    /// @brief Получает пункт меню по индексу
    /// @param index Индекс пункта меню
    /// @return Пункт меню
    const MenuItem& GetMenuItemAt(int index);

    /// @brief Устанавливает пункты меню
    /// @param menuItems Пункты меню
    void SetMenuItems(const std::vector<MenuItem>& menuItems);

    /// @brief Добавляет пункт меню
    /// @param menuItem Пункт меню
    void AddMenuItem(const MenuItem menuItem);

    /// @brief Устанавливает тип отображения меню
    /// @param displayMenu Тип отображения меню
    void SetDisplayMenu(DisplayMenu displayMenu);

    /// @brief Получает тип отображения меню
    /// @return Тип отображения меню
    DisplayMenu GetDisplayMenu() const;

    /// @brief Получает количество пунктов меню
    /// @return Количество пунктов меню
    int GetMenuItemsSize() const;

    /// @brief Получает текущий индекс
    /// @return Текущий индекс
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

    // Movement section end //

private:
    /// @brief Указатель на родительское меню
    std::shared_ptr<Menu> _parentMenu {nullptr};

    /// @brief Набор пунктов меню
    std::vector<MenuItem> _menuItems;

    /// @brief Текущий выбранный индекс пункта меню
    int _selectedItem {0};

    /// @brief Тип отображения меню
    DisplayMenu _displayMenu {DisplayMenu::SUB_MENU};
};
