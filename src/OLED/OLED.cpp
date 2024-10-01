#include "OLED.h"

OLED::OLED()
  : _u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE)
{
}

bool OLED::init()
{
  if(!_u8g2.begin())
    return false;
  
  _u8g2.setPowerSave(0);
  _u8g2.setFont(u8g_font_6x10);
  _u8g2.setFontRefHeightExtendedText();
  _u8g2.setFontPosTop();
  return true;
}

void OLED::printInitializeScreen()
{
  _u8g2.firstPage();
  do  
  {
    //NOTE: Без setFont не работает!
    _u8g2.setColorIndex(1);
    _u8g2.setFont(u8g_font_6x13);
    _u8g2.drawStr(40, DEBUG_TEXT_STRING_3, "LOADING...");
  } 
  while( _u8g2.nextPage() );
}

void OLED::printAllData(const SensorsData &data)
{
  // picture loop  
  _u8g2.firstPage();  
  do 
  {
    String temperatureStr = "Temp:  " + (isnan(data.temperature)? "nan" : String(data.temperature)) + " C";
    String humidityStr = "Hum:   " + (isnan(data.humidity)? "nan" : String(data.humidity)) + " %";
    String luxStr = "Lux:   " + String(data.lux) + " lx";
    String darkStr = "Is dark: " + String(data.isDark? "+" : "-");

    _u8g2.setFont(DEBUG_TEXT_FONT);
    _u8g2.drawStr(0, DEBUG_TEXT_STRING_0, temperatureStr.c_str());
    _u8g2.drawStr(0, DEBUG_TEXT_STRING_1, humidityStr.c_str());
    _u8g2.drawStr(0, DEBUG_TEXT_STRING_2, luxStr.c_str());
    _u8g2.drawStr(0, DEBUG_TEXT_STRING_3, darkStr.c_str());
  } 
  while( _u8g2.nextPage() );
}
