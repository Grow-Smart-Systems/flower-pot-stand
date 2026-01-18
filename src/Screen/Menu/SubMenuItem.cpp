#include "SubMenuItem.h"
#include "Menu.h"

SubMenuItem::SubMenuItem(const std::string& name,
                         std::shared_ptr<Menu> subMenu,
                         DisplayMenu displayMenuType)
    : _name(name)
    , _subMenu(std::move(subMenu))
    , _displayMenuType(displayMenuType)
{}

const std::string& SubMenuItem::GetName() const
{
    return _name;
}

MenuItemType SubMenuItem::GetType() const
{
    return MenuItemType::SUBMENU;
}

bool SubMenuItem::HasSubMenu() const
{
    return true;
}

void SubMenuItem::Execute()
{
    // SubMenuItem не имеет действия, переход осуществляется через GetSubMenu()
}

std::shared_ptr<Menu> SubMenuItem::GetSubMenu() const
{
    return _subMenu;
}

DisplayMenu SubMenuItem::GetDisplayMenuType() const
{
    return _displayMenuType;
}

void SubMenuItem::SetDisplayMenuType(DisplayMenu displayMenu)
{
    _displayMenuType = displayMenu;
}

void SubMenuItem::SetSubMenu(std::shared_ptr<Menu> subMenu)
{
    _subMenu = std::move(subMenu);
}
