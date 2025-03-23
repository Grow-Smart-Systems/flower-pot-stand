#pragma once

#include <Arduino.h>
#include <memory>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "../Common/DeviceInterface/DeviceInterface.h"

#include "../Common/Data.h"
#include "Menu/MenuController.h"
#include "../Utils/Timer.h"

class Display;
class MenuController;
class MenuInfoContainer;


/// @brief Общий класс управлением и взаимодействием с экраном
class Screen final : public DeviceInterface
{
    /// @brief Инвертированное значение количества пунктов меню
    const float INVERTED_SUB_MENU_ITEMS_SIZE {1.0f / 5.0f};

    /// @brief Количество пунктов главного меню
    constexpr static int MENU_MAIN_ITEMS_SIZE {3};

    /// @brief Количество пунктов подменю
    constexpr static int SUB_MENU_ITEMS_SIZE {5};

public:
    /// @brief Конструктор
    Screen();

    /// @brief Деструктор по умолчанию
    ~Screen() = default;

    /// @brief Итератор цикла
    void LoopIteration() override;

    /// @brief Запуск таймеров
    void StartTimers() override;

    /// @brief Инициализация экрана
    /// @return true - успешно, false - ошибка
    bool Init();

    /// @brief Инициализация меню
    void InitMenu();

    /// @brief Печать старового изображения на экране
    void PrintInitializeScreen();

    /// @brief Команда на отображения меню на экране
    void ShowMenu();

    /// Movement section ///

    /// @brief Перемещает указатель вверх по меню
    void MovemenuUp();

    /// @brief Перемещает указатель вниз по меню
    void MovemenuDown();

    /// @brief Перемещает указатель назад
    void MovemenuBack();

    /// @brief Выберает пункт меню
    void MovemenuEnter();

    /// Movement section end ///

    void temperatureAction();

protected:
    /// @brief Печать меню на экране
    void printMenu();

    /// @brief Отображение главного меню
    /// @param info Информация о меню
    void displayMainMenu(const MenuInfoContainer& info);

    /// @brief Отображение подменю
    /// @param info Информация о меню
    void displaySubMenu(const MenuInfoContainer& info);

    /// @brief Отображение функционального меню
    /// @param info Информация о меню
    void displayFunctionMenu(const MenuInfoContainer& info);

private:
    /// @brief Экземпляр дисплея объекта для SSD1306 с разрешением 128x64, с использованием аппаратного I2C.
    std::shared_ptr<Display> _display {nullptr};

    /// @brief Указатель на контроллер меню
    std::shared_ptr<MenuController> _menuController {nullptr};

    /// @brief Таймер для обновления экрана
    Timer _screenTimer;
};