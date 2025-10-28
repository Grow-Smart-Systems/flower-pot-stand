# GitHub Issues на основе код-ревю / GitHub Issues Based on Code Review

Этот документ содержит описание задач (issues), которые необходимо создать в GitHub на основе проведенного код-ревю.

---

## Issue #1: 🔴 Критическая проблема - Утечка памяти в классе Sensors

**Заголовок / Title:**
```
[CRITICAL] Memory leak in Sensors class - Replace raw pointers with smart pointers
```

**Описание / Description:**
```markdown
## Проблема / Problem

В классе `Sensors` используются сырые указатели с ручным управлением памятью, что противоречит современным практикам C++17 и создает риск утечек памяти.

**Файл:** `src/Sensors/Sensors.cpp` (строки 12-31)

### Текущий код / Current code:
```cpp
Sensors::Sensors()
{
#if LIGHT_SENSOR == SENSOR_LM393
    _lightSensor = new LightSensorLM393();  // ❌ Raw pointer
#endif

#if TEMPERATURE_SENSOR == SENSOR_DHT11
    _temperatureSensor = new TemperatureSensorDHT11();  // ❌ Raw pointer
#endif
}

Sensors::~Sensors()
{
    if (_lightSensor)
        delete _lightSensor;

    if (_temperatureSensor)
        delete _temperatureSensor;
}
```

## Риски / Risks

- Возможная утечка памяти при исключении в конструкторе
- Нарушение правила "Rule of Five" (отсутствуют copy/move конструкторы и операторы)
- Опасность двойного освобождения памяти при копировании объекта
- Не exception-safe код

## Решение / Solution

Заменить сырые указатели на `std::unique_ptr`:

### Изменения в заголовочном файле `src/Sensors/Sensors.h`:
```cpp
// Было:
LightSensor* _lightSensor;
TemperatureSensor* _temperatureSensor;

// Стало:
std::unique_ptr<LightSensor> _lightSensor;
std::unique_ptr<TemperatureSensor> _temperatureSensor;
```

### Изменения в `src/Sensors/Sensors.cpp`:
```cpp
Sensors::Sensors()
{
#if LIGHT_SENSOR == SENSOR_LM393
    _lightSensor = std::make_unique<LightSensorLM393>();
#endif

#if TEMPERATURE_SENSOR == SENSOR_DHT11
    _temperatureSensor = std::make_unique<TemperatureSensorDHT11>();
#endif
}

// Деструктор больше не нужен (автоматическое освобождение)
Sensors::~Sensors() = default;
```

## Критерии приемки / Acceptance Criteria

- [ ] Заменены все сырые указатели на `std::unique_ptr` в классе `Sensors`
- [ ] Удален явный деструктор (используется `= default`)
- [ ] Код компилируется без ошибок и предупреждений
- [ ] Проверена работа с датчиками на реальном устройстве
- [ ] Проверено отсутствие утечек памяти (если возможно)

## Приоритет / Priority
🔴 **CRITICAL** - Требует немедленного исправления

## Метки / Labels
- `bug`
- `critical`
- `memory-management`
- `technical-debt`
- `C++`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #1
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 1 - Critical Fixes

---

## Issue #2: 🔴 Критическая проблема - Отсутствие проверки ошибок датчиков

**Заголовок / Title:**
```
[CRITICAL] Missing error handling for DHT11 sensor readings (NaN check)
```

**Описание / Description:**
```markdown
## Проблема / Problem

Датчик DHT11 может возвращать `NaN` при ошибке чтения, но это значение не проверяется перед использованием. Это приводит к распространению невалидных данных по всей системе.

**Файл:** `src/Sensors/TemperatureSensors/TemperatureSensorDHT11.cpp`

### Текущий код / Current code:
```cpp
float TemperatureSensorDHT11::GetTemperature()
{
    return _dht.readTemperature();  // ❌ No NaN check
}

float TemperatureSensorDHT11::GetHumidity()
{
    return _dht.readHumidity();  // ❌ No NaN check
}
```

