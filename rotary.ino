#include "HID-Project.h"

#define PIN_CLK 2
#define PIN_DATA 3
#define PIN_SW 7

volatile int rotary = 0;

void swChange() {
  Serial.println("SW");
  Consumer.write(MEDIA_PLAY_PAUSE);
}

void clkChange() {
  bool clk = digitalRead(PIN_CLK);
  bool data = digitalRead(PIN_DATA);
  
  if(data != clk) {
    rotary += 1;
  }else{
    rotary -= 1;
  }

  Serial.println(rotary);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_DATA, INPUT);
  pinMode(PIN_SW, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PIN_CLK), clkChange, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_SW), swChange, FALLING);

  Consumer.begin();
}

int oldrot = 0;
void loop() {
  if(rotary != oldrot) {

    if(rotary > oldrot) {
      Consumer.write(MEDIA_VOLUME_UP);
      Consumer.write(MEDIA_VOLUME_UP);
    }
    if(rotary < oldrot) {
      Consumer.write(MEDIA_VOLUME_DOWN);
      Consumer.write(MEDIA_VOLUME_DOWN);
    }
    
    oldrot = rotary;
  }
}
