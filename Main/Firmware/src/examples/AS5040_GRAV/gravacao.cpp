#include <Arduino.h>
#include <AS5040.h>

// CHANGE THESE AS APPROPRIATE
#define CSpin   33
#define CLKpin  32
#define DOpin   34
#define PROGpin 35

#define ButtonPin 26

AS5040 enc(CLKpin, CSpin, DOpin, PROGpin);



void gravacao(){
    digitalWrite(2, HIGH);
    // troca o 3.3v por 7v, depois aperta o botao
    while(true){
        if(digitalRead(ButtonPin) == LOW){
            break;
        }
        Serial.println("aaaaaaaa");
        delay(100);
    }
    digitalWrite(2, LOW);

    // gravacao();
    for (byte i = 0 ; i < 16 ; i++){
        digitalWrite (CLKpin, HIGH) ;
        delayMicroseconds (2) ;
        digitalWrite (CLKpin, LOW) ;
        delayMicroseconds (2) ;
    }
    delay(3000);

    digitalWrite(2,HIGH);
    // troca o 7v por 3.3v, depois aperta o botao
    while(true){
        if(digitalRead(ButtonPin) == LOW){
            break;
        }
        Serial.println("bbbbbbbbbb");
        delay(100);
    }
    digitalWrite(2, LOW);
    
    // desce o CSn para lOW ----> terminado
    digitalWrite(CSpin, LOW);
    
    delay(3000);
    
}

void setup (){
    Serial.begin (115200) ;   // NOTE BAUD RATE
    if (!enc.begin (AS5040_QUADRATURE, false, 0))  // example setting reverse sense and an offset
        Serial.println ("Error setting up AS5040");

    pinMode(2, OUTPUT);
    pinMode(ButtonPin, INPUT_PULLUP);
    delay(1000);
    Serial.println("vai toma no cu");

    gravacao();

    Serial.println("Sera q deu certo?");

  
}

void loop(){

    

}