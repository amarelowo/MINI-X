#include <Arduino.h>
#include <Wire.h>
#include <AS5600.h>

AS5600 as5600;
#define DIRECTION_PIN 25

void setup() {
  Serial.begin(9600);

  delay(3000);

  Wire.begin();

  // inicia a comunicação definindo o pino DIR do encoder
  // Pino que estabele a direção positiva 
  as5600.begin(DIRECTION_PIN);
  as5600.setDirection(AS5600_CLOCK_WISE);

  Serial.println(as5600.getAddress());

  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);
  delay(1000);
}

void loop() {
  Serial.print("Angulo somado: ");
  Serial.print(as5600.getCumulativePosition());
  Serial.print("Revolucoes: ");
  Serial.print(as5600.getRevolutions());
  Serial.print("\tVel = ");
  // usar no .getAngularSpeed()
  //  getAngularSpeed
  //  AS5600_MODE_DEGREES       = 0;
  //  AS5600_MODE_RADIANS       = 1;
  //  AS5600_MODE_RPM           = 2;
  Serial.println(as5600.getAngularSpeed(AS5600_MODE_DEGREES));

}




// TESTES SEM O USO DA BIBLIOTECA
/*
int magnetStatus = 0;
int previousquadrantNumber = 0;
int numeroVoltas = 0;

void chackMagnetPresence(){
  while((magnetStatus & 32) != 32){
    magnetStatus = 0;

    Wire.beginTransmission(0x36);
    Wire.write(0x0B);
    Wire.endTransmission();
    Wire.requestFrom(0x36, 1);
    
    while(Wire.available() == 0);

    magnetStatus = Wire.read();

    Serial.print("Magnet status: ");
    Serial.println(magnetStatus);
  }
}

float readRawAngle(){
  float degAngle;
  int rawAngle;
  int lowbyte;
  word highbyte;
  //7:0 - bits
  Wire.beginTransmission(0x36); //connect to the sensor
  Wire.write(0x0D); //figure 21 - register map: Raw angle (7:0)
  Wire.endTransmission(); //end transmission
  Wire.requestFrom(0x36, 1); //request from the sensor
  
  while(Wire.available() == 0); //wait until it becomes available 
  lowbyte = Wire.read(); //Reading the data after the request
 
  //11:8 - 4 bits
  Wire.beginTransmission(0x36);
  Wire.write(0x0C); //figure 21 - register map: Raw angle (11:8)
  Wire.endTransmission();
  Wire.requestFrom(0x36, 1);
  
  while(Wire.available() == 0);  
  highbyte = Wire.read();
  
  //4 bits have to be shifted to its proper place as we want to build a 12-bit number
  highbyte = highbyte << 8; //shifting to left
  //What is happening here is the following: The variable is being shifted by 8 bits to the left:
  //Initial value: 00000000|00001111 (word = 16 bits or 2 bytes)
  //Left shifting by eight bits: 00001111|00000000 so, the high byte is filled in
  
  //Finally, we combine (bitwise OR) the two numbers:
  //High: 00001111|00000000
  //Low:  00000000|00001111
  //      -----------------
  //H|L:  00001111|00001111
  rawAngle = highbyte | lowbyte; //int is 16 bits (as well as the word)

  //We need to calculate the angle:
  //12 bit -> 4096 different levels: 360° is divided into 4096 equal parts:
  //360/4096 = 0.087890625
  //Multiply the output of the encoder with 0.087890625
  degAngle = rawAngle * 0.087890625;
  return degAngle; 
}

float somaAngulo(float rawAngle){
  int quadrantNumber;

  // 
  // Quadrants:
  // 4  |  1
  // ---|---
  // 3  |  2

 if(rawAngle >= 0 && rawAngle <=90){
  quadrantNumber = 1;
 }
 if(rawAngle > 90 && rawAngle <=180){
  quadrantNumber = 2;
 }
 if(rawAngle > 180 && rawAngle <=270){
  quadrantNumber = 3;
 }
 if(rawAngle > 270 && rawAngle <360){
  quadrantNumber = 4;
 }
  
  if(quadrantNumber != previousquadrantNumber){
    if(quadrantNumber == 1 && previousquadrantNumber == 4){
      numeroVoltas++; // 4 --> 1 transition: CW rotation
      if(numeroVoltas>3){
        numeroVoltas = 3;
      }
    }
    if(quadrantNumber == 4 && previousquadrantNumber == 1){
      numeroVoltas--; // 1 --> 4 transition: CCW rotation
      if(numeroVoltas<=0){
        numeroVoltas = 0;
      }
    }
    previousquadrantNumber = quadrantNumber;
  }
  float totalAngle = (numeroVoltas*360)+rawAngle;
  return totalAngle;
}
*/