#include <Arduino.h>
#include <Wire.h>

#define pinEncoder 19
int previousQuadrantNumber = 0;
int turns = 0;
int period = 200;
float time = 0;
unsigned long previousAngle = 0;
float rpm;

float readAngle(int pin) {
  unsigned long rawAngle = pulseIn(pin, HIGH);
  
  
  float angle = rawAngle*0.3515625;
  // Serial.println(angle);

  Serial.print("rawAngle: ");
  Serial.print(rawAngle);
  
  int quadrantNumber;

  //Quadrant 1
  if (angle >= 0 && angle <= 90)
  {
    quadrantNumber = 1;
  }

  //Quadrant 2
  if (angle > 90 && angle <= 180)
  {
    quadrantNumber = 2;
  }

  //Quadrant 3
  if (angle > 180 && angle <= 270)
  {
    quadrantNumber = 3;
  }

  //Quadrant 4
  if (angle > 270 && angle < 360)
  {
    quadrantNumber = 4;
  }

  if (quadrantNumber != previousQuadrantNumber) //if we changed quadrant
  {
    if (quadrantNumber == 1 && previousQuadrantNumber == 4)
    {
      turns++; // 4 --> 1 transition: CW rotation
    }

    if (quadrantNumber == 4 && previousQuadrantNumber == 1)
    {
      turns--; // 1 --> 4 transition: CCW rotation
    }
    //this could be done between every quadrants so one can count every 1/4th of transition

    previousQuadrantNumber = quadrantNumber;  //update to the current quadrant

  }

  return (turns*360)+angle;
}


int count = 0;
void contador(){
  count++;
}

void setup() {
  Serial.begin(112500);

  // pinMode(pinEncoder, INPUT);
  attachInterrupt(pinEncoder, contador, RISING);
}

void loop() {
  // float angle = readAngle(pinEncoder);
  // Serial.print(" | angle: ");
  // Serial.println(angle);
  // delay(500);
  // Serial.println(angle);
  

    
    // float velocidadeAngular = (previousAngle-angle)/period;

    // previousAngle = angle;

    // rpm = velocidadeAngular * 0.166667;

    // time = millis();
    // Serial.print("Ang: ");
    // Serial.print(angle);
    // Serial.println(" | ");
    // Serial.print("RPM: ");
    // Serial.println(rpm);
    Serial.println(count);
    delay(100);
  
}
