/*
*   G_Changing Direction
 *  Copyright June 2015, Don Bosley
 *  www.bosleymusic.com
 *  don@bosleymusic.com
 *  
 *  Written for NYU ITP Adult Summer Camp Session : 
 *  "Controlling Chaos : 
 *   Harnessing The Power of Random Number Generators as Creative Assistants"
 *
 *  This adds direction change to previous versions of the code.
 *
 */

/***** INCLUDES & PIN DEFINES *****/
#include <Adafruit_NeoPixel.h>

#define NEO_PIN       2  //Data Pin
#define NUM_PIXELS   12  //How many pixels in the ring
#define FORWARD       1  //Positive Rotation
#define BACKWARD      0  //Negative Rotation

/***** VARIABLES *****/
//COLOR VALUES
volatile uint8_t  red, green, blue = 0;
volatile uint8_t  red2, green2, blue2 = 0;

uint8_t  i = 0;        //Variables for counting
int8_t  k, carry = 0;         //We need to make k 'signed' now...
volatile uint8_t period = 0;    //Period in ms between color moves
float  scalar;         //The amount to trim color by
boolean dir;           //Moving Forward or Backward
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

  //Starting the direction forward always...
  //  dir = FORWARD; 
  //Actually, that's boring, let's choose a random direction
  dir = random(0,2);
}

void loop(){

  /*This is a very simple way to do this...the modulo operator is explored in 
   later iterations of this code */

  if(dir){ //If dir == FORWARD, or 'TRUE'
    //Outerloop (k) sets which pixel will recieve the color
    while(k < NUM_PIXELS){  

      pixel_zero(); //Setting all non-k values to 0 for new color
      does_something_change(); //Random Color or Speed Change
      color_vary(); //This code has been replaced by a subfunction

      pixels.setPixelColor(k, pixels.Color(red2, green2, blue2)); //Turn on 'k'th LED
      pixels.show();                                           //Show all values
      delay(period);        //Delay to next Move 

      //Decision to Change Direction - about an 8% chance
      if (random(0,255) > 240) {
        dir = !dir; //Flip the boolean value and reverse the direction
        break;      //Break from the loop...
      } 
      else { //Logic for counting and resetting the count
        k++;  
        if (k >= NUM_PIXELS){
          k = 0;
        }
      }
    }
  }


  if(!dir) {
    while(k > -1){
      pixel_zero(); //Setting all non-k values to 0 for new color
      does_something_change(); //Random Color or Speed Change
      color_vary(); //This code has been replaced by a subfunction

      pixels.setPixelColor(k, pixels.Color(red2, green2, blue2)); //Turn on 'k'th LED
      pixels.show();                                           //Show all values
      delay(period);                                           //Delay to next Move 

      //Decision to change direction - about an 8% chance
      if (random(0,255) > 240) {
        dir = !dir; //Flip the boolean value and reverse the direction
        break;
      } 
      else { //Logic for counting and resetting the count
        k--;
        if (k < 0){
          k = NUM_PIXELS-1;
        }
      }
    }
  }
}


/***** DECISION TREE FOR SELECTING NEW COLOR *****/
void color_select(void){
  //Redeclare i & k so that the external variables are not altered...
  //Otherwise it would force the loop count to reset to the random values

  int i, k;
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

}

/**** ADDS VARIATION TO COLORS *****/
void color_vary(void) {
  scalar = (float)random(10,101) / 100;
  if (red) {
    red2 = (uint8_t)(scalar * (float)red);
  } 
  else {
    red2 = 0;
  }
  if (green) {
    green2 = (uint8_t)(scalar * (float)green);
  } 
  else {
    green2 = 0;
  }
  if (blue) {
    blue2 = (uint8_t)(scalar * (float)blue);
  } 
  else {
    blue2 = 0;
  }
}


/***** SET PIXEL VALUES TO ZERO *****/
void pixel_zero(void){
  for(i=0;i<NUM_PIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  } 
}

void does_something_change(){

  //Replace the color selection with a function...10% chance of change...
  //Insert into the loop and make a decision on whether to change...
  if (random(0,255) > 235) {
    color_select();
  }
  //Re-change period ... 10% chance of change...
  if (random(0,255) > 235) {
    period = 1 + random(0,200);
  }

}













