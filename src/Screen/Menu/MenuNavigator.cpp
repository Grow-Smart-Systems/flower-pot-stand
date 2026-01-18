#include "MenuNavigator.h"
#include "Menu.h"
#include "IMenuItem.h"

void MenuNavigator::SetRootMenu(std::shared_ptr<Menu> rootMenu)
{
    _rootMenu = std::move(rootMenu);
    _currentMenu = _rootMenu;
}

std::shared_ptr<Menu> MenuNavigator::GetRootMenu() const
{
    return _rootMenu;
}

std::shared_ptr<Menu> MenuNavigator::GetCurrentMenu() const
{
    return _currentMenu;
}

bool MenuNavigator::NavigateUp()
{
    if (!_currentMenu)
        return false;
    return _currentMenu->SelectPrevious();
}

bool MenuNavigator::NavigateDown()
{
    if (!_currentMenu)
        return false;
    return _currentMenu->SelectNext();
}

bool MenuNavigator::Select()
{
    if (!_currentMenu)
        return false;

    IMenuItem* selectedItem = _currentMenu->GetSelectedItem();
    if (!selectedItem)
        return false;

    // Выполняем действие пункта меню
    selectedItem->Execute();

    // Если есть подменю - переходим в него
    if (selectedItem->HasSubMenu())
    {
        auto subMenu = selectedItem->GetSubMenu();
        if (subMenu)
        {
            _currentMenu = subMenu;
            return true;
        }
    }

    return false;
}

bool MenuNavigator::Back()
{
    if (!_currentMenu || !_currentMenu->HasParent())
        return false;

    auto parent = _currentMenu->GetParent();
    if (!parent)
        return false;

    // Сбрасываем выбор текущего меню перед выходом
    _currentMenu->ResetSelection();
    _currentMenu = parent;
    return true;
}

void MenuNavigator::GoToRoot()
{
    // Сбрасываем выбор во всех меню при переходе в корень
    if (_currentMenu && _currentMenu != _rootMenu)
    {
        auto current = _currentMenu;
        while (current && current != _rootMenu)
        {
            current->ResetSelection();
            current = current->GetParent();
        }
    }

    _currentMenu = _rootMenu;
    if (_currentMenu)
        _currentMenu->ResetSelection();
}

IMenuItem* MenuNavigator::GetSelectedItem() const
{
    if (!_currentMenu)
        return nullptr;
    return _currentMenu->GetSelectedItem();
}

int MenuNavigator::GetSelectedIndex() const
{
    if (!_currentMenu)
        return 0;
    return _currentMenu->GetSelectedIndex();
}

int MenuNavigator::GetCurrentMenuSize() const
{
    if (!_currentMenu)
        return 0;
    return _currentMenu->GetItemCount();
}

DisplayMenu MenuNavigator::GetCurrentDisplayMenuType() const
{
    if (!_currentMenu)
        return DisplayMenu::MAIN_MENU;
    return _currentMenu->GetDisplayMenuType();
}

bool MenuNavigator::IsAtRoot() const
{
    return _currentMenu == _rootMenu;
}
