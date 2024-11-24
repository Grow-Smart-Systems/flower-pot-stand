#include "OLED.h"


OLED::OLED()
    : _display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{
}

bool OLED::init()
{
    if (!_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        return false;
    }
    _display.clearDisplay();
    return true;
}

void OLED::printInitializeScreen()
{
    _display.clearDisplay();
    _display.setTextSize(2); // Normal 1:1 pixel scale
    _display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    _display.setCursor(0, 0); // Start at top-left corner
    _display.println(F("LOADING..."));
    _display.display();
}

void OLED::printAllData(const SensorsData& data)
{
    String temperatureStr = "Temp:  " + String(data.temperature) + " C";
    String humidityStr = "Hum:   " + String(data.humidity) + " %";
    String luxStr = "Lux:   " + String(data.lux) + " lx";


    Serial.println(temperatureStr);
    Serial.println(humidityStr);
    Serial.println(luxStr);


    _display.clearDisplay();
    _display.setTextSize(1);             // Normal 1:1 pixel scale
    _display.setTextColor(SSD1306_WHITE);        // Draw white text
    _display.setCursor(0, 0);             // Start at top-left corner

    _display.println(temperatureStr);
    _display.println(humidityStr);
    _display.println(luxStr);

    _display.display();
}
