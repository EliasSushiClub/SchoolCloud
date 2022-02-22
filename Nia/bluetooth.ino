#include <SoftwareSerial.h>
#define LED1  13
#define LED2  3
int i,val = 0;
SoftwareSerial BT(4, 2); // RX, TX
void setup() {
  BT.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
}

void loop() {
  
  if (BT.available() > 0)
  {
    val = BT.read();
    if (val == 'r')
    {
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      BT.print("*t led is on");
      int i=90; 
      BT.print("*D" +String(i)+ "*");
    }
    if (val == 'R')
    {
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      BT.print("*t led is off");
     int i=30;
     BT.print("*D" +String(i)+ "*");
    }
    
  }

}
