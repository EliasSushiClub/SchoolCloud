#include <LiquidCrystal_I2C.h>
#include <UltraDistSensor.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
UltraDistSensor mainSensor;
float reading;

void setup() {
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    mainSensor.attach(12, 13);
    pinMode(2, OUTPUT); //BUZZER
    pinMode(3, OUTPUT); //GREEN
    pinMode(4, OUTPUT); //YELLOW
    pinMode(5, OUTPUT); //RED
}

void loop() {
    reading = mainSensor.distanceInCm();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(reading);

    if (reading < 50 && reading > 0) {
        digitalWrite(3, HIGH);
        tone(2, 10000);
        delay(5000);
        digitalWrite(3, LOW);
        noTone(2);
    }

    else if (reading > 50 && reading < 100) {
        digitalWrite(4, HIGH);
        tone(2, 15000);
        delay(5000);
        digitalWrite(4, LOW);
        noTone(2);
    }

    else if (reading > 100 && reading < 150) {
        digitalWrite(5, HIGH);
        tone(2, 20000);
        delay(5000);
        digitalWrite(5, LOW);
        noTone(2);
    }
}
