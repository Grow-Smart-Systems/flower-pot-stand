#pragma once

#include <Arduino.h>
#include <vector>

#include "Display.h"

#define SUB_MENU_ITEMS_SIZE 5

class MenuItem
{
public:
    MenuItem(std::shared_ptr<Display> display, const String& name, std::function<void()> action = nullptr);

    void addSubMenu(const MenuItem& item);

    void execute();

    void back();

    void displaySubMenu() const;

    String getName() const { return name; }

    void selectNextItem();

    void selectPreviousItem();

private:

    std::shared_ptr<Display> _display;

    String name;

    std::function<void()> action;

    std::vector<MenuItem> subMenu;

    int _selectedSubItem{ 0 };


};
