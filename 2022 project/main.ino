#define SOUT 12
const int trigPin = 11;
const int echoPin = 12;
int vibPin=7;
long duration;
int distance;
char accessCard = "";

int vibrationSensor() {
    int result = digitalRead(vib_pin);
    return result
}

int pirSensor() {
    int PIRresult = digitalRead(SOUT);    
    return PIRresult
}

int ultrasonicSensor() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration*(0.034/2);
    return distance
}

char rfid() {
    //add RFID code and save card contents in var accessCard
    return accessCard
}

void setup() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(SOUT, INPUT);
    pinMode(vibPin, INPUT);
    Serial.begin(9600)
}

void loop() {
    accessCard = rfid();
    if (accessCard = content.substring(1)) {
        while (1==1) {
            int pir = pirSensor();
            int vibSensor = vibrationSensor();
            
            if (pir == 1) {
            int ultrasonic = ultrasonicSensor();
            }

            if (vibSensor == 1) {
                //send bluetooth
            }

            delay(1000);
        }
    }

    else {
        delay(10000)
    }
}