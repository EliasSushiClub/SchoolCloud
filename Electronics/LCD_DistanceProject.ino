#include <LiquidCrystal_I2C.h>

const int trigPin = 11;
const int echoPin = 12;

long duration;
int distance;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.init();
    lcd.backlight();
    pinMode(2, OUTPUT); //BUZZER
    pinMode(3, OUTPUT); //GREEN
    pinMode(4, OUTPUT); //YELLOW
    pinMode(5, OUTPUT); //RED
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration*(0.034/2);
    
    lcd.setCursor(2, 0);
    lcd.print("Distance: ");
    lcd.print(distance);

    if (distance < 50 && distance > 0) {
        digitalWrite(3, HIGH);
        tone(2, 262);
        delay(2000);
        digitalWrite(3, LOW);
        noTone(2);
    }

    else if (distance > 50 && distance < 100) {
        digitalWrite(4, HIGH);
        tone(2, 294);
        delay(2000);
        digitalWrite(4, LOW);
        noTone(2);
    }

    else if (distance > 100 && distance < 150) {
        digitalWrite(5, HIGH);
        tone(2, 330);
        delay(2000);
        digitalWrite(5, LOW);
        noTone(2);
    }
    delayMicroseconds(1000);
    lcd.clear();
}
