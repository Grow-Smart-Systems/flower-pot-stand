#include "Menu.h"
#include "IMenuItem.h"

Menu::Menu(DisplayMenu displayMenu)
    : _displayMenuType(displayMenu)
{}

Menu::~Menu()
{
    Clear();
}

void Menu::SetParent(std::weak_ptr<Menu> parent)
{
    _parent = parent;
}

std::shared_ptr<Menu> Menu::GetParent() const
{
    return _parent.lock();
}

bool Menu::HasParent() const
{
    return !_parent.expired();
}

void Menu::AddItem(std::unique_ptr<IMenuItem> item)
{
    if (item)
        _items.push_back(std::move(item));
}

IMenuItem* Menu::GetItemAt(int index) const
{
    if (index < 0 || index >= static_cast<int>(_items.size()))
        return nullptr;
    return _items[index].get();
}

IMenuItem* Menu::GetSelectedItem() const
{
    return GetItemAt(_selectedIndex);
}

int Menu::GetItemCount() const
{
    return static_cast<int>(_items.size());
}

int Menu::GetSelectedIndex() const
{
    return _selectedIndex;
}

void Menu::SetSelectedIndex(int index)
{
    if (index >= 0 && index < static_cast<int>(_items.size()))
        _selectedIndex = index;
}

void Menu::ResetSelection()
{
    _selectedIndex = 0;
}

bool Menu::SelectNext()
{
    if (_items.empty())
        return false;

    if (_selectedIndex < static_cast<int>(_items.size()) - 1)
    {
        ++_selectedIndex;
        return true;
    }
    return false;
}

bool Menu::SelectPrevious()
{
    if (_items.empty())
        return false;
        
    if (_selectedIndex > 0)
    {
        --_selectedIndex;
        return true;
    }
    return false;
}

DisplayMenu Menu::GetDisplayMenuType() const
{
    return _displayMenuType;
}

void Menu::SetDisplayMenuType(DisplayMenu displayMenu)
{
    _displayMenuType = displayMenu;
}

void Menu::Clear()
{
    _items.clear();
    _selectedIndex = 0;
}
