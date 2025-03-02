#pragma once

#include <Arduino.h>
#include <memory>
#include "../../Common/Data.h"

#define SUB_MENU_ITEMS_SIZE 5

class Menu;

class MenuController
{
    const float INVERTED_SUB_MENU_ITEMS_SIZE {1.0f / 5.0f};

public:
    MenuController();

    ~MenuController() = default;

    void DisplayMenu();

    std::shared_ptr<Menu> GetRootMenu() const;

    std::shared_ptr<Menu> CreateMenuItem(const String& name,
                                         std::shared_ptr<Menu> parentMenu,
                                         std::function<void()> action = nullptr);

    void GotoRootMenu();

    // MOVEMENT SECTION //

    void NavigateUp();

    void NavigateDown();

    void SelectOption();

    void Back();

protected:

    void displayMainMenu();

    void displaySubMenu();

    void displayFunctionMenu();

private:
    std::shared_ptr<Menu> _rootMenu {nullptr};
    std::shared_ptr<Menu> _currentMenu {nullptr};
};