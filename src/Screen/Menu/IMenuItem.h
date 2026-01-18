#pragma once

#include <Arduino.h>
#include <memory>
#include <string>
#include <functional>
#include "../../Common/EnumClasses.h"

class Menu;

/// @brief Тип пункта меню
enum class MenuItemType
{
    ACTION,     // Пункт с действием (листовой узел)
    SUBMENU     // Пункт с подменю (контейнер)
};

/// @brief Базовый интерфейс для всех типов пунктов меню
class IMenuItem
{
public:
    /// @brief Виртуальный деструктор
    virtual ~IMenuItem() = default;

    /// @brief Получает имя пункта меню
    /// @return Имя пункта меню
    virtual const std::string& GetName() const = 0;

    /// @brief Получает тип пункта меню
    /// @return Тип пункта меню
    virtual MenuItemType GetType() const = 0;

    /// @brief Проверяет, есть ли у пункта подменю
    /// @return true если есть подменю, false если нет
    virtual bool HasSubMenu() const = 0;

    /// @brief Выполняет действие пункта меню
    virtual void Execute() = 0;

    /// @brief Получает подменю (если есть)
    /// @return Указатель на подменю или nullptr
    virtual std::shared_ptr<Menu> GetSubMenu() const = 0;

    /// @brief Получает тип отображения для подменю
    /// @return Тип отображения меню
    virtual DisplayMenu GetDisplayMenuType() const = 0;

    /// @brief Устанавливает тип отображения меню
    /// @param displayMenu Тип отображения
    virtual void SetDisplayMenuType(DisplayMenu displayMenu) = 0;
};
