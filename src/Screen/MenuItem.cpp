#include "MenuItem.h"
#include "../Common/Data.h"

MenuItem::MenuItem(const String& name, std::function<void()> action) :
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
    auto& data = Data::getInstance();
    Serial.println("MenuItem | execute - " + name);

    if (data.getDisplayMenu() == Data::DisplayMenu::MAIN_MENU)
        data.setDisplayMenu(Data::DisplayMenu::SUB_MENU);
    else if (data.getDisplayMenu() == Data::DisplayMenu::SUB_MENU)
        data.setDisplayMenu(Data::DisplayMenu::FUNCTIONAL_SCREEN);

    Serial.println(String("DisplayMenu = ") + (data.getDisplayMenu() == Data::DisplayMenu::MAIN_MENU ? "MAIN_MENU"
        : (data.getDisplayMenu() == Data::DisplayMenu::SUB_MENU ? "SUB_MENU" : "FUNCTIONAL_SCREEN")));


    _selectedSubItem = 0;

    if (action)
        action();

    if (!subMenu.empty())
        displaySubMenu();
}

void MenuItem::selectedItemExecute()
{
    subMenu[_selectedSubItem].execute();
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

    /// получим текущее положени на странице с учетом того, что на странице 5 пунктов

    // количество страниц
    pagesCount = menuSize * INVERTED_SUB_MENU_ITEMS_SIZE + (menuSize % SUB_MENU_ITEMS_SIZE ? 1 : 0);

    // текущее положение на странице
    currentMenuPosition = _selectedSubItem % SUB_MENU_ITEMS_SIZE;

    // текущая страница
    currentPage = _selectedSubItem * INVERTED_SUB_MENU_ITEMS_SIZE;

    // отрисуем меню
    Data::getInstance().getScreen()->getDisplay()->printSubMenu(currentMenuPosition,
        subMenu[currentPage * SUB_MENU_ITEMS_SIZE].getName(),
        currentPage * SUB_MENU_ITEMS_SIZE + 1 < menuSize ? subMenu[currentPage * SUB_MENU_ITEMS_SIZE + 1].getName() : "",
        currentPage * SUB_MENU_ITEMS_SIZE + 2 < menuSize ? subMenu[currentPage * SUB_MENU_ITEMS_SIZE + 2].getName() : "",
        currentPage * SUB_MENU_ITEMS_SIZE + 3 < menuSize ? subMenu[currentPage * SUB_MENU_ITEMS_SIZE + 3].getName() : "",
        currentPage * SUB_MENU_ITEMS_SIZE + 4 < menuSize ? subMenu[currentPage * SUB_MENU_ITEMS_SIZE + 4].getName() : "");
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
