#include <LedControl.h>
int DIN = 10, CS = 9, CLK = 8, y = 0, x = 0;
byte heart[8][8] = {
  {0,0,0,0,0,0,0,0},
  {0,1,1,0,0,1,1,0},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {1,1,1,1,1,1,1,1},
  {0,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,0,0},
  {0,0,0,1,1,0,0,0}};

LedControl lc = LedControl(DIN, CLK, CS, 15);
void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,15);
  lc.clearDisplay(0);
}

void loop() {
  for (y=0; y<8; y++) {
    for (x=7; x>=0; x--) {
      lc.setLed(0,y,x,heart[y][x]);
      if (heart[y][x]==1){
        delay();
      }
      }
      x=0;
    }
    delay(1000);
    lc.clearDisplay(0);
}
