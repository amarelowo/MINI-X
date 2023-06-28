
#include "mpu.h"


bool _imu_connect; 
bool _connect = false;



// ----------- ultrasonic sensor - distance

void setup(){

  Serial.begin(9600);

  // check that the IMU initializes correctly
  _imu_connect = imu_setup();

  if(_imu_connect == 0) {
   
    digitalWrite(2, HIGH); 
  }
}


void loop(){



  float* imu_orientation = orientation(); 
  float* imu_ypr = imu_get_ypr();
  float* imu_angularVelocity = angular_velocity(); 
  float* imu_linaerAcceleration = linear_acceleration();
  float* imu_orientationCovariance = orientation_covariance();
  float* imu_linaerAccelerationCovariance = linear_acceleration_covariance(); 
  float* imu_angularVelocityCovariance = angular_velocity_covariance(); 
  
  Serial.print("Orientation ");
  Serial.print(imu_orientation[0]);
  Serial.print(",");
  Serial.print(imu_orientation[1]);
  Serial.print(",  ");
  Serial.print(imu_orientation[2]);
  Serial.print(", ");
  Serial.print(imu_orientation[3]);
  Serial.println("");
  
}   