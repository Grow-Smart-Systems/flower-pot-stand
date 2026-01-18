#include "Screen.h"
#include "Menu/Menu.h"
#include "Menu/MenuBuilder.h"
#include "Display/Display.h"
#include "../Common/Containers/MenuInfoContainer.h"

Screen::Screen()
{
    _display = std::make_shared<Display>();
    _menuController = std::make_shared<MenuController>();
}

void Screen::LoopIteration()
{
    if (_screenTimer.ready())
    {
        // Обновим экран
        printMenu();
    }
}

void Screen::StartTimers()
{
    _screenTimer.start(200);
}

bool Screen::Init()
{
    bool result = _display->Init();
    if (!result)
    {
        Serial.println("Screen::Init | Error: Display initialization failed");
        return false;
    }
    InitMenu();
    return true;
}

void Screen::InitMenu()
{
    Data::GetInstance().SetDisplayMode(DisplayMode::MENU_MODE);
    Data::GetInstance().SetDisplayMenu(DisplayMenu::MAIN_MENU);

    // Создаём корневое меню
    auto rootMenu = MenuBuilder::CreateRootMenu(DisplayMenu::MAIN_MENU);
    if (!rootMenu)
        return;

    _menuController->SetRootMenu(rootMenu);

    // Создаём меню сенсоров
    auto sensorsMenu = MenuBuilder::CreateSubMenu("Sensors", rootMenu, DisplayMenu::SUB_MENU);
    if (!sensorsMenu)
        return;

    {
        MenuBuilder::AddAction("Temperature", sensorsMenu,
            std::bind(&Screen::temperatureAction, this),
            DisplayMenu::FUNCTIONAL_MENU);

        MenuBuilder::AddAction("Humidity", sensorsMenu,
            std::bind(&Screen::humidityAction, this),
            DisplayMenu::FUNCTIONAL_MENU);

        MenuBuilder::AddAction("Lux", sensorsMenu,
            std::bind(&Screen::luxAction, this),
            DisplayMenu::FUNCTIONAL_MENU);
    }

    // Создаём меню настроек
    auto settingsMenu = MenuBuilder::CreateSubMenu("Settings", rootMenu, DisplayMenu::SUB_MENU);
    if (!settingsMenu)
        return;

    {
        MenuBuilder::AddAction("WiFi", settingsMenu,
            std::bind(&Screen::wifiAction, this),
            DisplayMenu::FUNCTIONAL_MENU);

        MenuBuilder::AddAction("Service connection", settingsMenu,
            std::bind(&Screen::serviceConnectionAction, this),
            DisplayMenu::FUNCTIONAL_MENU);
    }

    // Создаём меню "О программе"
    auto aboutMenu = MenuBuilder::CreateSubMenu("About", rootMenu, DisplayMenu::SUB_MENU);
    if (!aboutMenu)
        return;

    {
        MenuBuilder::AddAction("Version", aboutMenu,
            std::bind(&Screen::versionAction, this),
            DisplayMenu::FUNCTIONAL_MENU);

        MenuBuilder::AddAction("Author", aboutMenu,
            std::bind(&Screen::authorAction, this),
            DisplayMenu::FUNCTIONAL_MENU);
    }
}

void Screen::temperatureAction()
{
    Serial.println("Screen | temperatureAction");
    Data::GetInstance().SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    Data::GetInstance().SetDisplayFunctionalScreen(DisplayFunctionalScreen::TEMPERATURE_SENSOR_SCREEN);
}

void Screen::humidityAction()
{
    Serial.println("Screen | humidityAction (not implemented)");
    Data::GetInstance().SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    Data::GetInstance().SetDisplayFunctionalScreen(DisplayFunctionalScreen::UNDEFINED_FUNCTIONAL_SCREEN);
}

void Screen::luxAction()
{
    Serial.println("Screen | luxAction (not implemented)");
    Data::GetInstance().SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    Data::GetInstance().SetDisplayFunctionalScreen(DisplayFunctionalScreen::UNDEFINED_FUNCTIONAL_SCREEN);
}

void Screen::wifiAction()
{
    Serial.println("Screen | wifiAction (not implemented)");
    Data::GetInstance().SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    Data::GetInstance().SetDisplayFunctionalScreen(DisplayFunctionalScreen::UNDEFINED_FUNCTIONAL_SCREEN);
}

void Screen::serviceConnectionAction()
{
    Serial.println("Screen | serviceConnectionAction (not implemented)");
    Data::GetInstance().SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    Data::GetInstance().SetDisplayFunctionalScreen(DisplayFunctionalScreen::UNDEFINED_FUNCTIONAL_SCREEN);
}

void Screen::versionAction()
{
    Serial.println("Screen | versionAction (not implemented)");
    Data::GetInstance().SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    Data::GetInstance().SetDisplayFunctionalScreen(DisplayFunctionalScreen::UNDEFINED_FUNCTIONAL_SCREEN);
}

void Screen::authorAction()
{
    Serial.println("Screen | authorAction (not implemented)");
    Data::GetInstance().SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    Data::GetInstance().SetDisplayFunctionalScreen(DisplayFunctionalScreen::UNDEFINED_FUNCTIONAL_SCREEN);
}

