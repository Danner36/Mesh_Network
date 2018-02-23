/**
 * Keypad.cpp holds all functions related to the keypad. 
 */

#include <Arduino.h>
#include <Keypad.h>
#include "Globals.h"
#include "keyP.h"
#include "Radio.h"


/**
 * Constructor used to reference all other variables & functions.
 */
KEYPAD::KEYPAD()
{
  
}


/**
 * Updates "pressedKey" to current input. 
 */
void KEYPAD::check(char key)
{
  //Resets the inputted key. 
  pressedKey = ' ';
  
  //Checks for actual press. 0 means no key has been pressed.
  if(key != 0x00){
    Radio.blinkLED();

    pressedKey = key;
    
  }
}

