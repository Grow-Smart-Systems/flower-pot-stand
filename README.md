# flower-pot-stand

![CI](https://github.com/YOUR_USERNAME/flower-pot-stand/workflows/CI/badge.svg)

ESP32-based plant monitoring system with OLED display, sensors, and menu navigation.

## Features

- SSD1306 OLED display (128x64)
- DHT11 temperature/humidity sensor
- LM393 light sensor
- Menu navigation via analog keyboard
- Real-time sensor monitoring

## Build & Test

```bash
# Build firmware
pio run -e release

# Upload to ESP32
pio run -t upload

# Run unit tests (Linux/macOS)
pio test -e native

# Run unit tests (Windows)
pio test -e windows_x86

# Serial monitor
pio device monitor
```

## CI/CD

Automated testing and builds via GitHub Actions:
- ✅ Unit tests (Menu, Timer)
- ✅ ESP32 firmware build (release/debug)
- ✅ Code quality checks

See [CI.md](CI.md) for details.

## Project Structure

- `src/` — Source code (ESP32)
- `test/` — Unit tests (Menu, Timer)
- `.github/workflows/` — CI configuration

## Documentation

- [CI.md](CI.md) — CI/CD setup and usage
