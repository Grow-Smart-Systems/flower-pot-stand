#pragma once

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <memory>
#include <string>
#include <functional>

class Menu;

/// @brief Класс пункта меню
class MenuItem
{

public:
    /// @brief Конструктор
    /// @param name Имя пункта меню
    /// @param action Действие пункта меню
    /// @param subMenu Указатель на подменю
    MenuItem(const std::string& name,
             std::function<void()> action = nullptr,
             std::shared_ptr<Menu> subMenu = nullptr);

    /// @brief Конструктор по умолчанию
    MenuItem() = default;

    /// @brief Деструктор по умолчанию
    ~MenuItem() = default;

    /// @brief Установит действия пункта меню
    /// @param action Действие пункта меню
    void SetAction(std::function<void()> action);

    /// @brief Установит подменю для пункта меню
    /// @param subMenu Указатель на подменю
    void SetSubMenu(std::shared_ptr<Menu> subMenu);

    /// @brief Получает имени пункта меню
    /// @return Имя пункта меню
    std::string GetName() const;

    /// @brief Выполняет действия пункта меню
    void Execute();

    /// @brief Получает указаль на подменю
    /// @return Указатель на подменю
    std::shared_ptr<Menu> GetMenu();

private:
    /// @brief Имя пункта меню
    std::string _name {"[Empty menu item]"};

    /// @brief Действие пункта меню
    std::function<void()> _action {nullptr};

    /// @brief Подменю
    std::shared_ptr<Menu> _subMenu {nullptr};
};
