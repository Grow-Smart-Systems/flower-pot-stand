#include <DHT.h>
#include "OLED.h"
//#include <U8glib.h>

/// ===== define ===== //
// ARDUINO LED
#define PIN_LED 13
// Temp'n'hum sensor
#define DHTPIN 2
#define DHTTYPE DHT11
// Lux sensor
#define PIN_ANALOG_PHOTO_SENSOR A0
#define PIN_DIGITAL_PHOTO_SENSOR A1
/// ===== globals ===== //

DHT dht(DHTPIN, DHTTYPE);

OLED _screen;

SensorsData _data;

//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);	// I2C / TWI 


// ===== functions ===== //

void setup(void) 
{
  Serial.begin(9600);
  Serial.println(F("Start!"));

  // OLED
  _screen.printInitializeScreen();

  dht.begin();

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_ANALOG_PHOTO_SENSOR, INPUT);          // Установим вывод A0 как вход
  pinMode(PIN_DIGITAL_PHOTO_SENSOR, INPUT);          // Установим вывод A1 как вход

  delay(2000);
}

void loop(void) 
{
  // Обновим данные от сенсоров
  _data.lux = analogRead (PIN_ANALOG_PHOTO_SENSOR);
  _data.isDark = digitalRead(PIN_DIGITAL_PHOTO_SENSOR);
  _data.temperature = dht.readTemperature();
  _data.humidity = dht.readHumidity();

  // picture loop  
  _screen.printAllData(_data);
  
  // rebuild the picture after some delay
  delay(2000);
}


