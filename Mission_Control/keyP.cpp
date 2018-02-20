/**
 * Keypad.cpp holds all functions related to the keypad. 
 */

#include <Arduino.h>
#include <Keypad.h>
#include "Globals.h"
#include "keyP.h"
#include <Keypad.h>


/**
 * Constructor used to reference all other variables & functions.
 */
KEYPAD::KEYPAD()
{
  
}


/**
 * Updates "pressedKey" to current input. 
 */
void KEYPAD::check(char temp)
{
  pressedKey = temp;

  //Checks for actual press. 0 means no key has been pressed.
  if(pressedKey != 0x00){
  
    Serial.print("Key pressed: ");
    Serial.println(pressedKey);
  }
}