## Последствия / Consequences

- Невалидные данные отображаются на дисплее
- Некорректные решения на основе датчиков
- Отсутствие информации об ошибках чтения
- Сложность отладки проблем с датчиками

## Решение / Solution

Добавить проверку на `NaN` и обработку ошибок:

```cpp
float TemperatureSensorDHT11::GetTemperature()
{
    float temp = _dht.readTemperature();
    if (isnan(temp)) {
        Serial.println("Error: Failed to read temperature from DHT11");
        // Опция 1: Вернуть последнее валидное значение
        // Опция 2: Вернуть специальное значение (например, -999.0f)
        // Опция 3: Вернуть 0.0f с флагом ошибки
        return _lastValidTemperature; // или 0.0f
    }
    _lastValidTemperature = temp;
    return temp;
}

float TemperatureSensorDHT11::GetHumidity()
{
    float humidity = _dht.readHumidity();
    if (isnan(humidity)) {
        Serial.println("Error: Failed to read humidity from DHT11");
        return _lastValidHumidity;
    }
    _lastValidHumidity = humidity;
    return humidity;
}
```

### Дополнительно в заголовочном файле:
```cpp
private:
    float _lastValidTemperature {0.0f};
    float _lastValidHumidity {0.0f};
```

## Критерии приемки / Acceptance Criteria

- [ ] Добавлена проверка `isnan()` для всех методов чтения датчиков
- [ ] Реализовано логирование ошибок через Serial
- [ ] Добавлено сохранение последних валидных значений
- [ ] Протестировано поведение при отключенном/неисправном датчике
- [ ] Обновлена документация методов

## Приоритет / Priority
🔴 **CRITICAL** - Требует немедленного исправления

## Метки / Labels
- `bug`
- `critical`
- `error-handling`
- `sensors`
- `DHT11`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #2
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 1 - Critical Fixes

---

## Issue #3: 🔴 Критическая проблема - Неправильное использование shared_ptr

**Заголовок / Title:**
```
[CRITICAL] Incorrect shared_ptr construction in Display class
```

**Описание / Description:**
```markdown
## Проблема / Problem

В классе `Display` используется небезопасная конструкция `shared_ptr` с оператором `new` вместо рекомендованного `std::make_shared`.

**Файл:** `src/Screen/Display/Display.cpp` (строки 9-12)

### Текущий код / Current code:
```cpp
Display::Display()
{
    _display = std::shared_ptr<Adafruit_SSD1306>(new Adafruit_SSD1306(SCREEN_WIDTH,
                                                                      SCREEN_HEIGHT,
                                                                      &Wire,
                                                                      OLED_RESET));
}
```

## Проблемы / Issues

1. **Неэффективное использование памяти**: Две отдельные аллокации вместо одной
2. **Не exception-safe**: Если конструктор `shared_ptr` выбросит исключение после `new`, произойдет утечка
3. **Худшая производительность**: Больше операций с памятью

## Решение / Solution

Использовать `std::make_shared`:

```cpp
Display::Display()
{
    _display = std::make_shared<Adafruit_SSD1306>(SCREEN_WIDTH,
                                                   SCREEN_HEIGHT,
                                                   &Wire,
                                                   OLED_RESET);
}
```

## Преимущества / Benefits

✅ Одна аллокация памяти вместо двух  
✅ Exception-safe код  
✅ Лучшая производительность  
✅ Более чистый и читаемый код  

## Критерии приемки / Acceptance Criteria

- [ ] Заменено создание `shared_ptr` на `std::make_shared` в классе `Display`
- [ ] Код компилируется без ошибок
- [ ] Дисплей корректно инициализируется и работает
- [ ] Найдены и исправлены аналогичные проблемы в других частях кода

## Приоритет / Priority
🔴 **CRITICAL** - Исправить в Phase 1

## Метки / Labels
- `bug`
- `critical`
- `memory-management`
- `C++`
- `code-quality`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #3
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 1 - Critical Fixes

---

## Issue #4: 🟠 Серьезная проблема - Отсутствие bounds checking

**Заголовок / Title:**
```
[HIGH] Missing bounds checking for negative indices in Menu::GetMenuItemAt()
```

**Описание / Description:**
```markdown
## Проблема / Problem

