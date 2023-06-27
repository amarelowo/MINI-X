#include <Arduino.h>
#include "motor_brushles.h"
#include "config.h"

int pinPot = 25;


// init motor -> goes from -100% 2 + 100% 
motor_brushless left_motor(MOTOR_LEFT_PIN);
motor_brushless right_motor(MOTOR_RIGH_PIN);

void setup() {

    left_motor.init();
    right_motor.init();

    //debug potenciometer
    pinMode(pinPot,INPUT);

    Serial.begin(112500);
}

void loop() {
int val; 
int speed; 
    val= analogRead(pinPot);
    Serial.print("pot: ");
    Serial.print(val); 
    speed = map(val, 0, 4096,-100,100); 
    Serial.print(" motor: ");
    Serial.println(speed);
    left_motor.write(speed);
    right_motor.write(speed);
}