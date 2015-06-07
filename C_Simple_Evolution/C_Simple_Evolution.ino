/*
*   C_Simple_Evolution
 *  Copyright June 2015, Don Bosley
 *  www.bosleymusic.com
 *  don@bosleymusic.com
 *  
 *  Written for NYU ITP Adult Summer Camp Session : 
 *  "Controlling Chaos : 
 *   Harnessing The Power of Random Number Generators as Creative Assistants"
 *
 *  C_Simple_Evolution will randomize color and speed on each rotation.
 *  While it produces a variety of colors and speeds, the viewer knows
 *  that when the rotation has gone through 360 degrees, that a change 
 *  will occur. This is fairly deterministic.
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

  //Re-randomize Color
  red = random(0,255); 
  green = random(0,255); 
  blue = random(0,255); 

  //Re-change period
  period = 1 + random(0,199);

  //Outerloop (k) sets which pixel will recieve the color
  for (k = 0; k < NUM_PIXELS; k++){  
    pixels.setPixelColor(k, pixels.Color(red, green, blue)); //Turn on 'k'th LED
    pixels.show();                                           //Show all values
    delay(period);                                         //Delay to next Move 
    pixels.setPixelColor(k, pixels.Color(0, 0, 0));          //Reset that pixel to zero
  }
}



