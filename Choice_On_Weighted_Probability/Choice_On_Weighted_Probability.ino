/*
*   Choice_On_Weighted_Probability
 *  Copyright June 2015, Don Bosley
 *  www.bosleymusic.com
 *  don@bosleymusic.com
 *  
 *  Written for NYU ITP Adult Summer Camp Session : 
 *  "Controlling Chaos : 
 *   Harnessing The Power of Random Number Generators as Creative Assistants"
 *
 *  Given a fixed set of states, we're establishing a set of probabilities
 *  that any state transistions to another state. By setting up these
 *  probabilities, you can establish certain elements of a grammar, or 
 *  an element of predictability to random decisions. Psuedo-patterns of 
 *  behavior can be achieved that are rich enough in variety so as not to 
 *  become boring, but can still be predictable enough that a structure 
 *  begins to emerge.
 *
 *  To run this, dump the code to Arduino, and open the serial terminal.
 *
 *   Things to try : 
 *    - Initialize your probability table with random numbers
 *    --- This will ensure a 'unique' process every time.
 *    - To evolve a process, change the probabilities over time.
 *
 *  For more infomation on similar processes, look up : 
 *     - State Machines
 *     - Markov-chains
 *
 */


/* Variables for holding state */
uint8_t current_state = 0; 
uint8_t rand_decision_value = 0; 

/* State table and probailities of transition : 
 Left Column = The state of the variable
 Top Row = the states that the variable can move to,
 The intersection is the probability that 
 the left column value transitions to the top row
 value. Notice all of the probability rows add to 1.
 
 ___|  0  |   1   |   2   |  3   |
 ________________________________
 0  | .7  |  .1   |  .1   |  .1  |  = 1
 ___|_____|_______|_______|______|
 1  |  0  |  .7   |  .2   |  .1  |  = 1
 ___|_____|_______|_______|______|
 2  |  0  |  .2   |  .7   |  .1  |  = 1
 ___|_____|_______|_______|______|
 3  | .2  |  .1   |  .1   |  .6  |  = 1
 ___|_____|_______|_______|______|
 
 
 Only 3 can transition to 0, and 0's 
 self choice is weaker than other values, 
 so 0 will likely appear the least, and for
 the shortest amounts of time when it does.
 1 and 2 have the most likelihood to be 
 transitioned to. 
 
 The array to hold the probabilities will be 
 be 0:100 in integer values, so that our table
 is compatible with the random number generator
 output.
 
 You'll also notice the table is a running sum, 
 rather than the values. This is to enable the logic 
 in the while loop that makes the "decision."
 */

uint8_t state_probability_table[4][4] = {
  {
    70, 80, 90, 100  }
  , //70, 10, 10, 10;
  {
    0, 70, 90, 100  }
  , //0, 70, 20, 10;
  {
    0, 20, 90, 100  }
  , //0, 20, 70, 10;
  {
    20, 30, 40, 100  }
  ,//20, 10, 10, 60;
};

uint8_t adder = 0;   //This will keep a running sum for comparison
uint8_t k = 0;        //Generic Counter

/***** SETUP *****/
void setup(){
  Serial.begin(9600); //Start serial communication
  randomSeed(analogRead(0));//Seed
  delay(5000);        //5 seconds to open terminal   
}


void loop(){

  //Generate the Random Number to Make a Decision
  rand_decision_value = random(0,101);        //0 - 100 (101 non-inclusive)
  Serial.print("Random Number : ");              // prints the label
  Serial.println(rand_decision_value, DEC);   //prints a value

  //Initialize the transition
  k = 0;
  /* Find the selected transition: This was the reason for the running 
   sum values of the state_probability_table. We look at 
   state_probability_table[...][...] and make a comparison of the random value.
   If we simply used raw values, the right state would never be reached. 
   If the random value is less than the value from the table the loop terminates
   and we have the new state, which will be accessed in the decision on the next
   loop.  */
  while(rand_decision_value > state_probability_table[current_state][k]){
    k++;
  }
  current_state = k;                    //New or continued state
  Serial.print("Current State : ");     // prints the label
  Serial.println(current_state, DEC);   //prints a value

  delay(2000); //Delays 2 seconds so you can actually watch terminal 
}



