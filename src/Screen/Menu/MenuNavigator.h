#pragma once

#include <Arduino.h>
#include <memory>

#include "../../Common/EnumClasses.h"

class Menu;
class IMenuItem;

/// @brief Класс навигации по меню
/// @details Отвечает за перемещение между меню и отслеживание текущего состояния
class MenuNavigator
{
public:
    /// @brief Конструктор
    MenuNavigator() = default;

    /// @brief Деструктор
    ~MenuNavigator() = default;

    /// @brief Устанавливает корневое меню
    /// @param rootMenu Указатель на корневое меню
    void SetRootMenu(std::shared_ptr<Menu> rootMenu);

    /// @brief Получает корневое меню
    /// @return Указатель на корневое меню
    std::shared_ptr<Menu> GetRootMenu() const;

    /// @brief Получает текущее меню
    /// @return Указатель на текущее меню
    std::shared_ptr<Menu> GetCurrentMenu() const;

    /// @brief Перемещает выбор вверх
    /// @return true если перемещение выполнено
    bool NavigateUp();

    /// @brief Перемещает выбор вниз
    /// @return true если перемещение выполнено
    bool NavigateDown();

    /// @brief Выбирает текущий пункт меню
    /// @return true если переход в подменю выполнен, false если выполнено действие или нет выбора
    bool Select();

    /// @brief Возвращается на уровень выше
    /// @return true если возврат выполнен, false если уже в корне
    bool Back();

    /// @brief Возвращается в корневое меню
    void GoToRoot();

    /// @brief Получает текущий выбранный пункт
    /// @return Указатель на текущий пункт или nullptr
    IMenuItem* GetSelectedItem() const;

    /// @brief Получает текущий индекс выбора
    /// @return Текущий индекс
    int GetSelectedIndex() const;

    /// @brief Получает количество пунктов в текущем меню
    /// @return Количество пунктов
    int GetCurrentMenuSize() const;

    /// @brief Получает тип отображения текущего меню
    /// @return Тип отображения
    DisplayMenu GetCurrentDisplayMenuType() const;

    /// @brief Проверяет, находимся ли мы в корневом меню
    /// @return true если в корне
    bool IsAtRoot() const;

private:
    /// @brief Корневое меню
    std::shared_ptr<Menu> _rootMenu{nullptr};

    /// @brief Текущее меню
    std::shared_ptr<Menu> _currentMenu{nullptr};
};
