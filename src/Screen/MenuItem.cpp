#include "MenuItem.h"

MenuItem::MenuItem(std::shared_ptr<Display> display, const String& name, std::function<void()> action) :
    _display(display),
    name(name),
    action(action)
{
}

void MenuItem::addSubMenu(const MenuItem& item)
{
    subMenu.push_back(item);
}

void MenuItem::execute()
{
    Data::getInstance().setDisplayMenu(Data::DisplayMenu::SUB_MENU);

    _selectedSubItem = 0;

    if (action)
        action();

    if (!subMenu.empty())
        displaySubMenu();
}

void MenuItem::back()
{
    Data::getInstance().setDisplayMenu(Data::DisplayMenu::MAIN_MENU);
}

void MenuItem::displaySubMenu() const
{
    int currentMenuPosition{ 0 };
    int currentPage{ 0 };
    int pagesCount{ 0 };
    int menuSize = subMenu.size();

    // получим текущее положени на странице с учетом того, что на странице 5 пунктов

    // количество страниц
    pagesCount = menuSize / SUB_MENU_ITEMS_SIZE + (menuSize % SUB_MENU_ITEMS_SIZE ? 1 : 0);

    // текущее положение на странице
    currentMenuPosition = _selectedSubItem % SUB_MENU_ITEMS_SIZE;

    // текущая страница
    currentPage = _selectedSubItem / SUB_MENU_ITEMS_SIZE;

    // отрисуем меню



}

void MenuItem::selectNextItem()
{
    if (_selectedSubItem < subMenu.size() - 1)
        _selectedSubItem++;
}

void MenuItem::selectPreviousItem()
{
    if (_selectedSubItem > 0)
        _selectedSubItem--;
}
