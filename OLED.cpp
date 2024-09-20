#include <Arduino.h>
#include "OLED.h"

OLED::OLED()
{
    u8g = U8GLIB_SSD1306_128X64(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 
}

void OLED::printInitializeScreen()
{
  _u8g.firstPage();
  do  
  {
    //NOTE: Без setFont не работает!
    _u8g.setFont(u8g_font_6x13);
    _u8g.drawStr(40, TEXT_STRING_3, "LOADING...");
  } 
  while( _u8g.nextPage() );
}

void OLED::printAllData(const SensorsData &data)
{
  // picture loop  
  _u8g.firstPage();  
  do 
  {
    String temperatureStr = "Temp:  " + (isnan(data.temperature)? "nan" : String(data.temperature)) + " C";
    String humidityStr = "Hum:   " + (isnan(data.humidity)? "nan" : String(data.humidity)) + " %";
    String luxStr = "Lux:   " + String(data.lux) + " lx";
    String darkStr = "Is dark: " + String(data.isDark? "+" : "-");

    _u8g.setFont(u8g_font_6x10);
    _u8g.drawStr(0, TEXT_STRING_0, temperatureStr.c_str());
    _u8g.drawStr(0, TEXT_STRING_1, humidityStr.c_str());
    _u8g.drawStr(0, TEXT_STRING_2, luxStr.c_str());
    _u8g.drawStr(0, TEXT_STRING_3, darkStr.c_str());
  } 
  while( _u8g.nextPage() );
}
