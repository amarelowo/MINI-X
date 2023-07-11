#include <Arduino.h>
#include <Wire.h>

#include <AS5040.h>

// CHANGE THESE AS APPROPRIATE
#define CSpin   5
#define CLKpin  18
#define DOpin   27
#define PROGpin 19

// OUTPUT PINS
#define enc_a  6
#define enc_b  7
#define enc_z  8


AS5040 enc (CLKpin, CSpin, DOpin, PROGpin) ;

// Set mode to quadrature (A + B + index), monitor via serial IF
void setup ()
{
  Serial.begin (115200) ;   // NOTE BAUD RATE
  if (!enc.begin (AS5040_QUADRATURE, false, 0))  // example setting reverse sense and an offset
    Serial.println ("Error setting up AS5040") ;
}

void loop ()
{
  // Serial.print (enc.read (), HEX) ;
  // Serial.print ("   ") ;
  // Serial.print (enc.status (), BIN) ;
  // Serial.print ("   ") ;
  // Serial.print (enc.valid () ? "OK" : "Fault") ;
  // Serial.print ("   ") ;
  // Serial.println (enc.Zaxis ()) ;
  // delay (400) ;
}
