#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RS_PIN 9
byte i, letter;
char code = "";

char accessCard = "";
char clientCode = "D6 58 08 F8"; //change
MFRC522 mfrcs522(SS_PIN, RST_PIN);

char rfid() {
    if (!mfrcc522.PICC_IsNewCardPresent()) {return;}
    if (!mfrc522.ReadCardSerial()) {return;}
    
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
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_init();
}

void loop() {
    accessCard = rfid();
    Serial.print(accessCard);
    delay(10000)
}
