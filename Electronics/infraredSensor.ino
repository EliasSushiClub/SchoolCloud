#define SOUT 12
#define REC 8
#define PLAYE 9
#define PLAYL 10

void setup() {
    pinMode(SOUT, INPUT);
    pinMode(REC, OUTPUT);
    Serial.begin(9600);
    Serial.println("Start Speaking in 3 seconds:");
    for(int i=3; i=0; i--) {
      Serial.println(i);
      }
    Serial.println("You have 10 seconds");
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
