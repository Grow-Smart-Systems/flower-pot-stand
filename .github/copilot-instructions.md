# Copilot Instructions — Flower Pot Stand (ESP32)

## Обзор проекта

Встраиваемая система на ESP32 для мониторинга растений с OLED-дисплеем (SSD1306), датчиками (DHT11, LM393) и навигацией через аналоговую клавиатуру. Arduino Framework, PlatformIO, C++17.

## Архитектура

### Ключевые компоненты

```
Data (Singleton)  ─────────────────────────────────────────────────────────────┐
    │                                                                          │
    └─► DeviceInterfaceController ─► vector<DeviceInterface>                   │
              │                            │                                   │
              │        ┌───────────────────┼───────────────────┐               │
              │        ▼                   ▼                   ▼               │
              │     Screen            Sensors          ControlDevices          │
              │        │                   │                   │               │
              │   MenuController    LightSensor        AdKeyboard              │
              │   Display           TemperatureSensor  SerialPortProcessor     │
              │                                                                │
              └─► MakeLoopIterations() вызывает LoopIteration() у всех ◄───────┘
```

- **`Data`** ([src/Common/Data.h](src/Common/Data.h)) — глобальный Singleton, хранит ссылки на все компоненты и статусы (`TemperatureStatus`, `HumidityStatus`, etc.)
- **`DeviceInterface`** ([src/Common/DeviceInterface/DeviceInterface.h](src/Common/DeviceInterface/DeviceInterface.h)) — базовый интерфейс для всех устройств с методами `LoopIteration()` и `StartTimers()`
- **`DeviceInterfaceController`** — агрегирует устройства и вызывает их методы в main loop

### Иерархия меню

Меню строится через **Builder pattern** ([src/Screen/Menu/MenuBuilder.h](src/Screen/Menu/MenuBuilder.h)):
- `IMenuItem` — интерфейс пунктов меню
- `ActionMenuItem` — пункт с callback-действием
- `SubMenuItem` — пункт с вложенным подменю
- `Menu` — контейнер с навигацией (parent-child связи через `weak_ptr`/`shared_ptr`)

Три типа отображения: `MAIN_MENU`, `SUB_MENU`, `FUNCTIONAL_MENU` (см. `DisplayMenu` enum).

### Сенсоры

Абстракция через `BaseSensor::SetDataIn(SensorsDataContainer&)`. Конкретные реализации:
- `TemperatureSensorDHT11` → `TemperatureSensor` → `BaseSensor`
- `LightSensorLM393` → `LightSensor` → `BaseSensor`

Выбор сенсора через define в [src/Sensors/SensorsConfiguration.h](src/Sensors/SensorsConfiguration.h).

## Паттерны и соглашения

### Умные указатели
- `std::shared_ptr` для компонентов, хранящихся в `Data` и передаваемых между модулями
- `std::unique_ptr` для пунктов меню (`IMenuItem`)
- `std::weak_ptr` для parent-ссылок меню (избежание циклических зависимостей)

### Таймеры
Вместо `delay()` используй класс `Timer` ([src/Utils/Timer.h](src/Utils/Timer.h)):
```cpp
Timer _timer(1000);
if (_timer.ready()) { /* действие каждую секунду */ }
```

### Добавление нового устройства
1. Создай класс, наследующий `DeviceInterface`
2. Реализуй `LoopIteration()` и `StartTimers()`
3. Добавь в `Data` через setter
4. Зарегистрируй через `DeviceInterfaceController::AddDevice()`

### Добавление нового сенсора
1. Наследуй от `LightSensor` или `TemperatureSensor`
2. Реализуй `SetDataIn(SensorsDataContainer&)`
3. Добавь define в `SensorsList.h`
4. Выбери в `SensorsConfiguration.h`

## Сборка и отладка

```bash
# Сборка release
pio run -e release

# Сборка debug
pio run -e debug

# Загрузка на плату
pio run -t upload

# Мониторинг Serial (115200 baud)
pio device monitor
```

Debug через `esp-prog` с точкой останова в `setup()`.

## Структура файлов

| Директория | Назначение |
|------------|------------|
| `src/Common/` | Shared типы, `Data`, `DeviceInterface`, контейнеры |
| `src/Screen/` | Дисплей, меню, функциональные экраны |
| `src/Sensors/` | Абстракции сенсоров и их реализации |
| `src/ControlDevices/` | Ввод: клавиатура, Serial |
| `src/Utils/` | Утилиты (`Timer`) |

## GPIO пины

Определены в [src/ESP32_defines.h](src/ESP32_defines.h). Клавиатура на `GPIO32`.
