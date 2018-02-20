/**
 * Keypad.h holds all declarations and varaibles related to the Keypad.cpp file.
 */

#ifndef KEYPAD_h
#define KEYPAD_h

#include <Arduino.h>

class KEYPAD
{
  public:

  //Constructor
  KEYPAD();

  //Checks for new key press. Records its value. 
  void check(char temp);



  //Current key being pressed down. If none, than = 0.
  int pressedKey = 0;
 
};

#endif
