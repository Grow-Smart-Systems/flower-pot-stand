#pragma once

#include <Arduino.h>
#include <vector>

#include "Display.h"

#define SUB_MENU_ITEMS_SIZE 5

class Display;

class MenuItem
{
public:
    MenuItem(const String& name, std::function<void()> action = nullptr);
    ~MenuItem() = default;

    String getName() const { return name; }

    void addSubMenu(const MenuItem& item);

    void execute();

    void back();

    void displaySubMenu() const;

    void selectNextItem();

    void selectPreviousItem();

private:

    String name;

    std::function<void()> action;

    std::vector<MenuItem> subMenu;

    int _selectedSubItem{ 0 };
};
