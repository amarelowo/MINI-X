#include <Arduino.h>
#include <AS5040.h>
#include <ESP32Servo.h>

// CHANGE THESE AS APPROPRIATE
#define CSpin   5
#define CLKpin  18
#define DOpin   19
#define PROGpin 2

// OUTPUT PINS
#define enc_a  14
#define enc_b  35
#define enc_z  8

// Motor pins
#define pinPot 25
#define pinEsc 33


Servo esc;
AS5040 enc (CLKpin, CSpin, DOpin, PROGpin) ;

unsigned long count = 0;

void contador(){
  count++;
}

// Set mode to quadrature (A + B + index), monitor via serial IF
void setup ()
{
  Serial.begin (115200) ;   // NOTE BAUD RATE
  if (!enc.begin (AS5040_QUADRATURE, false, 0))  // example setting reverse sense and an offset
    Serial.println ("Error setting up AS5040");

  esc.attach(pinEsc); 
  esc.writeMicroseconds(1500);
  attachInterrupt(enc_a, contador, RISING);   
}

void loop (){
    int val; 

    val= analogRead(pinPot);
    // Serial.print(val);
    // Serial.print(" | ");

    val= map(val, 0, 4096,1000,2000); 
    Serial.println(count);

    esc.writeMicroseconds(val);   
    // Serial.print (enc.read (), HEX) ;
    // Serial.print ("   ") ;
    // Serial.print (enc.status (), BIN) ;
    // Serial.print ("   ") ;
    // Serial.print (enc.valid () ? "OK" : "Fault") ;
    // Serial.print ("   ") ;
    // Serial.println (enc.Zaxis ()) ;
    delay (400) ;
}
