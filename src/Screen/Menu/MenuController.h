#pragma once

#include <Arduino.h>
#include <memory>
#include <vector>
#include "../../Common/Containers/MenuInfoContainer.h"

class Menu;
class MenuNavigator;
class IMenuItem;

/// @brief Класс контроллера меню
/// @details Фасад для работы с системой меню, объединяет навигацию и предоставление данных
class MenuController final
{
public:
    /// @brief Конструктор
    MenuController();

    /// @brief Деструктор
    ~MenuController() = default;

    /// @brief Получает информацию о текущем меню для отображения
    /// @return Контейнер с информацией о меню
    const MenuInfoContainer& GetDisplayInfo();

    /// @brief Получает корневое меню
    /// @return Указатель на корневое меню
    std::shared_ptr<Menu> GetRootMenu() const;

    /// @brief Устанавливает корневое меню
    /// @param rootMenu Указатель на корневое меню
    void SetRootMenu(std::shared_ptr<Menu> rootMenu);

    /// @brief Переход к корневому меню
    void GoToRootMenu();

    /* NAVIGATION SECTION */

    /// @brief Перемещение вверх по меню
    void NavigateUp();

    /// @brief Перемещение вниз по меню
    void NavigateDown();

    /// @brief Выбор пункта меню
    void SelectOption();

    /// @brief Возврат назад
    void Back();

    /* NAVIGATION SECTION END */

    /// @brief Проверяет, находимся ли в корневом меню
    /// @return true если в корневом меню
    bool IsAtRoot() const;

private:
    /// @brief Навигатор меню
    std::unique_ptr<MenuNavigator> _navigator;

    /// @brief Контейнер информации о меню для отображения
    MenuInfoContainer _menuInfoContainer;
};
