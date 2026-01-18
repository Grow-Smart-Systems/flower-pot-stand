#include "MenuController.h"
#include "Menu.h"
#include "MenuNavigator.h"
#include "IMenuItem.h"
#include "../Display/Display.h"

MenuController::MenuController()
    : _navigator(new MenuNavigator())
{}

const MenuInfoContainer& MenuController::GetDisplayInfo()
{
    _menuInfoContainer.text.clear();

    auto currentMenu = _navigator->GetCurrentMenu();
    if (!currentMenu)
    {
        _menuInfoContainer.currentIndex = 0;
        _menuInfoContainer.menuSize = 0;
        _menuInfoContainer.displayMenu = DisplayMenu::MAIN_MENU;
        return _menuInfoContainer;
    }

    _menuInfoContainer.currentIndex = currentMenu->GetSelectedIndex();
    _menuInfoContainer.menuSize = currentMenu->GetItemCount();
    _menuInfoContainer.displayMenu = currentMenu->GetDisplayMenuType();

    if (_menuInfoContainer.menuSize == 0)
        return _menuInfoContainer;

    _menuInfoContainer.text.reserve(_menuInfoContainer.menuSize);
    for (int i = 0; i < _menuInfoContainer.menuSize; ++i)
    {
        IMenuItem* item = currentMenu->GetItemAt(i);
        if (item)
            _menuInfoContainer.text.push_back(item->GetName());
        else
            _menuInfoContainer.text.push_back("");
    }
    _menuInfoContainer.text.shrink_to_fit();

    return _menuInfoContainer;
}

std::shared_ptr<Menu> MenuController::GetRootMenu() const
{
    return _navigator->GetRootMenu();
}

void MenuController::SetRootMenu(std::shared_ptr<Menu> rootMenu)
{
    _navigator->SetRootMenu(std::move(rootMenu));
}

void MenuController::GoToRootMenu()
{
    _navigator->GoToRoot();
}

void MenuController::NavigateUp()
{
    _navigator->NavigateUp();
}

void MenuController::NavigateDown()
{
    _navigator->NavigateDown();
}

void MenuController::SelectOption()
{
    _navigator->Select();
}

void MenuController::Back()
{
    _navigator->Back();
}

bool MenuController::IsAtRoot() const
{
    return _navigator->IsAtRoot();
}
