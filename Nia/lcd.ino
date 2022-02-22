#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
}

void loop() {
  // set cursor
    lcd.setCursor(2, 0);
  // print
    lcd.print("");
  // clear
    lcd.clear();
}
