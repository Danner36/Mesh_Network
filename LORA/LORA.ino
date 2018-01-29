/****LIBRARIES****/
#include <RH_RF95.h>
#include "RADIO.h"

/*****CONSTRUCTORS*****/ //(Objects that can reference their respective functions & variables)
RADIO Radio;

//Directs the radio object to focus on two specific ports.
RH_RF95 rf95(8,7);


/**
 * INITIALIZES ALL REQUIRED PERIPHIALS AND DEPENDENCIES.
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

  //Responsible for grabbing all of the craft's current information, 
  //   turning that data into an array that can be sent out via radio.
  //   Also reads in incoming messages.
  Radio.manager();


  delay(1000);
}
