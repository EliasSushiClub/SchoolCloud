#define SOUT 12
//#define REC 8
#define PLAYE 9
#define PLAYL 10

void setup() {
    pinMode(SOUT, INPUT);
    Serial.begin(9600);
}

void loop() {
    //delay(10000);
    int ret = digitalRead(SOUT);
    if (ret == 1) {
        Serial.println("Danger Detected :(");
        digitalWrite(PLAYE, 1);
        delay(3000);
        digitalWrite(PLAYE, 0);
    }
}


////////

#define SOUT 12
#define REC 8
#define PLAYE 9
#define PLAYL 10

void setup() {
    pinMode(SOUT, INPUT);
    Serial.begin(9600);
    Serial.println("Start Speaking in 3 seconds:");
    digitalWrite(REC, 1);
    delay(10000);
    digitalWrite(REC, 0);
}

void loop() {
    int ret = digitalRead(SOUT);
    if (ret == 1) {
        Serial.println("Danger Detected :(");
        digitalWrite(PLAYE, 1);
        delay(10000);
        digitalWrite(PLAYE, 0);
    }
}