Метод `Menu::GetMenuItemAt()` не проверяет отрицательные значения индекса, что может привести к неопределенному поведению.

**Файл:** `src/Screen/Menu/Menu.cpp` (строки 52-56)

### Текущий код / Current code:
```cpp
const MenuItem& Menu::GetMenuItemAt(int index)
{
    if (index >= _menuItems.size())  // ❌ Не проверяется index < 0
        return _emptyItem;
    return _menuItems[index];
}
```

## Риск / Risk

- Undefined behavior при передаче отрицательного индекса
- Возможный segmentation fault
- Доступ к произвольной памяти

## Решение / Solution

```cpp
const MenuItem& Menu::GetMenuItemAt(int index)
{
    if (index < 0 || index >= static_cast<int>(_menuItems.size()))
        return _emptyItem;
    return _menuItems[index];
}
```

## Критерии приемки / Acceptance Criteria

- [ ] Добавлена проверка на отрицательные индексы
- [ ] Найдены и исправлены аналогичные проблемы в других методах
- [ ] Добавлены тесты для граничных случаев (если есть тестовая инфраструктура)
- [ ] Код проверен статическими анализаторами

## Приоритет / Priority
🟠 **HIGH** - Исправить в Phase 1

## Метки / Labels
- `bug`
- `high-priority`
- `bounds-checking`
- `safety`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #5
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 1 - Critical Fixes

---

## Issue #5: 🟠 Серьезная проблема - Магические числа в коде клавиатуры

**Заголовок / Title:**
```
[HIGH] Magic numbers in keyboard threshold configuration
```

**Описание / Description:**
```markdown
## Проблема / Problem

В классе `AdKeyboardDevice` используются магические числа без объяснения их значения, что затрудняет понимание и модификацию кода.

**Файл:** `src/ControlDevices/AdKeyboardDevice.cpp`

### Текущий код / Current code:
```cpp
if (value < 3000)  // ❌ Magic number
{
    // ...
}

const int thresholds[KEYS_COUNT + 1] = {0, 50, 500, 1200, 2000, 2800};  // ❌ Magic numbers
```

## Проблемы / Issues

- Непонятно, откуда взялись эти значения
- Сложно изменить конфигурацию
- Нет документации по калибровке
- Трудно адаптировать под разные клавиатуры

## Решение / Solution

### В заголовочном файле `AdKeyboardDevice.h`:
```cpp
class AdKeyboardDevice final
{
    // Максимальное значение АЦП для валидного нажатия
    static constexpr int ANALOG_READ_MAX_VALUE = 3000;
    
    // Пороговые значения для кнопок (калиброваны для конкретной клавиатуры)
    static constexpr int THRESHOLD_BUTTON_1 = 50;
    static constexpr int THRESHOLD_BUTTON_2 = 500;
    static constexpr int THRESHOLD_BUTTON_3 = 1200;
    static constexpr int THRESHOLD_BUTTON_4 = 2000;
    static constexpr int THRESHOLD_BUTTON_5 = 2800;
    
    // Массив порогов для итерации
    static constexpr int BUTTON_THRESHOLDS[KEYS_COUNT + 1] = {
        0, 
        THRESHOLD_BUTTON_1, 
        THRESHOLD_BUTTON_2, 
        THRESHOLD_BUTTON_3, 
        THRESHOLD_BUTTON_4, 
        THRESHOLD_BUTTON_5
    };
    
    // ... остальной код
};
```

### В cpp файле:
```cpp
if (value < ANALOG_READ_MAX_VALUE)
{
    // ...
}

