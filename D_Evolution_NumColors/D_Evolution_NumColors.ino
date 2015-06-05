/*
*   D_Evolution_NumColors
 *  Copyright June 2015, Don Bosley
 *  www.bosleymusic.com
 *  don@bosleymusic.com
 *  
 *  Written for NYU ITP Adult Summer Camp Session : 
 *  "Controlling Chaos : 
 *   Harnessing The Power of Random Number Generators as Creative Assistants"
 *
 *  D_Evolution_NumColors presents the first decision tree : 
 *  it will randomize not only the color values,  but the number of colors which 
 *  will be present. This will eliminate the whiteness and speed on each rotation.
 *  While it produces a variety of colors and speeds, the viewer knows
 *  that when the rotation has gone through 360 degrees, that a change 
 *  will occur. This is STILL fairly deterministic.
 *
 */

/***** INCLUDES & PIN DEFINES *****/
#include <Adafruit_NeoPixel.h>

#define NEO_PIN       2  //Data Pin
#define NUM_PIXELS   12  //How many pixels in the ring

/***** VARIABLES *****/
//COLOR VALUES
uint8_t  red = 0;
uint8_t  green = 0;
uint8_t  blue = 0;  

uint8_t  i,k = 0;         //Variables for counting
uint32_t period = 0;    //Period in ms between color moves

//Initialize Neo-pixel library
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  pixels.begin(); // This initializes the NeoPixel library.

  //Seed the random number generator with "pin noise" 
  //Arduino's DAC is not necissarily the best seed...
  randomSeed(analogRead(0));

  //Randomly select the color intensity values
  red = random(0,255); 
  green = random(0,255); 
  blue = random(0,255); 

  //Getting sort of a whitish every time? 
  //Set the period between 10ms and .5 s
  period = 1 + random(0,199);
}

void loop(){

  //Re-randomize Color and number of colors
  i = random(1,4); 

  switch (i) {  //Picks number of colors, sub switches pick which colors
  case 1:
    k = random(1,4);
    switch(k){
    case 1:
      red = random(0,255); 
      green = blue = 0;
      break; 
    case 2:
      green = random(0,255); 
      blue = red = 0;
      break; 
    case 3:
      blue = random(0,255); 
      green = red = 0;
      break;
    default:
      break;
    }
    break;
  case 2:
    k = random(1,4);
    switch(k){
    case 1:
      red = random(0,255); 
      green = random(0,255);
      blue = 0;
      break; 
    case 2:
      red = 0; 
      green = random(0,255);
      blue = random(0,255);
      break; 
    case 3:
      red = random(0,255); 
      green = 0;
      blue = random(0,255);
      break;
    default:
      break;
    }
    break;
  case 3: //Adding weight...
    k = random(1,5);
    switch(k){
    case 1:
      red = random(0,64); 
      green = random(0,255);
      blue = random(0,255);
      break; 
    case 2:
      red = random(0,255); 
      green = random(0,64);
      blue = random(0,255);
      break; 
    case 3:
      red = random(0,255); 
      green = random(0,255);
      blue = random(0,64);
      break;
    case 4:
      red = random(0,random(255)); 
      green = random(0,random(255));
      blue = random(0,random(255));
      break;
    default: 
      break;
    }
    break;
  default : 
    break; 
  }

  //Re-change period
  period = 1 + random(0,199);

  /*This is a very simple way to do this...the modulo operator is explored in 
   later iterations of this code */

  //Outerloop (k) sets which pixel will recieve the color
  for (k = 0; k < NUM_PIXELS; k++){  
    pixels.setPixelColor(k, pixels.Color(red, green, blue)); //Turn on 'k'th LED
    pixels.show();                                           //Show all values
    delay(period);                                         //Delay to next Move 
    pixels.setPixelColor(k, pixels.Color(0, 0, 0));          //Reset that pixel to zero  
  }
}










