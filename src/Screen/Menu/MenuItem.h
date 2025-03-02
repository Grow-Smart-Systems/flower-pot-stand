#pragma once

#include <Arduino.h>
#include <memory>

class Menu;

class MenuItem
{

public:
    /// @brief Конструктор
    /// @param name Имя пункта меню
    /// @param action Действие пункта меню
    /// @param subMenu Указатель на подменю
    MenuItem(const String& name, std::function<void()> action = nullptr, std::shared_ptr<Menu> subMenu = nullptr);

    /// @brief Конструктор по умолчанию
    MenuItem() = default;

    ~MenuItem() = default;

    void SetAction(std::function<void()> action);

    void SetSubMenu(std::shared_ptr<Menu> subMenu);

    String GetName() const;

    void Execute();

    std::shared_ptr<Menu> GetMenu();

private:
    /// @brief Имя пункта меню
    String _name {"[Empty menu item]"};

    /// @brief Действие пункта меню
    std::function<void()> _action {nullptr};

    /// @brief Подменю
    std::shared_ptr<Menu> _subMenu {nullptr};
};
