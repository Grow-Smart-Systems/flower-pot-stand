#pragma once

struct SensorsData
{
  float temperature {.0};
  float humidity {.0};
  uint16_t lux {0};
  uint8_t isDark {0};

  void reset() {
    temperature = 0.0;
    humidity = 0.0;
    lux = 0;
    isDark = 0;
  }

};