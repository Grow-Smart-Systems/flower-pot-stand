#pragma once

#include "IMenuItem.h"

/// @brief Пункт меню с действием (листовой узел)
/// @details Представляет конечный пункт меню, который выполняет действие при выборе
class ActionMenuItem final : public IMenuItem
{
public:
    /// @brief Конструктор
    /// @param name Имя пункта меню
    /// @param action Действие для выполнения
    /// @param displayMenuType Тип отображения (по умолчанию FUNCTIONAL_MENU)
    ActionMenuItem(const std::string& name,
                   std::function<void()> action = nullptr,
                   DisplayMenu displayMenuType = DisplayMenu::FUNCTIONAL_MENU);

    /// @brief Деструктор
    ~ActionMenuItem() override = default;

    /// @brief Получает имя пункта меню
    /// @return Имя пункта меню
    const std::string& GetName() const override;

    /// @brief Получает тип пункта меню
    /// @return Всегда возвращает MenuItemType::ACTION
    MenuItemType GetType() const override;

    /// @brief Проверяет наличие подменю
    /// @return Всегда возвращает false
    bool HasSubMenu() const override;

    /// @brief Выполняет действие пункта меню
    void Execute() override;

    /// @brief Получает подменю
    /// @return Всегда возвращает nullptr
    std::shared_ptr<Menu> GetSubMenu() const override;

    /// @brief Получает тип отображения меню
    /// @return Тип отображения
    DisplayMenu GetDisplayMenuType() const override;

    /// @brief Устанавливает тип отображения меню
    /// @param displayMenu Тип отображения
    void SetDisplayMenuType(DisplayMenu displayMenu) override;

    /// @brief Устанавливает действие
    /// @param action Новое действие
    void SetAction(std::function<void()> action);

private:
    /// @brief Имя пункта меню
    std::string _name;

    /// @brief Действие пункта меню
    std::function<void()> _action;

    /// @brief Тип отображения меню
    DisplayMenu _displayMenuType;
};
