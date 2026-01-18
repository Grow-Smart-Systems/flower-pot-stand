#pragma once

#include <Arduino.h>
#include <memory>
#include <functional>
#include <vector>

#include "../../Common/EnumClasses.h"

class Menu;

/// @brief Callback-тип для действий меню
using MenuAction = std::function<void()>;

/// @brief Структура для определения действия пункта меню
struct MenuActionDef
{
    std::string name;
    MenuAction action;
    DisplayMenu displayType = DisplayMenu::FUNCTIONAL_MENU;
};

/// @brief Класс построителя меню
/// @details Отвечает за создание и конфигурацию структуры меню
class MenuBuilder
{
public:
    /// @brief Конструктор
    MenuBuilder() = default;

    /// @brief Деструктор
    ~MenuBuilder() = default;

    /// @brief Создаёт корневое меню
    /// @param displayType Тип отображения корневого меню
    /// @return Указатель на созданное меню
    static std::shared_ptr<Menu> CreateRootMenu(DisplayMenu displayType = DisplayMenu::MAIN_MENU);

    /// @brief Создаёт подменю и добавляет его как пункт в родительское меню
    /// @param name Имя пункта меню
    /// @param parent Родительское меню
    /// @param displayType Тип отображения подменю
    /// @return Указатель на созданное подменю
    static std::shared_ptr<Menu> CreateSubMenu(const std::string& name,
                                                std::shared_ptr<Menu> parent,
                                                DisplayMenu displayType = DisplayMenu::SUB_MENU);

    /// @brief Добавляет пункт-действие в меню
    /// @param name Имя пункта
    /// @param menu Меню, в которое добавляется пункт
    /// @param action Действие для выполнения
    /// @param displayType Тип отображения при выполнении действия
    static void AddAction(const std::string& name,
                          std::shared_ptr<Menu> menu,
                          MenuAction action = nullptr,
                          DisplayMenu displayType = DisplayMenu::FUNCTIONAL_MENU);

    /// @brief Добавляет несколько пунктов-действий в меню
    /// @param menu Меню, в которое добавляются пункты
    /// @param actions Вектор определений действий
    static void AddActions(std::shared_ptr<Menu> menu,
                           const std::vector<MenuActionDef>& actions);
};