int AdKeyboardDevice::getKey(int value)
{
    for (int i = 0; i < KEYS_COUNT; ++i)
    {
        if (value >= BUTTON_THRESHOLDS[i] && value < BUTTON_THRESHOLDS[i + 1])
        {
            return i;
        }
    }
    return -1;
}
```

## Дополнительно / Additionally

Рекомендуется добавить:
- Комментарии с объяснением происхождения значений
- Инструкцию по калибровке в документации
- Возможность настройки через конфигурационный файл (опционально)

## Критерии приемки / Acceptance Criteria

- [ ] Все магические числа заменены на именованные константы
- [ ] Добавлены комментарии с объяснением значений
- [ ] Код компилируется и работает корректно
- [ ] Создана документация по калибровке клавиатуры

## Приоритет / Priority
🟠 **HIGH** - Исправить в Phase 2

## Метки / Labels
- `enhancement`
- `code-quality`
- `maintainability`
- `documentation`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #6
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 2 - Quality Improvements

---

## Issue #6: 🟠 Серьезная проблема - Неэффективное копирование строк

**Заголовок / Title:**
```
[HIGH] Inefficient string copying in MenuItem::GetName()
```

**Описание / Description:**
```markdown
## Проблема / Problem

Метод `GetName()` возвращает строку по значению, что приводит к ненужному копированию.

**Файл:** `src/Screen/Menu/MenuItem.h`

### Текущий код / Current code:
```cpp
std::string GetName() const  // ❌ Возвращает копию
{
    return _name;
}
```

## Влияние на производительность / Performance Impact

- Каждый вызов создает копию строки
- На ESP32 с ограниченной памятью это критично
- Метод вызывается часто при отрисовке меню

## Решение / Solution

```cpp
const std::string& GetName() const  // ✅ Возвращает константную ссылку
{
    return _name;
}
```

## Дополнительные места для исправления / Additional Fixes

Найти и исправить аналогичные проблемы в других геттерах:
- [ ] `MenuItem::GetName()`
- [ ] Другие методы, возвращающие строки или контейнеры

## Критерии приемки / Acceptance Criteria

- [ ] Изменен возвращаемый тип на `const std::string&`
- [ ] Проверены все аналогичные методы в проекте
- [ ] Код компилируется без warning'ов
- [ ] Проверено отсутствие проблем с временем жизни объектов

## Приоритет / Priority
🟠 **HIGH** - Исправить в Phase 2

## Метки / Labels
- `performance`
- `optimization`
- `C++`
- `memory-efficiency`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #7
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 2 - Quality Improvements

---

## Issue #7: 🟡 Средний приоритет - Централизация конфигурации GPIO

**Заголовок / Title:**
```
[MEDIUM] Centralize GPIO pin configuration
```

**Описание / Description:**
```markdown
## Проблема / Problem

GPIO пины разбросаны по разным файлам без единой конфигурации и документации их назначения.

**Текущее состояние:**
- `src/ESP32_defines.h` - частичное определение
- Дублирование в разных файлах
- Отсутствие комментариев о назначении пинов

### Текущий код / Current code:
```cpp
// ESP32_defines.h
#define GPIO32 32
#define GPIO33 33
#define GPIO25 25
#define GPIO35 35

// AdKeyboardDevice.h
#define KEYBOARD_PIN GPIO32

// LightSensorLM393.cpp
#define PIN_ANALOG_PHOTO_SENSOR GPIO35
```

## Решение / Solution

Создать централизованный файл конфигурации:

### Новый файл `src/Config/PinConfiguration.h`:
```cpp
#pragma once

/// @file PinConfiguration.h
/// @brief Централизованная конфигурация GPIO пинов ESP32

namespace Config {
namespace Pins {

    // I2C интерфейс для OLED дисплея
    constexpr uint8_t SDA = 21;  // I2C Data
    constexpr uint8_t SCL = 22;  // I2C Clock
    
    // Аналоговая клавиатура
    constexpr uint8_t KEYBOARD_ANALOG = 32;  // GPIO32 - Аналоговый вход для клавиатуры
    
    // Датчик температуры и влажности
    constexpr uint8_t DHT11_SENSOR = 33;  // GPIO33 - DHT11 температура/влажность
    
