#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

SoftwareSerial BTserial(2,4);

#define SS_PIN 10
#define RST_PIN 9
byte i, letter;
String code = "";

#define SOUT 3
const int trigPin = 5;
const int echoPin = 6;
long duration;
int distance;
int vibPin = 7;
float ultrasonic = 0;
float currentDistance = 0;
String systemState = "";
String accessCard = "";
String clientHash = "f6663cd2cba3a6e960e5522866e721c2";
MFRC522 mfrc522(SS_PIN, RST_PIN);

void bluetooth(String notif) {
    BTserial.write(notif);
}

int vibrationSensor() {
    int result = digitalRead(vib_pin);
    return result;
}

int pirSensor() {
    int PIRresult = digitalRead(SOUT);    
    return PIRresult;
}

int ultrasonicSensor() {
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

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(SOUT, INPUT);
    pinMode(vibPin, INPUT);
    BTserial.begin(9600);
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
}

void loop() {
    delay(5000);
    accessCard = rfid();
    if (md5Hash(accessCard) == clientHash) {
        delay(10000)
        while (1==1) {
            
            if (pirSensor() == 1) {
                ultrasonic = ultrasonicSensor();
                while (ultrasonicSensor() != 0) {
                    currentDistance = ultrasonicSensor();
                    if (currentDistance < ultrasonic) {
                        BTserial.write("OBJECT APPROACHING THE DOOR:", currentDistance);
                    }
                    
                    else {
                        BTserial.write("NON THREATENING OBJECT SPOTTED");
                    }
                    
                    ultraSonic = currentDistance();
                }
            }

            if (vibrationSensor() == 1) {
                bluetooth("INTRUDER ALERT!");
            }

            if (mfrcc522.PICC_IsNewCardPresent()) || BTserial.available() {
                accessCard = rfid();
                systemState = BTserial.read();
                systemState = systemState.toUpperCase();
                if ((md5Hash(accessCard) == clientHash) || systemState == "TURN OFF") {
                    break;
                }
            }

            delay(1000);
        }
    }

    else {
        delay(5000)
    }
}
