#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial BTserial(2,4);
LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 mfrc522(SS_PIN, RST_PIN);

#define SS_PIN 10
#define RST_PIN 9
byte i, letter;
String code = "";
String accessCard = "";
String clientCode = "";

const int lm35_pin = A1;
int temp_adc_val;
float temp_val;
float finalTemp = 0;

#define SOUT 3

const int trigPin = 5;
const int echoPin = 6;
long duration;
int distance;
float currentDistance = 0;

int ledPin = A0;
int sensorPin = 0;
double alpha = 0.75;
double change = 0.0;
double pulseResult = 0;


void bluetooth(String notif) {
    BTserial.write(notif);
}

int PIR() {
    int PIRresult = digitalRead(SOUT);    
    return PIRresult;
}

int USS() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration*(0.034/2);
    return distance;
}

String rfid() {
    if (!mfrc522.PICC_IsNewCardPresent()) {return;}
    if (!mfrc522.PICC_ReadCardSerial()) {return;}
    
    for (int i = 0; i<mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) {
            Serial.print(" 0");
        } else {
            Serial.print(" ");
        }

        Serial.print(mfrc522.uid.uidByte[i], HEX);

        code.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
        code.concat(String(mfrc522.uid.uidByte[i], HEX));

        code.toUpperCase();
        accessCard = code.substring(1);
    }
    
    return accessCard;
}

float lm35() {
    temp_adc_val = analogRead(lm35_pin);
    temp_val = (temp_adc_val * 4.88);
    temp_val = (temp_val/10);
    Serial.print("Temperature = ");
    Serial.print(temp_val);
    Serial.print(" Degree Celsius\n");
    return temp_val
}

double pulseMonitor() {
    static double oldValue = 0;
    static double oldChange = 0;
    int rawValue = analogRead(sensorPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;
    Serial.print(rawValue);
    Serial.print(",");
    Serial.println(value);
    oldValue = value;
    return value;
}



void setup() {
    pinMode(ledPin, OUTPUT);
    lcd.init();
    lcd.backlight();
}

void loop() {
    delay(5000);
    if (rfid() == clientCode) {
        while (1==1) {
            if (USS() < 20) {
                if (PIR() == 1) {
                    delay(2000);
                    pulseResult = pulseMonitor();
                }

                lcd.setCursor(2, 0);
                lcd.print("Put your finger by the temp sensor");
                delay(2000);
                finalTemp = lm35();
                delay(500);
                lcd.clear();

                bluetooth("Tempratue:", finalTemp,"......");
                bluetooth("Heart Beat:", pulseResult);

                lcd.setCursor(2, 0);
                lcd.setCursor(2, 0);
                lcd.print("Tempratue:", finalTemp);
                lcd.setCursor(2, 1);
                lcd.print("Heart Beat:", pulseResult);
                delay(10000);
                lcd.clear();
            }
        }
    }
}
