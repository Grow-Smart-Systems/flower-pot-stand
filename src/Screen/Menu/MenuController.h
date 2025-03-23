#pragma once

#include <Arduino.h>
#include <memory>
#include <vector>
#include "../../Common/Containers/MenuInfoContainer.h"

class Menu;
class Display;


/// @brief Класс контроллера меню
class MenuController final
{
public:
    /// @brief Конструктор
    MenuController();

    /// @brief Деструктор
    ~MenuController() = default;

    /// @brief Передает информацию о текущем меню
    /// @return Контейнер информации о меню
    const MenuInfoContainer& GetDisplayInfo();

    /// @brief Возвращает корневое меню
    /// @return Указатель на корневое меню
    std::shared_ptr<Menu> GetRootMenu() const;

    /// @brief Создает новый пункт меню
    /// @param name Имя пункта меню
    /// @param parentMenu Родительское меню
    /// @param action Действие пункта меню
    /// @return Указатель на новое меню
    std::shared_ptr<Menu> CreateMenuItem(const std::string& name,
                                         std::shared_ptr<Menu> parentMenu,
                                         std::function<void()> action = nullptr);

    /// @brief Переход к корневому меню
    void GotoRootMenu();

    /* MOVEMENT SECTION */

    /// @brief Перемещение вверх по меню
    void NavigateUp();

    /// @brief Перемещение вниз по меню
    void NavigateDown();

    /// @brief Выбор пункта меню
    void SelectOption();

    /// @brief Возврат назад
    void Back();

    /* MOVEMENT SECTION END */

private:
    /// @brief Указатель на корневое меню
    std::shared_ptr<Menu> _rootMenu {nullptr};

    /// @brief Указатель на текущее меню
    std::shared_ptr<Menu> _currentMenu {nullptr};

    /// @brief Контейнер информации о меню
    MenuInfoContainer _menuInfoContainer;
};