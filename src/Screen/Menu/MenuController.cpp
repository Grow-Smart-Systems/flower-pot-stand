#include "MenuController.h"
#include "Menu.h"
#include "../Display/Display.h"

MenuController::MenuController()
{
    _rootMenu = std::make_shared<Menu>(nullptr, DisplayMenu::MAIN_MENU);
    _currentMenu = _rootMenu;
}

const MenuInfoContainer& MenuController::GetDisplayInfo()
{
    _menuInfoContainer.text.clear();

    _menuInfoContainer.currentIndex = _currentMenu->GetCurrentIndex();
    _menuInfoContainer.menuSize = _currentMenu->GetMenuItemsSize();
    _menuInfoContainer.displayMenu = _currentMenu->GetDisplayMenu();

    if (_menuInfoContainer.menuSize == 0)
        return _menuInfoContainer;

    _menuInfoContainer.text.reserve(_menuInfoContainer.menuSize);
    for (int i = 0; i < _menuInfoContainer.menuSize; ++i)
    {
        _menuInfoContainer.text.push_back(_currentMenu->GetMenuItemAt(i).GetName());
    }
    _menuInfoContainer.text.shrink_to_fit();
    return _menuInfoContainer;
}

std::shared_ptr<Menu> MenuController::GetRootMenu() const
{
    return _rootMenu;
}

std::shared_ptr<Menu> MenuController::CreateMenuItem(const std::string& name,
                                                     std::shared_ptr<Menu> parentMenu,
                                                     std::function<void()> action)
{
    if (!parentMenu)
        return nullptr;

    auto newMenu = std::make_shared<Menu>(parentMenu);
    MenuItem menuItem(name, action, newMenu);
    parentMenu->AddMenuItem(menuItem);
    return newMenu;
}

void MenuController::GotoRootMenu()
{
    _currentMenu = _rootMenu;
}

void MenuController::NavigateUp()
{
    _currentMenu->SelectPreviousItem();
}

void MenuController::NavigateDown()
{
    _currentMenu->SelectNextItem();
}

void MenuController::SelectOption()
{
    auto newCurrentMenu = _currentMenu->ExecuteMenu();
    if (newCurrentMenu)
        _currentMenu = newCurrentMenu;
}

void MenuController::Back()
{
    auto newCurrentMenu = _currentMenu->Back();
    if (newCurrentMenu)
        _currentMenu = newCurrentMenu;
}


