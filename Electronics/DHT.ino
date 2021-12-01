#include <dht.h>
#include <LiquidCrystal_I2C.h>

dht DHT;
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHT11_PIN 2

void setup(){
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop(){
    int chk = DHT.read11(DHT11_PIN);
    lcd.setCursor(2, 0);
    lcd.print("Temperature = ");
    lcd.print(DHT.temperature);
    lcd.setCursor(2, 1);
    lcd.print("Humidity = ");
    lcd.print(DHT.humidity);
    lcd.clear();
    delay(1000);
}
