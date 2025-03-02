#include "MenuItem.h"
#include "../../Common/Data.h"

MenuItem::MenuItem(const String& name, std::function<void()> action, std::shared_ptr<Menu> subMenu) :
    _name(name),
    _action(action),
    _subMenu(subMenu)
{}

void MenuItem::SetAction(std::function<void()> action)
{
    _action = action;
}

void MenuItem::SetSubMenu(std::shared_ptr<Menu> subMenu)
{
    _subMenu = subMenu;
}

String MenuItem::GetName() const
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