    // Датчик освещенности
    constexpr uint8_t LIGHT_SENSOR = 35;  // GPIO35 - LM393 фоторезистор (только вход)
    
    // Резервные пины
    constexpr uint8_t RESERVED_1 = 25;  // GPIO25 - Зарезервирован для будущего использования

} // namespace Pins
} // namespace Config
```

### Обновить использование:
```cpp
// В AdKeyboardDevice.h
#include "Config/PinConfiguration.h"
// ...
pinMode(Config::Pins::KEYBOARD_ANALOG, INPUT);

// В LightSensorLM393.cpp
#include "Config/PinConfiguration.h"
// ...
analogRead(Config::Pins::LIGHT_SENSOR);
```

## Дополнительно / Additionally

Создать схему подключения в документации:
```
ESP32 GPIO Pin Layout для Flower Pot Stand
==========================================
GPIO21 (SDA)    -> OLED Display SDA
GPIO22 (SCL)    -> OLED Display SCL
GPIO32          -> Analog Keyboard Input
GPIO33          -> DHT11 Sensor
GPIO35          -> LM393 Light Sensor (Input only)
```

## Критерии приемки / Acceptance Criteria

- [ ] Создан файл `src/Config/PinConfiguration.h`
- [ ] Все пины документированы с комментариями
- [ ] Обновлены все файлы, использующие GPIO
- [ ] Удалены дублирующиеся определения
- [ ] Добавлена схема подключения в README или отдельный документ
- [ ] Код компилируется и работает

## Приоритет / Priority
🟡 **MEDIUM** - Исправить в Phase 2

## Метки / Labels
- `enhancement`
- `refactoring`
- `configuration`
- `documentation`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #11
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 2 - Quality Improvements

---

## Issue #8: 🟡 Средний приоритет - TODO комментарии в production коде

**Заголовок / Title:**
```
[MEDIUM] Resolve or track TODO comments in production code
```

**Описание / Description:**
```markdown
## Проблема / Problem

В production коде присутствуют TODO комментарии без отслеживания в issue tracker.

### Найденные TODO:

1. **Файл:** `src/ControlDevices/ControlDevices.cpp` (строки 17-18)
```cpp
// TODO: 1. Не совсем удачное решение использовать процессор серийного порта, но пока так
// TODO: 2. Нужно отладить с настоящим устройством, кнопки могут работать не так как ожидается
```

2. **Файл:** `src/Screen/Display/Display.cpp` (строка 167)
```cpp
//TODO: Доделать реализацию. Выводить статус бар с текущим временем и статусом сети и пр.
```

## Решение / Solution

Для каждого TODO нужно:

### TODO #1: Рефакторинг обработки команд клавиатуры
- **Проблема:** Использование `SerialPortProcessor` для обработки кнопок не оптимально
- **Решение:** Создать отдельный `ButtonCommandProcessor` или использовать паттерн Command
- **Приоритет:** Средний
- **Создать issue:** "Refactor keyboard button command processing"

### TODO #2: Тестирование с реальным устройством
- **Проблема:** Пороговые значения кнопок могут требовать калибровки
- **Решение:** Провести тестирование с реальной клавиатурой и документировать результаты
- **Приоритет:** Высокий (перед production deployment)
- **Создать issue:** "Test and calibrate keyboard button thresholds on real hardware"

### TODO #3: Реализация полного статус-бара
- **Проблема:** Неполная реализация статус-бара на дисплее
- **Решение:** Добавить время, статус WiFi, статус сенсоров
- **Приоритет:** Низкий (feature enhancement)
- **Создать issue:** "Implement complete status bar with time and network status"

## Действия / Actions

1. Создать отдельные issues для каждого TODO
2. Удалить TODO комментарии из кода или заменить на ссылки на issues
3. Установить правило: новые TODO создаются только вместе с issue

## Критерии приемки / Acceptance Criteria

- [ ] Для каждого TODO создан отдельный issue
- [ ] TODO комментарии удалены или заменены на `// See issue #XXX`
- [ ] Добавлено правило в CONTRIBUTING.md о работе с TODO

