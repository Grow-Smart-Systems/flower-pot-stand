#pragma once

#include <Arduino.h>
#include <memory>

#include "Display.h"
#include "MenuItem.h"


class Menu
{
public:
    Menu(std::shared_ptr<Display>& display);

    ~Menu() = default;

    void addItem(const MenuItem& item);

    void showMenu() const;

    void showSubMenu() const;

    void executeMenu();

    void selectNextItem();

    void selectPreviousItem();

private:
    std::vector<MenuItem> _menu;

    std::shared_ptr<Display> _display;

    int _selectedItem{ 0 };
};
