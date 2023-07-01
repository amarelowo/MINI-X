#include <Arduino.h>
#include "motor_brushles.h"
#include "mpu.h"
#include "led_rgb.h"

#include "config.h"

int pinPot = 25;

bool imu_connect; 
bool connect = false;


// init motor -> goes from -100% 2 + 100% 
motor_brushless left_motor(MOTOR_LEFT_PIN);
motor_brushless right_motor(MOTOR_RIGH_PIN);

led_rgb LED ;

void setup() {
    LED.init();
    LED.latch(100,AZUL);

    pinMode(2,OUTPUT);

    left_motor.init();
    right_motor.init();
   
    imu_connect = imu_setup();


  if(imu_connect == 0) {
   
    digitalWrite(2, HIGH); 
  }

    //debug potenciometer
    pinMode(pinPot,INPUT);

    Serial.begin(112500);

    delay(500);

    LED.latch(100,AZUL);

}

void loop() {

    int val; 
    int speed; 

    val= analogRead(pinPot);

    float* imu_ypr = imu_get_ypr(); 

    speed = map(val, 0, 4096,-100,100); 




    Serial.print(" motor: ");
    Serial.print(speed);
    Serial.print("pot: ");
    Serial.print(val); 
    Serial.print(" |IMU  Y :");
    Serial.print(imu_ypr[0]);
    Serial.print(" P : ");
    Serial.print(imu_ypr[1]);
    Serial.print(" R : ");
    Serial.print(imu_ypr[2]);

    Serial.println("");




    left_motor.write(speed);
    right_motor.write(speed);
}