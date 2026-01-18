#include "MenuItem.h"
#ifndef UNIT_TEST
#include "../../Common/Data.h"
#endif

MenuItem::MenuItem(const std::string& name, std::function<void()> action, std::shared_ptr<Menu> subMenu) :
    _name(name),
    _action(action),
    _subMenu(std::move(subMenu))
{}

void MenuItem::SetAction(std::function<void()> action)
{
    _action = action;
}

void MenuItem::SetSubMenu(std::shared_ptr<Menu> subMenu)
{
    _subMenu = subMenu;
}

std::string MenuItem::GetName() const
{
    return _name;
}

void MenuItem::Execute()
{
    if (_action)
        _action();
}

std::shared_ptr<Menu> MenuItem::GetMenu()
{
    return _subMenu;
}
