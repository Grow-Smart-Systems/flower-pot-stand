#include "MenuBuilder.h"
#include "Menu.h"
#include "ActionMenuItem.h"
#include "SubMenuItem.h"

std::shared_ptr<Menu> MenuBuilder::CreateRootMenu(DisplayMenu displayType)
{
    return std::make_shared<Menu>(displayType);
}

std::shared_ptr<Menu> MenuBuilder::CreateSubMenu(const std::string& name,
                                                  std::shared_ptr<Menu> parent,
                                                  DisplayMenu displayType)
{
    if (!parent)
        return nullptr;

    // Создаём новое подменю
    auto subMenu = std::make_shared<Menu>(displayType);
    subMenu->SetParent(parent);

    // Создаём пункт меню, ведущий к подменю
    std::unique_ptr<SubMenuItem> subMenuItem(new SubMenuItem(name, subMenu, displayType));

    // Добавляем пункт в родительское меню
    parent->AddItem(std::move(subMenuItem));

    return subMenu;
}

void MenuBuilder::AddAction(const std::string& name,
                            std::shared_ptr<Menu> menu,
                            MenuAction action,
                            DisplayMenu displayType)
{
    if (!menu)
        return;

    std::unique_ptr<ActionMenuItem> actionItem(new ActionMenuItem(name, std::move(action), displayType));
    menu->AddItem(std::move(actionItem));
}

void MenuBuilder::AddActions(std::shared_ptr<Menu> menu,
                             const std::vector<MenuActionDef>& actions)
{
    if (!menu)
        return;

    for (const auto& actionDef : actions)
    {
        AddAction(actionDef.name, menu, actionDef.action, actionDef.displayType);
    }
}
