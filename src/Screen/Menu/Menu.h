#pragma once

#include <Arduino.h>
#include <memory>
#include <vector>

#include "../../Common/EnumClasses.h"
#include "IMenuItem.h"

class IMenuItem;

/// @brief Класс контейнера меню
/// @details Хранит пункты меню и управляет навигацией внутри одного уровня
class Menu final : public std::enable_shared_from_this<Menu>
{
public:
    /// @brief Конструктор
    /// @param displayMenu Тип отображения меню
    Menu(DisplayMenu displayMenu = DisplayMenu::SUB_MENU);

    /// @brief Деструктор
    ~Menu();

    /// @brief Устанавливает родительское меню
    /// @param parent Указатель на родительское меню
    void SetParent(std::weak_ptr<Menu> parent);

    /// @brief Получает родительское меню
    /// @return Указатель на родительское меню или nullptr
    std::shared_ptr<Menu> GetParent() const;

    /// @brief Проверяет наличие родительского меню
    /// @return true если есть родитель, false если корневое меню
    bool HasParent() const;

    /// @brief Добавляет пункт меню
    /// @param item Указатель на пункт меню
    void AddItem(std::unique_ptr<IMenuItem> item);

    /// @brief Получает пункт меню по индексу
    /// @param index Индекс пункта
    /// @return Указатель на пункт меню или nullptr
    IMenuItem* GetItemAt(int index) const;

    /// @brief Получает текущий выбранный пункт меню
    /// @return Указатель на выбранный пункт или nullptr
    IMenuItem* GetSelectedItem() const;

    /// @brief Получает количество пунктов меню
    /// @return Количество пунктов
    int GetItemCount() const;

    /// @brief Получает текущий индекс выбранного пункта
    /// @return Текущий индекс
    int GetSelectedIndex() const;

    /// @brief Устанавливает текущий индекс выбранного пункта
    /// @param index Новый индекс
    void SetSelectedIndex(int index);

    /// @brief Сбрасывает индекс на начало
    void ResetSelection();

    /// @brief Перемещает выбор на следующий пункт
    /// @return true если перемещение выполнено, false если уже в конце
    bool SelectNext();

    /// @brief Перемещает выбор на предыдущий пункт
    /// @return true если перемещение выполнено, false если уже в начале
    bool SelectPrevious();

    /// @brief Получает тип отображения меню
    /// @return Тип отображения
    DisplayMenu GetDisplayMenuType() const;

    /// @brief Устанавливает тип отображения меню
    /// @param displayMenu Тип отображения
    void SetDisplayMenuType(DisplayMenu displayMenu);

    /// @brief Очищает все пункты меню
    void Clear();

private:
    /// @brief Указатель на родительское меню (weak для избежания циклических ссылок)
    std::weak_ptr<Menu> _parent;

    /// @brief Набор пунктов меню (владеющие указатели)
    std::vector<std::unique_ptr<IMenuItem>> _items;

    /// @brief Текущий выбранный индекс
    int _selectedIndex{0};

    /// @brief Тип отображения меню
    DisplayMenu _displayMenuType;
};