void Screen::PrintInitializeScreen()
{
    _display->DispayOn();
    _display->PrintInitializeScreen();
}

void Screen::printMenu()
{
    if (Data::GetInstance().GetDisplayMode() != DisplayMode::MENU_MODE)
        return;

    const auto& displayInfo = _menuController->GetDisplayInfo();
    switch (displayInfo.displayMenu)
    {
        case DisplayMenu::MAIN_MENU:
            displayMainMenu(displayInfo);
            break;
        case DisplayMenu::SUB_MENU:
            displaySubMenu(displayInfo);
            break;
        case DisplayMenu::FUNCTIONAL_MENU:
            displayFunctionMenu(displayInfo);
            break;
        default:
            break;
    }
}

void Screen::ShowMenu()
{
    auto& data = Data::GetInstance();
    data.SetDisplayMode(DisplayMode::MENU_MODE);
    data.SetDisplayMenu(DisplayMenu::MAIN_MENU);
}

void Screen::MovemenuUp()
{
    Serial.println("Screen | movemenuUp");
    if (Data::GetInstance().GetDisplayMode() != DisplayMode::MENU_MODE)
        return;

    _menuController->NavigateUp();
}

void Screen::MovemenuDown()
{
    Serial.println("Screen | movemenuDown");
    if (Data::GetInstance().GetDisplayMode() != DisplayMode::MENU_MODE)
        return;

    _menuController->NavigateDown();
}

void Screen::MovemenuBack()
{
    Serial.println("Screen | movemenuBack");
    if (Data::GetInstance().GetDisplayMode() != DisplayMode::MENU_MODE)
        return;

    _menuController->Back();
}

void Screen::MovemenuEnter()
{
    Serial.println("Screen | movemenuEnter");
    if (Data::GetInstance().GetDisplayMode() != DisplayMode::MENU_MODE)
        return;

    _menuController->SelectOption();
}

void Screen::displayMainMenu(const MenuInfoContainer& info)
{
    // Валидация входных данных
    if (info.menuSize == 0 ||
        info.text.size() != info.menuSize ||
        info.currentIndex < 0 ||
        info.currentIndex >= info.menuSize)
        return;

    // Определение видимости навигационных треугольников
    const bool upTriangle = info.currentIndex > 0 && info.menuSize > MENU_MAIN_ITEMS_SIZE;
    const bool downTriangle = info.currentIndex < info.menuSize - 1 && info.menuSize > MENU_MAIN_ITEMS_SIZE;

    // Инициализация массива указателей на строки
    const std::string* text[MENU_MAIN_ITEMS_SIZE] = {nullptr};

    // Вычисление позиции и заполнение указателей
    int currentMenuPosition = std::min(1, std::max(0, info.menuSize - 1));

    if (info.menuSize > 2)
    {
        currentMenuPosition = (info.currentIndex == 0) ? 0 :
            (info.currentIndex == info.menuSize - 1) ? 2 : 1;

        const int startIndex = info.currentIndex - currentMenuPosition;
        for (int i = 0; i < MENU_MAIN_ITEMS_SIZE; ++i)
        {
            const int itemIndex = startIndex + i;
            if (itemIndex >= 0 && itemIndex < info.menuSize)
            {
                // Сохраняем указатель
                text[i] = &info.text[itemIndex];
            }
        }
    }
    else
    {
        currentMenuPosition = info.currentIndex;
        for (int i = 0; i < info.menuSize; ++i)
        {
            // Сохраняем указатель
            text[i] = &info.text[i];
        }
    }

    // Вывод меню, передаём пустые строки для nullptr
    _display->PrintMainMenu(
        currentMenuPosition,
        upTriangle,
        downTriangle,
        text[0] ? *text[0] : "",
        text[1] ? *text[1] : "",
        text[2] ? *text[2] : ""
    );
}

void Screen::displaySubMenu(const MenuInfoContainer& info)
{
    // Валидация входных данных
    if (info.menuSize == 0 ||
        info.text.size() != info.menuSize ||
        info.currentIndex < 0 ||
        info.currentIndex >= info.menuSize)
        return;

    // Вычисление текущей позиции и страницы
    const int itemsPerPage = SUB_MENU_ITEMS_SIZE;
    const int pagesCount = (info.menuSize + itemsPerPage - 1) / itemsPerPage;
    const int currentMenuPosition = info.currentIndex % itemsPerPage;
    const int currentPage = info.currentIndex / itemsPerPage;

    // Инициализация массива указателей на строки
    const std::string* text[SUB_MENU_ITEMS_SIZE] = {nullptr};

    // Заполнение массива указателей
    const int startIndex = currentPage * itemsPerPage;
    for (int i = 0; i < SUB_MENU_ITEMS_SIZE; ++i)
    {
        const int itemIndex = startIndex + i;
        if (itemIndex < info.menuSize)
            text[i] = &info.text[itemIndex];
    }

    // Отрисовка меню
    _display->PrintSubMenu(
    currentMenuPosition,
    text[0] ? *text[0] : "",
    text[1] ? *text[1] : "",
    text[2] ? *text[2] : "",
    text[3] ? *text[3] : "",
    text[4] ? *text[4] : ""
    );
}

void Screen::displayFunctionMenu(const MenuInfoContainer& info)
{
    _display->PrintFunctionMenu(false);
}