## Приоритет / Priority
🟡 **MEDIUM** - Исправить в Phase 2

## Метки / Labels
- `technical-debt`
- `documentation`
- `project-management`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #10
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 2 - Quality Improvements

---

## Issue #9: 🔵 Дизайн - Нарушение Single Responsibility Principle в Screen

**Заголовок / Title:**
```
[DESIGN] Refactor Screen class - violates Single Responsibility Principle
```

**Описание / Description:**
```markdown
## Проблема / Problem

Класс `Screen` имеет слишком много ответственностей, что нарушает принцип единой ответственности (SRP).

**Файл:** `src/Screen/Screen.cpp`

### Текущие ответственности класса Screen:

1. Управление дисплеем (hardware interaction)
2. Управление меню (menu logic)
3. Обработка таймеров (timing)
4. Логика отображения (rendering)
5. Координация между компонентами

## Последствия / Consequences

- Сложность тестирования
- Высокая связанность (coupling)
- Трудность модификации
- Нарушение принципов SOLID

## Решение / Solution

Разделить класс `Screen` на специализированные компоненты:

### Предлагаемая архитектура:

```
ScreenController (координатор)
├── DisplayDriver (низкоуровневая работа с дисплеем)
├── MenuSystem (логика меню)
├── ScreenRenderer (отрисовка UI элементов)
└── ScreenTimer (управление обновлениями)
```

### Пример реализации:

```cpp
// ScreenController.h
class ScreenController final : public DeviceInterface
{
public:
    ScreenController();
    
    void LoopIteration() override;
    void StartTimers() override;
    bool Init();
    
    // Делегирование к специализированным компонентам
    void ShowMenu();
    void MoveMenuUp();
    void MoveMenuDown();
    void MoveMenuBack();
    void MoveMenuEnter();
    
private:
    std::unique_ptr<DisplayDriver> _displayDriver;
    std::unique_ptr<MenuSystem> _menuSystem;
    std::unique_ptr<ScreenRenderer> _renderer;
    Timer _updateTimer;
};

// DisplayDriver.h - Низкоуровневая работа с дисплеем
class DisplayDriver final
{
public:
    bool Init();
    void Clear();
    void Display();
    Adafruit_SSD1306& GetDisplay();
    
private:
    std::shared_ptr<Adafruit_SSD1306> _display;
};

// MenuSystem.h - Логика меню
class MenuSystem final
{
public:
    void NavigateUp();
    void NavigateDown();
    void SelectOption();
    void GoBack();
    const MenuInfoContainer& GetDisplayInfo();
    
private:
    std::shared_ptr<MenuController> _menuController;
};

// ScreenRenderer.h - Отрисовка UI
class ScreenRenderer final
{
public:
    void RenderMainMenu(const MenuInfoContainer& info);
    void RenderSubMenu(const MenuInfoContainer& info);
    void RenderFunctionalScreen(const MenuInfoContainer& info);
    
private:
    DisplayDriver& _displayDriver;
};
```

## План рефакторинга / Refactoring Plan

### Фаза 1: Подготовка
- [ ] Создать unit тесты для текущего класса `Screen` (если их нет)
- [ ] Документировать текущее поведение

### Фаза 2: Разделение
- [ ] Создать класс `DisplayDriver`
- [ ] Создать класс `MenuSystem`
- [ ] Создать класс `ScreenRenderer`
- [ ] Обновить `ScreenController` для использования новых компонентов

### Фаза 3: Миграция
- [ ] Постепенно перенести функциональность
- [ ] Обновить все вызовы `Screen` в других частях кода
- [ ] Протестировать на реальном устройстве

### Фаза 4: Очистка
- [ ] Удалить старый класс `Screen`
- [ ] Обновить документацию
- [ ] Провести финальное тестирование

## Преимущества / Benefits

✅ Каждый класс имеет одну ответственность  
✅ Легче тестировать изолированно  
✅ Проще модифицировать и расширять  
✅ Лучшая читаемость и поддерживаемость  
✅ Соответствие SOLID принципам  

## Критерии приемки / Acceptance Criteria

- [ ] Создана новая архитектура с разделенными компонентами
- [ ] Все функциональность работает как раньше
- [ ] Код покрыт unit тестами
- [ ] Обновлена документация архитектуры
- [ ] Проведено тестирование на реальном устройстве

## Приоритет / Priority
🔵 **DESIGN** - Долгосрочный рефакторинг (Phase 3)

## Метки / Labels
- `refactoring`
- `architecture`
- `SOLID`
- `design-pattern`
- `long-term`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, проблема #15
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 3 - Architecture & Testing

---

## Issue #10: 🔵 Инфраструктура - Добавить unit тесты

**Заголовок / Title:**
```
[INFRASTRUCTURE] Add unit testing framework and initial tests
```

**Описание / Description:**
```markdown
## Проблема / Problem

