/*
*  A_Rotation
 *  Copyright June 2015, Don Bosley
 *  www.bosleymusic.com
 *  don@bosleymusic.com
 *
 *  Written for NYU ITP Adult Summer Camp Session : 
 *  "Controlling Chaos : 
 *   Harnessing The Power of Random Number Generators as Creative Assistants"
 *
 *  A_Rotation drives a custom ring of (12) 5112b RGB LEDs utilizing 
 *  the Adafruit Neo-Pixel library. It simply moves circularly giving 
 *  the appearance of a single color, rotating point around the 
 *  circumference of the ring.
 *
 */

/***** INCLUDES & PIN DEFINES *****/
#include <Adafruit_NeoPixel.h>

#define NEO_PIN       2  //Data Pin
#define NUM_PIXELS   12  //How many pixels in the ring

/***** VARIABLES *****/
//COLOR VALUES
int red = 32;
int green = 128;
int blue = 0;  

int i,k = 0;         //Variables for counting
int period = 100;    //Period in ms between color moves

//Initialize Neo-pixel library
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  pixels.begin(); // This initializes the NeoPixel library. 
}

void loop(){

  //Loop counter (k) sets which pixel will recieve the color
  for (k = 0; k < NUM_PIXELS; k++){  
    pixels.setPixelColor(k, pixels.Color(red, green, blue)); //Turn on 'k'th LED
    pixels.show();                                           //Show all values
    delay(period);                                           //Delay until next "move"
    pixels.setPixelColor(k, pixels.Color(0, 0, 0));          //Reset that pixel to zero
  }
}



