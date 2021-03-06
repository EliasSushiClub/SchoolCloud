#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <LedControl.h>

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
double alpha = 0.75;
int period = 20;
double pulseResult = 0;

int DIN = 6, CS = 5, CLK = 1, y = 0, x = 0;
byte heart[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,1,1,0},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,1,1,0,0,0}};

byte badToken[8][8] = {
  {1,0,0,0,0,0,0,1},
  {0,1,0,0,0,0,1,0},
  {0,0,1,0,0,1,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,0,1,1,0,0,0},
  {0,0,1,0,0,1,0,0},
  {0,1,0,0,0,0,1,0},
  {1,0,0,0,0,0,0,1}};


void heartControl() {
    for (y=0; y<8; y++) {
    for (x=7; x>=0; x--) {
      lc.setLed(0,y,x,heart[y][x]);
      if (heart[y][x]==1){
        delay(150);
      }
      }
      x=0;
    }
    delay(5000);
    lc.clearDisplay(0);
}

void errorControl() {
    for (y=0; y<8; y++) {
    for (x=7; x>=0; x--) {
      lc.setLed(0,y,x,badToken[y][x]);
      if (badToken[y][x]==1){
        delay(100);
      }
      }
      x=0;
    }
    delay(2000);
    lc.clearDisplay(0);
}

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
    int rawValue = analogRead(ledPin);
    double value = alpha * oldValue + (1 - alpha) * rawValue;
    Serial.print(rawValue);
    Serial.print(",");
    Serial.println(value);
    oldValue = value;
    delay(period*10);
}


void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    lcd.init();
    lcd.backlight();
    lc.shutdown(0,false);
    lc.setIntensity(0,15);
    lc.clearDisplay(0);
}

void loop() {
    delay(5000);
    if (rfid() == clientCode) {
        while (1==1) {
            if (USS() < 20) {
                if (PIR() == 1) {
                    delay(2000);
                    pulseResult = pulseMonitor();
                    heartControl();
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
  
    else {
        lcd.setCursor(2, 0);
        lcd.print("You don't have authorized access to this device");
        errorControl();
        delay(2000);
        lcd.clear();
    }
}