Проект не имеет unit тестов, что затрудняет:
- Проверку корректности кода
- Рефакторинг
- Обнаружение регрессий
- Документирование ожидаемого поведения

**Текущее состояние:**
- ❌ Unit тесты отсутствуют
- ❌ Integration тесты отсутствуют
- ❌ CI/CD отсутствует

## Решение / Solution

### Фаза 1: Настройка инфраструктуры

1. **Выбрать фреймворк:** Unity или Google Test для embedded
2. **Настроить PlatformIO** для тестирования
3. **Создать структуру тестов**

### Рекомендуемая структура:
```
test/
├── unit/
│   ├── test_timer/
│   │   └── test_timer.cpp
│   ├── test_menu/
│   │   ├── test_menu_item.cpp
│   │   └── test_menu_controller.cpp
│   └── test_sensors/
│       └── test_sensors_container.cpp
├── integration/
│   └── test_system.cpp
└── mocks/
    ├── mock_display.h
    ├── mock_sensor.h
    └── mock_serial.h
```

### Пример конфигурации PlatformIO:

```ini
; platformio.ini
[env:test]
platform = native
test_framework = unity
build_flags = 
    -D UNIT_TEST
    -std=c++17
lib_deps = 
    throwtheswitch/Unity@^2.5.2
```

### Фаза 2: Создание mock объектов

Создать моки для:
- [ ] Adafruit_SSD1306 (дисплей)
- [ ] DHT (датчик температуры)
- [ ] Serial (последовательный порт)
- [ ] Wire (I2C)

### Фаза 3: Написание тестов

Приоритетные компоненты для тестирования:

1. **Timer класс** (простой, хорошая стартовая точка)
```cpp
// test/unit/test_timer/test_timer.cpp
#include <unity.h>
#include "Utils/Timer.h"

void test_timer_initialization()
{
    Timer timer;
    TEST_ASSERT_FALSE(timer.ready());
}

void test_timer_with_period()
{
    Timer timer(1000);
    delay(1100);
    TEST_ASSERT_TRUE(timer.ready());
}

void setup()
{
    UNITY_BEGIN();
    RUN_TEST(test_timer_initialization);
    RUN_TEST(test_timer_with_period);
    UNITY_END();
}
```

2. **Menu система** (критична для UI)
3. **Sensors контейнер** (работа с данными)
4. **Data singleton** (централизованное состояние)

### Фаза 4: CI/CD Integration

Настроить GitHub Actions:

```yaml
# .github/workflows/tests.yml
name: Run Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - name: Set up Python
        uses: actions/setup-python@v4
        with:
          python-version: '3.x'
      - name: Install PlatformIO
        run: pip install platformio
      - name: Run tests
        run: pio test -e test
```

## Метрики покрытия / Coverage Goals

- [ ] **Phase 1:** 30% coverage - критичные компоненты
- [ ] **Phase 2:** 50% coverage - основная функциональность
- [ ] **Phase 3:** 70%+ coverage - полное покрытие

## Критерии приемки / Acceptance Criteria

