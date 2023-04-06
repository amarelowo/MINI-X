#include <Arduino.h>
#include <Wire.h>

class as5600{
    public:
        float degAngle,
            correctdAngle = 0,
            starAngle,
            totalAngle = 0;

        int rawAngle,
            lowbyte,
            quadrant,
            lastQuandrant = 0,
            turns = 0,
            magnetStatus = 0,
            adress;

        word highbyte;

    as5600(int _adress){
        adress = _adress;
        
    }

    void setInitialAngle(){
        starAngle = readRawAngle();
        Serial.print("IA: ");
        Serial.println(starAngle);
    }

    void checkMagnetPresence(){
        // 
        while((magnetStatus & 32) != 32){
            magnetStatus = 0;

            Wire.beginTransmission(adress);
            Wire.write(0x0B);
            Wire.endTransmission();
            Wire.requestFrom(0x36, 1);
    
            while(Wire.available() == 0);

            magnetStatus = Wire.read();

            Serial.print("Magnet status: BIN: ");
            Serial.print(magnetStatus, BIN);
            Serial.print(" | DEC: ");
            Serial.println(int(magnetStatus));
        }
    }

    float readRawAngle(){
        Wire.beginTransmission(adress);
        Wire.write(0x0D);
        Wire.endTransmission();
        Wire.requestFrom(adress,1);

        while(Wire.available() == 0);
        lowbyte = Wire.read();

        Wire.beginTransmission(adress);
        Wire.write(0x0C); //figure 21 - register map: Raw angle (11:8)
        Wire.endTransmission();
        Wire.requestFrom(adress, 1);

        while(Wire.available() == 0);  
        highbyte = Wire.read();

        highbyte = highbyte << 8;

        rawAngle = highbyte | lowbyte;

        degAngle = rawAngle * 0.087890625;
        Serial.print("PA: ");
        Serial.print(rawAngle);
        Serial.print(" | ");
        return degAngle;
    }

    float readAngle(){

        degAngle = readRawAngle();

        correctdAngle = degAngle - starAngle;
        if(correctdAngle < 0){
            correctdAngle = correctdAngle + 360;
        }

        if(correctdAngle > 0 && correctdAngle <= 90){
            quadrant = 1;
        }
        if(correctdAngle > 90 && correctdAngle <= 180){
            quadrant = 2;
        }
        if(correctdAngle > 180 && correctdAngle <= 270){
            quadrant = 3;
        }
        if(correctdAngle > 270 && correctdAngle < 360){
            quadrant = 4;
        }

        if((quadrant != lastQuandrant) && (lastQuandrant != 0)){
            if(quadrant == 1 && lastQuandrant == 4){
                turns++;
            }
            if(quadrant == 4 && lastQuandrant == 1){
                turns--;
            }
        }
        lastQuandrant = quadrant;
        totalAngle = (turns * 360) + correctdAngle;
        Serial.print("T: ");
        Serial.print(turns);
        Serial.print(" | Q: ");
        Serial.print(quadrant);
        Serial.print(" | CA: ");
        Serial.print(correctdAngle);
        Serial.print(" | RA: ");
        Serial.print(degAngle);
        Serial.print(" | TA: ");
        Serial.println(totalAngle);

        return totalAngle;
    }
};