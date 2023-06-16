#include <Arduino.h>


int POT = 25;
int SIGNAL = 33;
int pot_reading = 0; 

void debug(int pot){

Serial.print("pot: ");
Serial.print(pot);
Serial.println("");

}

void setup() 
{
    Serial.begin(112500); 

    //pot  0 - 4095
    pinMode(POT,INPUT);
}

void loop() 
{   
    pot_reading = analogRead(POT);
    debug(pot_reading);
}
