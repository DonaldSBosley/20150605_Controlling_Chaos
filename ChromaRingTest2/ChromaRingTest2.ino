#include <Adafruit_NeoPixel.h>

#define NEOPIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, NEOPIN, NEO_RGB + NEO_KHZ800); 
int k; 
void setup(){
  strip.begin(); 
  strip.show(); 
}

void loop(){

  strip.setPixelColor(random(0,12) , random(0, random(0,random(0,250))),random(0, random(0,random(0,250))),random(0, random(0,random(0,250))));
  strip.show();
  for (k = 0; k < 12; k++){
      strip.setPixelColor(random(0,12) , 0,0,0);
  }
  delay(random(0,500)); 
    strip.show();
    
 }
  



