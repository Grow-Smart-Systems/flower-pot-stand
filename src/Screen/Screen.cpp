#include "Screen.h"
#include "Menu/Menu.h"
#include "../Common/Containers/MenuInfoContainer.h"

Screen::Screen()
{
    _display = std::make_shared<Display>();
    _menuController = std::make_shared<MenuController>();
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

    auto rootMenu = _menuController->GetRootMenu();
    auto sensorsMenu = _menuController->CreateMenuItem("Sensors", rootMenu, nullptr);
    {
        auto tempMenuItem = _menuController->CreateMenuItem("Temperature", sensorsMenu, std::bind(&Screen::temperatureAction, this));
        tempMenuItem->SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);

        auto humidityMenuItem = _menuController->CreateMenuItem("Humidity", sensorsMenu, nullptr);
        humidityMenuItem->SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);

        auto luxMenuItem = _menuController->CreateMenuItem("Lux", sensorsMenu, nullptr);
        luxMenuItem->SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    }

    auto settingsMenu = _menuController->CreateMenuItem("Settings", rootMenu, nullptr);
    {
        auto wifiMenuItem = _menuController->CreateMenuItem("WiFi", settingsMenu, nullptr);
        wifiMenuItem->SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);

        auto serviceMenuItem = _menuController->CreateMenuItem("Service connection", settingsMenu, nullptr);
        serviceMenuItem->SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    }

    auto aboutMenu = _menuController->CreateMenuItem("About", rootMenu, nullptr);
    {
        auto versionMenuItem = _menuController->CreateMenuItem("Version", aboutMenu, nullptr);
        versionMenuItem->SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);

        auto authorMenuItem = _menuController->CreateMenuItem("Author", aboutMenu, nullptr);
        authorMenuItem->SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    }
}

void Screen::temperatureAction()
{
    Serial.println("Screen | temperatureAction");
    Data::GetInstance().SetDisplayMenu(DisplayMenu::FUNCTIONAL_MENU);
    Data::GetInstance().SetDisplayFunctionalScreen(DisplayFunctionalScreen::TEMPERATURE_SENSOR_SCREEN);
}

void Screen::PrintInitializeScreen()
{
    _display->DispayOn();
    _display->PrintInitializeScreen();
}

void Screen::PrintMenu()
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