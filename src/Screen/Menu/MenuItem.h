#pragma once

#include <Arduino.h>
#include <vector>

#include "../Display/Display.h"

#define SUB_MENU_ITEMS_SIZE 5

class Display;

class MenuItem
{
    const float INVERTED_SUB_MENU_ITEMS_SIZE{ 1.0f / 5.0f };

public:
    MenuItem(const String& name, std::function<void()> action = nullptr, std::shared_ptr<Menu> subMenu = nullptr);
    ~MenuItem() = default;

    void AddAction(std::function<void()> action);

    void AddSubMenu(std::shared_ptr<Menu> subMenu);

    String GetName() const;

    void Execute();

    std::shared_ptr<Menu> GetItemMenu();

private:

    /// @brief Имя пункта меню
    String _name;

    /// @brief Действие пункта меню
    std::function<void()> _action;

    /// @brief Подменю
    std::shared_ptr<Menu> _subMenu{ nullptr };
};
