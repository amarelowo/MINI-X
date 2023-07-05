// #include <Arduino.h>
#include <Wire.h>

// #define pinEncoder 19
// int previousQuadrantNumber = 0;
// int turns = 0;
// int period = 200;
// float time = 0;
// unsigned long previousAngle = 0;
// float rpm;

// float readAngle(int pin) {
//   unsigned long rawAngle = pulseIn(pin, HIGH);
  
  
//   float angle = rawAngle*0.3515625;
//   // Serial.println(angle);

//   Serial.print("rawAngle: ");
//   Serial.print(rawAngle);
  
//   int quadrantNumber;

//   //Quadrant 1
//   if (angle >= 0 && angle <= 90)
//   {
//     quadrantNumber = 1;
//   }

//   //Quadrant 2
//   if (angle > 90 && angle <= 180)
//   {
//     quadrantNumber = 2;
//   }

//   //Quadrant 3
//   if (angle > 180 && angle <= 270)
//   {
//     quadrantNumber = 3;
//   }

//   //Quadrant 4
//   if (angle > 270 && angle < 360)
//   {
//     quadrantNumber = 4;
//   }

//   if (quadrantNumber != previousQuadrantNumber) //if we changed quadrant
//   {
//     if (quadrantNumber == 1 && previousQuadrantNumber == 4)
//     {
//       turns++; // 4 --> 1 transition: CW rotation
//     }

//     if (quadrantNumber == 4 && previousQuadrantNumber == 1)
//     {
//       turns--; // 1 --> 4 transition: CCW rotation
//     }
//     //this could be done between every quadrants so one can count every 1/4th of transition

//     previousQuadrantNumber = quadrantNumber;  //update to the current quadrant

//   }

//   return (turns*360)+angle;
// }


// int count = 0;
// void IRAM_ATTR contador(){
//   count++;
// }

// void setup() {
//   Serial.begin(112500);

//   pinMode(pinEncoder, INPUT);
//   attachInterrupt(pinEncoder, contador, RISING);
// }

// void loop() {
//   // float angle = readAngle(pinEncoder);
//   // Serial.print(" | angle: ");
//   // Serial.println(angle);
//   // delay(500);
//   // Serial.println(angle);
  

    
//     // float velocidadeAngular = (previousAngle-angle)/period;

//     // previousAngle = angle;

//     // rpm = velocidadeAngular * 0.166667;

//     // time = millis();
//     // Serial.print("Ang: ");
//     // Serial.print(angle);
//     // Serial.println(" | ");
//     // Serial.print("RPM: ");
//     // Serial.println(rpm);
//     Serial.println(count);
//     delay(100);
  
// }
#include <Arduino.h>
#include <AS5040.h>

// CHANGE THESE AS APPROPRIATE
#define CSpin   5
#define CLKpin  18
#define DOpin   19
#define PROGpin 2

// OUTPUT PINS
#define enc_a  6
#define enc_b  7
#define enc_z  8


AS5040 enc (CLKpin, CSpin, DOpin, PROGpin) ;

// Set mode to quadrature (A + B + index), monitor via serial IF
void setup ()
{
  Serial.begin (115200) ;   // NOTE BAUD RATE
  if (!enc.begin (AS5040_QUADRATURE, true, 0x200))  // example setting reverse sense and an offset
    Serial.println ("Error setting up AS5040") ;
}

void loop ()
{
  Serial.print (enc.read (), HEX) ;
  Serial.print ("   ") ;
  Serial.print (enc.status (), BIN) ;
  Serial.print ("   ") ;
  Serial.print (enc.valid () ? "OK" : "Fault") ;
  Serial.print ("   ") ;
  Serial.println (enc.Zaxis ()) ;
  delay (400) ;
}
