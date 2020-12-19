
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define BRAZIL_TIME -3 * 60 * 60 
#define NTP_POOL "pool.ntp.br"

#define COLUMS 16
#define ROWS 2

LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_POOL, BRAZIL_TIME );

void setup()
{
  Serial.begin(9600);

  WiFi.begin("ssid", "pass");

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();

  while (lcd.begin(COLUMS, ROWS, LCD_5x8DOTS, D2, D1) != 1)
  {
    Serial.println( "Error on display i2c connection" );
    delay(5000);
  }

}

void loop()
{
  timeClient.update();

  lcd.setCursor( 0,0 );

  lcd.print(timeClient.getFormattedTime());

  delay(1000);
}