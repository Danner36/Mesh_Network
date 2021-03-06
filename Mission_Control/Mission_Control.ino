// NON EAGLE EYE
#include <RH_RF95.h>
#include <Keypad.h>

// EAGLE EYE'S
#include "Globals.h"
#include "Data.h"
#include "Radio.h"
#include "keyP.h"


// Construct objects that can reference their respective functions & variables
DATA Data;
RADIO Radio;
KEYPAD Key;


// Directs the radio object to focus on two specific ports.
RH_RF95 rf95(8,7);
          
// Keypad object. Defind in Keypad.cpp initialize function. 
Keypad pad = Keypad(makeKeymap(Key.keys), Key.rowPins, Key.colPins, 3, 3); 



/**
 * Method initializes the main hardware components.
 */
void setup(){

  // Creates a serial communication line between the arduino and the serial port 
  // found under 'Tools' -> 'Serial Monitor'
  Serial.begin(115200);
  
  // Initializes the Radio.
  Radio.initialize();
}


/**
 * MAIN PROGRAM CODE.
 */
void loop(){

  // Checks for a user inputted command. 
  Data.newCommand();
  
  // Looks to see any keys have been pressed. Updates the variable "pressedKey" if found.
  Key.check(pad.getKey());
  
  // Responsible for grabbing all of the craft's current information,
  // turning that data into an array that can be sent out via radio.
  // Also reads in incoming messages.
  Radio.manager();

  // Displays current information of craft.
  Data.displayInfo();
  
  delay(10);
}
