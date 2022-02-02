#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
byte i, letter;
String code = "";

#define SOUT 3
const int trigPin = 4;
const int echoPin = 5;
long duration;
int distance;
int vibPin = 7;
String accessCard = "";
String clientCode = "69 DE 28 A469 DE 28 A4";
MFRC522 mfrc522(SS_PIN, RST_PIN);

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
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
}

void loop() {
    delay(5000);
    accessCard = rfid();
    if (accessCard == clientCode) {
        delay(10000)
        while (1==1) {
            int pir = pirSensor();
            int vibSensor = vibrationSensor();
            
            if (pir == 1) {
            int ultrasonic = ultrasonicSensor();
            }

            if (vibSensor == 1) {
                //send bluetooth
            }

            if (mfrcc522.PICC_IsNewCardPresent()) {
                accessCard = rfid();
                if (accessCard == clientCode) {
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