- [ ] Настроен test framework (Unity или Google Test)
- [ ] Создана структура директорий для тестов
- [ ] Созданы моки для hardware компонентов
- [ ] Написаны тесты для Timer класса
- [ ] Написаны тесты для Menu системы
- [ ] Написаны тесты для Data контейнеров
- [ ] Настроен CI/CD для автоматического запуска тестов
- [ ] Документация по запуску тестов в README

## Примеры для разработки / Development Examples

### Тестирование Menu:
```cpp
void test_menu_navigation()
{
    Menu menu;
    menu.AddMenuItem(MenuItem("Item 1"));
    menu.AddMenuItem(MenuItem("Item 2"));
    
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
    menu.SelectNextItem();
    TEST_ASSERT_EQUAL(1, menu.GetCurrentIndex());
    menu.SelectPreviousItem();
    TEST_ASSERT_EQUAL(0, menu.GetCurrentIndex());
}
```

### Тестирование SensorsDataContainer:
```cpp
void test_sensor_data_initialization()
{
    SensorsDataContainer container;
    TEST_ASSERT_EQUAL_FLOAT(0.0f, container.temperature);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, container.humidity);
    TEST_ASSERT_EQUAL_UINT16(0, container.lux);
}
```

## Приоритет / Priority
🔵 **INFRASTRUCTURE** - Phase 3, критично для долгосрочной поддержки

## Метки / Labels
- `testing`
- `infrastructure`
- `ci-cd`
- `quality-assurance`
- `long-term`

## Связанные задачи / Related Issues
- См. CODE_REVIEW.md, раздел "Тестирование"
- Связано с Issue #9 (рефакторинг для тестируемости)
```

**Исполнитель / Assignee:** TBD  
**Milestone:** Phase 3 - Architecture & Testing

---

## Инструкция по созданию issues / Instructions for Creating Issues

### В GitHub Web UI:

1. Перейти в раздел **Issues** репозитория
2. Нажать **New Issue**
3. Скопировать заголовок из этого документа
4. Скопировать описание (markdown) из этого документа
5. Добавить указанные метки (Labels)
6. Назначить Milestone
7. При необходимости назначить Assignee
8. Нажать **Submit new issue**

### Через GitHub CLI:

```bash
# Установить gh cli, если не установлен
# brew install gh  # macOS
# или скачать с https://cli.github.com/

# Создать issue из markdown файла
gh issue create --title "[CRITICAL] Memory leak in Sensors class" \
  --body-file issue_1.md \
  --label "bug,critical,memory-management" \
  --milestone "Phase 1"
```

### Рекомендуемый порядок создания / Recommended Order:

1. ✅ Issue #1 - Memory leak (CRITICAL)
2. ✅ Issue #2 - Error handling (CRITICAL)
3. ✅ Issue #3 - shared_ptr (CRITICAL)
4. ✅ Issue #4 - Bounds checking (HIGH)
5. Issue #5 - Magic numbers (HIGH)
6. Issue #6 - String copying (HIGH)
7. Issue #7 - GPIO config (MEDIUM)
8. Issue #8 - TODO comments (MEDIUM)
9. Issue #9 - SRP violation (DESIGN)
10. Issue #10 - Unit tests (INFRASTRUCTURE)

---

## Дополнительные рекомендации / Additional Recommendations

### Project Board

Создать GitHub Project Board с колонками:
- 📋 **Backlog** - Все новые issues
- 🔴 **Phase 1: Critical** - Критические исправления
- 🟠 **Phase 2: Quality** - Улучшения качества
- 🔵 **Phase 3: Architecture** - Долгосрочный рефакторинг
- 🚧 **In Progress** - В работе
- ✅ **Done** - Завершено

### Шаблоны Issues

Рекомендуется создать templates в `.github/ISSUE_TEMPLATE/`:
- `bug_report.md`
- `feature_request.md`
- `refactoring.md`

---

**Документ создан на основе:** CODE_REVIEW.md  
**Дата:** 2025-10-28  
**Следующий шаг:** Создание issues в GitHub
