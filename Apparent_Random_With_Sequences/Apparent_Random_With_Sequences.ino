/*
*   Apparent Random Sequences
 *  Copyright June 2015, Don Bosley
 *  www.bosleymusic.com
 *  don@bosleymusic.com
 *  
 *  Written for NYU ITP Adult Summer Camp Session : 
 *  "Controlling Chaos : 
 *   Harnessing The Power of Random Number Generators as Creative Assistants"
 *
 *  Very simple. By using an underlying process that is very controlled
 *  and predicatable, you can create an output that looks very complex.
 *
 *  To run this, dump the code to Arduino, and open the serial terminal.
 *
 *   Things to try : 
 *    - Various Prime Numbers to see how "random" you can make the appearance
 *      of the sequence. Set the define value to different numbers and see 
 *      what happens
 *
 *  For more infomation on similar processes, look up : 
 *     - Phasing
 *
 */

#define IMAX   3  
#define KMAX   2

uint8_t value = 15; 
int8_t i, k; //Counters

void setup(){
  Serial.begin(9600);   //Starts our connection to terminal
  Serial.println(value); //Shows the value of seed
  delay(10000);         //Gives 10 seconds to open terminal
  
  i = 0;
  k = KMAX;
}


void loop(){
  
   value = (value << i++);      //Perform A left sheft, increase i
   value = (value | 1 << k--);  //Perform OR, decrease k
   Serial.println(value, DEC);   //Show Resulting value
   delay(1000);                 //Give you a second to process
   
   //Ensure counters stay in range
   if (i > IMAX){                  
     i = 0;
   }
   if (k < 0){
     k = KMAX;
   }
    
}
