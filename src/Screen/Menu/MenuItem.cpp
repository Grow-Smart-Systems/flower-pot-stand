#include "MenuItem.h"
#include "../../Common/Data.h"

MenuItem::MenuItem(const String& name, std::function<void()> action, std::shared_ptr<Menu> subMenu) :
    _name(name),
    _action(action),
    _subMenu(subMenu)
{
}
void MenuItem::AddAction(std::function<void()> action)
{
    _action = action;
}

void MenuItem::AddSubMenu(std::shared_ptr<Menu> subMenu)
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

std::shared_ptr<Menu> MenuItem::GetItemMenu()
{
    return _subMenu;
}

// void MenuItem::DisplaySubMenu() const
// {
//     int currentMenuPosition{ 0 };
//     int currentPage{ 0 };
//     int pagesCount{ 0 };
//     int menuSize = _subMenu.size();

//     /// получим текущее положени на странице с учетом того, что на странице 5 пунктов

//     // количество страниц
//     pagesCount = menuSize * INVERTED_SUB_MENU_ITEMS_SIZE + (menuSize % SUB_MENU_ITEMS_SIZE ? 1 : 0);

//     // текущее положение на странице
//     currentMenuPosition = _selectedSubItem % SUB_MENU_ITEMS_SIZE;

//     // текущая страница
//     currentPage = _selectedSubItem * INVERTED_SUB_MENU_ITEMS_SIZE;

//     // отрисуем меню
//     Data::getInstance().getScreen()->getDisplay()->printSubMenu(currentMenuPosition,
//         _subMenu[currentPage * SUB_MENU_ITEMS_SIZE].GetName(),
//         currentPage * SUB_MENU_ITEMS_SIZE + 1 < menuSize ? _subMenu[currentPage * SUB_MENU_ITEMS_SIZE + 1].GetName() : "",
//         currentPage * SUB_MENU_ITEMS_SIZE + 2 < menuSize ? _subMenu[currentPage * SUB_MENU_ITEMS_SIZE + 2].GetName() : "",
//         currentPage * SUB_MENU_ITEMS_SIZE + 3 < menuSize ? _subMenu[currentPage * SUB_MENU_ITEMS_SIZE + 3].GetName() : "",
//         currentPage * SUB_MENU_ITEMS_SIZE + 4 < menuSize ? _subMenu[currentPage * SUB_MENU_ITEMS_SIZE + 4].GetName() : "");
// }

