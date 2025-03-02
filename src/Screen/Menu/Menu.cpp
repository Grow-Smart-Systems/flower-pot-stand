#include "Menu.h"

static const MenuItem _emptyItem;

Menu::Menu(std::shared_ptr<Menu> parentMenu, DisplayMenu displayMenu)
    : _parentMenu(parentMenu)
    , _displayMenu(displayMenu)
{}

Menu::~Menu()
{
    _menuItems.clear();
}

const MenuItem& Menu::GetSelectedItem()
{
    if (_menuItems.empty())
        return _emptyItem;
    return _menuItems[_selectedItem];
}

void Menu::SetMenuItems(const std::vector<MenuItem>& menuItems)
{
    _menuItems = menuItems;
}

void Menu::AddMenuItem(const MenuItem menuItem)
{
    _menuItems.push_back(menuItem);
}

void Menu::SetDisplayMenu(DisplayMenu displayMenu)
{
    _displayMenu = displayMenu;
}

DisplayMenu Menu::GetDisplayMenu() const
{
    return _displayMenu;
}

int Menu::GetMenuItemsSize() const
{
    return _menuItems.size();
}

int Menu::GetCurrentIndex() const
{
    return _selectedItem;
}

const MenuItem& Menu::GetMenuItemAt(int index)
{
    if (index >= _menuItems.size())
        return _emptyItem;
    return _menuItems[index];
}

std::shared_ptr<Menu> Menu::ExecuteMenu()
{
    if (_menuItems.empty())
        return nullptr;

    auto string = _menuItems[_selectedItem].GetName();
    _menuItems[_selectedItem].Execute();
    return _menuItems[_selectedItem].GetMenu();
}

std::shared_ptr<Menu> Menu::Back()
{
    _selectedItem = 0;
    return _parentMenu;
}

void Menu::SelectNextItem()
{
    if (_selectedItem < _menuItems.size() - 1)
        ++_selectedItem;
}

void Menu::SelectPreviousItem()
{
    if (_selectedItem > 0)
        --_selectedItem;
}
