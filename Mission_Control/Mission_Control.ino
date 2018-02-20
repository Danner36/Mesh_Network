/****LIBRARIES****/

//NON EAGLE EYE
#include <RH_RF95.h>
#include <Keypad.h>

//EAGLE EYE'S
#include "Globals.h"
#include "Data.h"
#include "Radio.h"
#include "keyP.h"



/*****CONSTRUCTORS*****/ //(Objects that can reference their respective functions & variables)
DATA Data;
RADIO Radio;
KEYPAD Key;


//Directs the radio object to focus on two specific ports.
RH_RF95 rf95(8,7);

//No idea.
byte ligne_pin[3] = {5, 6, 9};

//No idea.
byte colonne_pin[3] = {11, 12, 13};

//Matrix layout of the keypad in use. 
char keypadLayout[3][3] ={
                 {'1','2','3'},
                 {'4','5','6'},
                 {'7','8','9'},
                };
                
//Keypad object. Defind in Keypad.cpp initialize function. 
Keypad pad = Keypad(makeKeymap(keypadLayout), ligne_pin, colonne_pin, 3, 3); 

/**
 * Method initializes the main hardware components.
 */
void setup(){

  //Creates a serial communication line between the arduino and the serial port 
  //   found under 'Tools' -> 'Serial Monitor'
  Serial.begin(115200);
  
  //Initializes the Radio.
  Radio.initialize();
}


/**
 * MAIN PROGRAM CODE.
 */
void loop(){

  //Looks to see any keys have been pressed. Updates the variable "pressedKey" if found.
  Key.check(pad.getKey());
  
  //Responsible for grabbing all of the craft's current information,
  //   turning that data into an array that can be sent out via radio.
  //   Also reads in incoming messages.
  Radio.manager();

  //Displays current information of craft.
  Data.displayInfo();
  
  delay(5000);
}
