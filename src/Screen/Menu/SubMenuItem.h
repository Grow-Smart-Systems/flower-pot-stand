#pragma once

#include "IMenuItem.h"

/// @brief Пункт меню с подменю (контейнер)
/// @details Представляет пункт меню, который ведёт к вложенному меню
class SubMenuItem final : public IMenuItem
{
public:
    /// @brief Конструктор
    /// @param name Имя пункта меню
    /// @param subMenu Указатель на подменю
    /// @param displayMenuType Тип отображения подменю
    SubMenuItem(const std::string& name,
                std::shared_ptr<Menu> subMenu,
                DisplayMenu displayMenuType = DisplayMenu::SUB_MENU);

    /// @brief Деструктор
    ~SubMenuItem() override = default;

    /// @brief Получает имя пункта меню
    /// @return Имя пункта меню
    const std::string& GetName() const override;

    /// @brief Получает тип пункта меню
    /// @return Всегда возвращает MenuItemType::SUBMENU
    MenuItemType GetType() const override;

    /// @brief Проверяет наличие подменю
    /// @return Всегда возвращает true
    bool HasSubMenu() const override;

    /// @brief Выполняет действие (ничего не делает для SubMenuItem)
    void Execute() override;

    /// @brief Получает подменю
    /// @return Указатель на подменю
    std::shared_ptr<Menu> GetSubMenu() const override;

    /// @brief Получает тип отображения меню
    /// @return Тип отображения
    DisplayMenu GetDisplayMenuType() const override;

    /// @brief Устанавливает тип отображения меню
    /// @param displayMenu Тип отображения
    void SetDisplayMenuType(DisplayMenu displayMenu) override;

    /// @brief Устанавливает подменю
    /// @param subMenu Указатель на подменю
    void SetSubMenu(std::shared_ptr<Menu> subMenu);

private:
    /// @brief Имя пункта меню
    std::string _name;

    /// @brief Указатель на подменю
    std::shared_ptr<Menu> _subMenu;

    /// @brief Тип отображения меню
    DisplayMenu _displayMenuType;
};
