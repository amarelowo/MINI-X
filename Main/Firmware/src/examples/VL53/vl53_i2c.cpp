//Bibliotecas externas
#include <Arduino.h>
#include <Wire.h>       //Auxiliar dos sensores
#include <VL53L0X.h>    // Usar a biblioteca da POLULU!

// MAPA PARA CONEXÕES ELETRÔNICAS

// ADICIONAR UM RESISTOR DE 4.7K ENTRE O PINO SCL E O 3.3V APENAS NO PRIMEIRO SENSOR
// ADICIONAR UM RESISTOR DE 4.7K ENTRE O PINO SDA E O 3.3V APENAS NO PRIMEIRO SENSOR
  

// SCL, SDA, as mesmas portas para todos os sensores
#define SCL_SDIST 22
#define SDA_SDIST 21

// XSHUT, uma porta por sensor 
#define SDIST_1 13
#define SDIST_2 12
#define SDIST_3 27
#define SDIST_4 26
// #define SDIST_5 25
#define SDIST_6 2
// #define SDIST_7 16

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

void sensorsInit();
void distanceRead();
void printDistances();

void setup(){
  Serial.begin(112500);
  sensorsInit();
}

void loop() {
  distanceRead();
  printDistances();
  delay(500);

}

void sensorsInit() {

    //Iniciando o endereçamento dos sensores
    // Wire.begin();

    pinMode(SDIST_1, OUTPUT);
    pinMode(SDIST_2, OUTPUT);
    pinMode(SDIST_3, OUTPUT);
    pinMode(SDIST_4, OUTPUT);
    // pinMode(SDIST_5, OUTPUT);
    pinMode(SDIST_6, OUTPUT);
    // pinMode(SDIST_7, OUTPUT);

    digitalWrite(SDIST_1, LOW);
    digitalWrite(SDIST_2, LOW);
    digitalWrite(SDIST_3, LOW);
    digitalWrite(SDIST_4, LOW);
    // digitalWrite(SDIST_5, LOW);
    digitalWrite(SDIST_6, LOW);
    // digitalWrite(SDIST_7, LOW);

    pinMode(SDIST_1, INPUT);
    sensor1.init(true);
    sensor1.setAddress((uint8_t)0x21); //endereço do sensor 1

    pinMode(SDIST_2, INPUT);
    sensor2.init(true);
    sensor2.setAddress((uint8_t)0x22); //endereço do sensor 2

    pinMode(SDIST_3, INPUT);
    sensor3.init(true);
    sensor3.setAddress((uint8_t)0x23); //endereço do sensor 3

    pinMode(SDIST_4, INPUT);
    sensor4.init(true);
    sensor4.setAddress((uint8_t)0x24); //endereço do sensor 4

    // pinMode(SDIST_5, INPUT);
    // sensor5.init(true);
    // sensor5.setAddress((uint8_t)0x25); //endereço do sensor 5

    pinMode(SDIST_6, INPUT);
    sensor6.init(true);
    sensor6.setAddress((uint8_t)0x26); //endereço do sensor 6

    // pinMode(SDIST_7, INPUT);
    // sensor7.init(true);
    // sensor7.setAddress((uint8_t)0x27); //endereço do sensor 7

    sensor1.setTimeout(20);
    sensor2.setTimeout(20);
    sensor3.setTimeout(20);
    sensor4.setTimeout(20);
    // sensor5.setTimeout(20);
    sensor6.setTimeout(20);
    // sensor7.setTimeout(20);
}

void distanceRead() {
    //Armazena os valores lidos nas respectivas variáveis
    dist1 = sensor1.readRangeSingleMillimeters();
    dist2 = sensor2.readRangeSingleMillimeters();
    dist3 = sensor3.readRangeSingleMillimeters();
    dist4 = sensor4.readRangeSingleMillimeters();
    // dist5 = sensor5.readRangeSingleMillimeters();
    dist6 = sensor6.readRangeSingleMillimeters();
    // dist7 = sensor7.readRangeSingleMillimeters();

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
  Serial.print("2: ");
  Serial.print(dist2);
  Serial.print("\t");
  Serial.print("3: ");
  Serial.print(dist3);
  Serial.print("\t");
  Serial.print("4: ");
  Serial.print(dist4);
  Serial.print("\t");
  // Serial.print("5: ");
  // Serial.print(dist5);
  // Serial.print("\t");
  Serial.print("6: ");
  Serial.print(dist6);
  // Serial.print("\t");
  // Serial.print("7: ");
  // Serial.print(dist7);
  Serial.println("\t\t");
}