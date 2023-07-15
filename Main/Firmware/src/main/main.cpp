#include <Arduino.h>
#include "motor_brushles.h"
#include "mpu.h"
#include "led_rgb.h"
#include "controle_juiz.h"
#include "refletancia.h"
#include <VL53L0X.h>

#include "config.h"

int pinPot = 25;

bool imu_connect; 
bool connect = false;

int led_color = VERMELHO;
// init motor -> goes from -100% 2 + 100% 
motor_brushless left_motor(MOTOR_LEFT_PIN);
motor_brushless right_motor(MOTOR_RIGH_PIN);

led_rgb LED ;

controle_juiz controle_sony(CR_PIN);

refletancia rft_front(RFT_FRONT_PIN,700);
refletancia rft_back(RFT_BACK_PIN,700);

// Def funcoes VL's
void vl_init();
void distanceRead();
void printDistances();

//Cria os objetos para cada sensor
VL53L0X sensor1;  //Sensor da esquerda
VL53L0X sensor2;  //Sensor da frente
VL53L0X sensor3;  //Sensor da direita
VL53L0X sensor4;  //Sensor da direita
// VL53L0X sensor5;  //Sensor da direita
VL53L0X sensor6;  //Sensor da direita
// VL53L0X sensor7;  //Sensor da direita

//Variáveis que vão receber os valores lidos dos pinos dos sensores
int dist1;  //Valor lido pelo sensor 1
int dist2;  //Valor lido pelo sensor 2
int dist3;  //Valor lido pelo sensor 3
int dist4;  //Valor lido pelo sensor 4
// int dist5;  //Valor lido pelo sensor 5
int dist6;  //Valor lido pelo sensor 6
// int dist7;  //Valor lido pelo sensor 7


void setup() {
    Serial.begin(112500);
    LED.init();
    LED.latch(100,AZUL);

    // pinMode(2,OUTPUT);

    left_motor.init();
    right_motor.init();
   
    imu_connect = imu_setup();
    Serial.print("aaaaaaaaaaaaaaaaaaaaaaaaaaa");

    controle_sony.init();
    Serial.print("bbbbbbbbbbbbbbbbbbbbbbbbbbbbb");
    rft_back.init();
    Serial.print("ccccccccccccccccccccccccccccc");
    rft_front.init();
    Serial.print("ddddddddddddddddddddddddddddddd");


  if(imu_connect == 0) {
   
    // digitalWrite(2, HIGH); 
  }

  // vl_init();


    //debug potenciometer
    pinMode(pinPot,INPUT);

    

    delay(500);


    LED.set(VERMELHO);

}

void loop() {


    //inputs 

    int cr_read = controle_sony.read();

    int  detect_border_front = rft_front.read();
    int  detect_border_back = rft_back.read();

    float* imu_ypr = imu_get_ypr(); 

    int val = analogRead(pinPot);
    int speed = map(val, 0, 4096,-100,100); 


   //main_machine state for the fight levels 

    switch (cr_read)
    {
    case ONE :
      //enable robot 
      led_color = AMARELO;
      break;
    
    case TWO :
      // fight 
      led_color = VERDE;
      break;    


    case TREE :
      // stop 
      led_color = AZUL ;
      break;    
    }

    // distanceRead();

    Serial.print(" CR: ");
    Serial.print(cr_read);
    Serial.print(" RFT: ");
    Serial.print(detect_border_back);
    Serial.print(" ");
    Serial.print(detect_border_front);
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

    // printDistances();

    LED.set(led_color);
    left_motor.write(speed);
    right_motor.write(speed);
}

void vl_init() {

    //Iniciando o endereçamento dos sensores
    // Wire.begin();

    pinMode(SDIST_1, OUTPUT);
    // pinMode(SDIST_2, OUTPUT);
    // pinMode(SDIST_3, OUTPUT);
    // pinMode(SDIST_4, OUTPUT);
    // // pinMode(SDIST_5, OUTPUT);
    // pinMode(SDIST_6, OUTPUT);
    // // pinMode(SDIST_7, OUTPUT);

    digitalWrite(SDIST_1, LOW);
    // digitalWrite(SDIST_2, LOW);
    // digitalWrite(SDIST_3, LOW);
    // digitalWrite(SDIST_4, LOW);
    // // digitalWrite(SDIST_5, LOW);
    // digitalWrite(SDIST_6, LOW);
    // // digitalWrite(SDIST_7, LOW);

    pinMode(SDIST_1, INPUT);
    sensor1.init(true);
    sensor1.setAddress((uint8_t)0x21); //endereço do sensor 1

    // pinMode(SDIST_2, INPUT);
    // sensor2.init(true);
    // sensor2.setAddress((uint8_t)0x22); //endereço do sensor 2

    // pinMode(SDIST_3, INPUT);
    // sensor3.init(true);
    // sensor3.setAddress((uint8_t)0x23); //endereço do sensor 3

    // pinMode(SDIST_4, INPUT);
    // sensor4.init(true);
    // sensor4.setAddress((uint8_t)0x24); //endereço do sensor 4

    // pinMode(SDIST_5, INPUT);
    // sensor5.init(true);
    // sensor5.setAddress((uint8_t)0x25); //endereço do sensor 5

    // pinMode(SDIST_6, INPUT);
    // sensor6.init(true);
    // sensor6.setAddress((uint8_t)0x26); //endereço do sensor 6

    // pinMode(SDIST_7, INPUT);
    // sensor7.init(true);
    // sensor7.setAddress((uint8_t)0x27); //endereço do sensor 7

    sensor1.setTimeout(4);
    // sensor2.setTimeout(20);
    // sensor3.setTimeout(20);
    // sensor4.setTimeout(20);
    // // sensor5.setTimeout(20);
    // sensor6.setTimeout(20);
    // // sensor7.setTimeout(20);
}

void distanceRead() {
    //Armazena os valores lidos nas respectivas variáveis
    dist1 = sensor1.readRangeSingleMillimeters();
    // dist2 = sensor2.readRangeSingleMillimeters();
    // dist3 = sensor3.readRangeSingleMillimeters();
    // dist4 = sensor4.readRangeSingleMillimeters();
    // // dist5 = sensor5.readRangeSingleMillimeters();
    // dist6 = sensor6.readRangeSingleMillimeters();
    // // dist7 = sensor7.readRangeSingleMillimeters();

// Filtro 
//    if(distL > 600) distL = 600;
//    if(distC > 600) distC = 600;
//    if(distR > 600) distR = 600;
}

void printDistances() {
  // Mostra o valor de cada sensor na tela e a decisão escolhida
  Serial.print("1: ");
  Serial.print(dist1);
  Serial.print("\t");
  // Serial.print("2: ");
  // Serial.print(dist2);
  // Serial.print("\t");
  // Serial.print("3: ");
  // Serial.print(dist3);
  // Serial.print("\t");
  // Serial.print("4: ");
  // Serial.print(dist4);
  // Serial.print("\t");
  // // Serial.print("5: ");
  // // Serial.print(dist5);
  // // Serial.print("\t");
  // Serial.print("6: ");
  // Serial.print(dist6);
  // Serial.print("\t");
  // Serial.print("7: ");
  // Serial.print(dist7);
  Serial.println("\t\t");
}
