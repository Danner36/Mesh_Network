/**
 * Data.h is responsible for updating the programs main struct to the current most values.
 */

#ifndef DATA_h
#define DATA_h

#include <Arduino.h>

class DATA
{
  public:
  
  //Constructor
  DATA();

  //Responsible for pulling current sensor data from peripherals.
  void displayInfo();

  //Prints nodes from Radio.nodeList.
  void printNodes();

  
  
	//Parses passed in message by using commas as the identifiers.
	float Parse(char message[], int objective);

  //State of Data.
  //   This enum is used in the UI display process. It will watch all the variables
  //   and if any have changed compared to the last cycle, it will switch to yes. 
  //   When it is in the YES state, the displayInfo() method will print out the newly
  //   accuried data to the serial monitor. The purpose of this is have a readable UI
  //   without having it update every few milliseconds. (Potential future solution is
  //   would be to use an external terminal such as Putty)
  enum dataState {NO, YES};
  enum dataState newData = YES; //Starts in Yes to the intial UI. 

  //false = Direct Line of Commuication to Craft. (Eagle Eye Blimp)
  //   true = Receiving information through another craft. Not direct from Eagle Eye.
  //
  //   THIS WILL NOT BE IMPLEMENTED UNTIL THIRD NODE IS BROUGHT ONLINE. PLACEHOLDER.
  //
  bool flyByWire = false;

};

#endif
