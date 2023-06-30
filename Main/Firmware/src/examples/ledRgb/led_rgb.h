//PWM control for the motors 
#include <Adafruit_NeoPixel.h>

#define AMARELO #fce803
#define VERMELHO #fc0303
#define VERDE #00f708
#define AZUL #00c2f7

#define NUMPIXELS 7
#define RGB_PIN 4


class led_rgb 
{
private:
  
public:

    Adafruit_NeoPixel pixels(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800);
    void init();
    void blink(int time);
};


void led_rgb ::init(){
    //set motor
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.setBrightness(100); // not so bright]
  pixels.fill(0x000000);
  pixels.show();
    
};

void led_rgb ::blink(int time){
   // set color to red
  pixels.fill(0xFF0000);
  pixels.show();
  delay(500); // wait half a second

  // turn off
  pixels.fill(0x000000);
  pixels.show();
  delay(500); 
   
}