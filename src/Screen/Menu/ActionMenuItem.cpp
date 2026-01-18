#include "ActionMenuItem.h"

ActionMenuItem::ActionMenuItem(const std::string& name,
                               std::function<void()> action,
                               DisplayMenu displayMenuType)
    : _name(name)
    , _action(std::move(action))
    , _displayMenuType(displayMenuType)
{}

const std::string& ActionMenuItem::GetName() const
{
    return _name;
}

MenuItemType ActionMenuItem::GetType() const
{
    return MenuItemType::ACTION;
}

bool ActionMenuItem::HasSubMenu() const
{
    return false;
}

void ActionMenuItem::Execute()
{
    if (_action)
        _action();
}

std::shared_ptr<Menu> ActionMenuItem::GetSubMenu() const
{
    return nullptr;
}

DisplayMenu ActionMenuItem::GetDisplayMenuType() const
{
    return _displayMenuType;
}

void ActionMenuItem::SetDisplayMenuType(DisplayMenu displayMenu)
{
    _displayMenuType = displayMenu;
}

void ActionMenuItem::SetAction(std::function<void()> action)
{
    _action = std::move(action);
}
