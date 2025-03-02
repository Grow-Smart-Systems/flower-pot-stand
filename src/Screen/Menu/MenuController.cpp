#include "MenuController.h"
#include "Menu.h"

MenuController::MenuController()
{
    _rootMenu = std::make_shared<Menu>(nullptr, Data::DisplayMenu::MAIN_MENU);
    _currentMenu = _rootMenu;
}

void MenuController::DisplayMenu()
{
    const auto& currentTypeMenu = _currentMenu->GetDisplayMenu();
    Serial.println("Current menu selected Item: " + String(_currentMenu->GetSelectedItem().GetName()));
    switch (currentTypeMenu)
    {
        case Data::DisplayMenu::MAIN_MENU:
            Serial.println("Display main menu");
            displayMainMenu();
            break;
        case Data::DisplayMenu::SUB_MENU:
            Serial.println("Display sub menu");
            displaySubMenu();
            break;
        case Data::DisplayMenu::FUNCTIONAL_MENU:
            Serial.println("Display functional menu");
            displayFunctionMenu();
            break;
        default:
            break;
    }
}

std::shared_ptr<Menu> MenuController::GetRootMenu() const
{
    return _rootMenu;
}

std::shared_ptr<Menu> MenuController::CreateMenuItem(const String& name,
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

void MenuController::displayMainMenu()
{
    int currentMenuPosition = 0;
    int menuSize = _currentMenu->GetMenuItemsSize();
    int currentIndex = _currentMenu->GetCurrentIndex();

    // Определим наличие навигационных треугольников    
    bool upTriangle = (currentIndex > 0 && menuSize > 3);
    bool downTriangle = (currentIndex < menuSize - 1 && menuSize > 3);

    // Определим текст для отображения и текущую позицию в меню
    String text0 {""}, text1 {""}, text2 {""};
    if (menuSize == 1)
    {
        currentMenuPosition = 0;
        text0 = _currentMenu->GetMenuItemAt(0).GetName();
    }
    else if (menuSize == 2)
    {
        currentMenuPosition = currentIndex;
        text0 = _currentMenu->GetMenuItemAt(0).GetName();
        text1 = _currentMenu->GetMenuItemAt(1).GetName();
    }
    else
    {
        if (currentIndex == 0)
            currentMenuPosition = 0;
        else if (currentIndex > 0 && currentIndex < menuSize - 1)
            currentMenuPosition = 1;
        else if (currentIndex == menuSize - 1)
            currentMenuPosition = 2;

        if (currentMenuPosition == 0)
        {
            text0 = _currentMenu->GetMenuItemAt(currentIndex).GetName();
            text1 = _currentMenu->GetMenuItemAt(currentIndex + 1).GetName();
            text2 = _currentMenu->GetMenuItemAt(currentIndex + 2).GetName();
        }
        else if (currentMenuPosition == 1)
        {
            text0 = _currentMenu->GetMenuItemAt(currentIndex - 1).GetName();
            text1 = _currentMenu->GetMenuItemAt(currentIndex).GetName();
            text2 = _currentMenu->GetMenuItemAt(currentIndex + 1).GetName();
        }
        else if (currentMenuPosition == 2)
        {
            text0 = _currentMenu->GetMenuItemAt(currentIndex - 2).GetName();
            text1 = _currentMenu->GetMenuItemAt(currentIndex - 1).GetName();
            text2 = _currentMenu->GetMenuItemAt(currentIndex).GetName();
        }
    }

    // Отобразим меню
    Data::getInstance().getScreen()->getDisplay()->printMainMenu(
        currentMenuPosition,
        upTriangle,
        downTriangle,
        text0,
        text1,
        text2);
}

void MenuController::displaySubMenu()
{
    int currentMenuPosition = 0;
    int menuSize = _currentMenu->GetMenuItemsSize();
    int currentIndex = _currentMenu->GetCurrentIndex();

    // количество страниц
    int pagesCount = (menuSize + SUB_MENU_ITEMS_SIZE - 1) / SUB_MENU_ITEMS_SIZE;

    // текущее положение на странице
    currentMenuPosition = currentIndex % SUB_MENU_ITEMS_SIZE;

    // текущая страница
    int currentPage = currentIndex / SUB_MENU_ITEMS_SIZE;

    // отрисуем меню
    Data::getInstance().getScreen()->getDisplay()->printSubMenu(
        currentMenuPosition,
        _currentMenu->GetMenuItemAt(currentPage * SUB_MENU_ITEMS_SIZE).GetName(),
        currentPage * SUB_MENU_ITEMS_SIZE + 1 < menuSize ?
            _currentMenu->GetMenuItemAt(currentPage * SUB_MENU_ITEMS_SIZE + 1).GetName() : "",
        currentPage * SUB_MENU_ITEMS_SIZE + 2 < menuSize ?
            _currentMenu->GetMenuItemAt(currentPage * SUB_MENU_ITEMS_SIZE + 2).GetName() : "",
        currentPage * SUB_MENU_ITEMS_SIZE + 3 < menuSize ?
            _currentMenu->GetMenuItemAt(currentPage * SUB_MENU_ITEMS_SIZE + 3).GetName() : "",
        currentPage * SUB_MENU_ITEMS_SIZE + 4 < menuSize ?
            _currentMenu->GetMenuItemAt(currentPage * SUB_MENU_ITEMS_SIZE + 4).GetName() : "");
}

void MenuController::displayFunctionMenu()
{
    Data::getInstance().getScreen()->getDisplay()->printFunctionMenu(false);
}

