#pragma once

#include <Arduino.h>
#include <memory>
#include <vector>
#include <string>

#include "../EnumClasses.h"


/// @brief Контейнер предачи информации о меню
struct MenuInfoContainer
{
    /// @brief Текущий индекс
    int currentIndex {0};

    /// @brief Размер меню
    int menuSize {0};

    /// @brief Тип меню
    DisplayMenu displayMenu {DisplayMenu::MAIN_MENU};

    /// @brief Набор текста в меню
    std::vector<std::string> text;
};
