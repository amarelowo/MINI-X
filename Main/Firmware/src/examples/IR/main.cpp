#include <Arduino.h>
#include "IRremote.h"

#define ONE 0
#define TWO 1
#define TREE 3
#define POWER 21

#define print Serial.print

int last_button_pressed = 300; 
int button_pressed = 300;

void setup() {
  Serial.begin(112500);
  IrReceiver.begin(34);
}
void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    button_pressed = IrReceiver.decodedIRData.command;
  }

  if(button_pressed != last_button_pressed){
    Serial.println(button_pressed);
  }

  switch (button_pressed)
  {
  case ONE :
   Serial.println("--> 1");
    break;
  case TWO :
     Serial.println("--> 2");
    break;
  case TREE :
    Serial.println("--> 3");
    break;

  case POWER :
    Serial.println("--> PWR");
    break;
  }
  last_button_pressed = button_pressed;
  button_pressed = 300;
  //  Serial.println(button_pressed);
}