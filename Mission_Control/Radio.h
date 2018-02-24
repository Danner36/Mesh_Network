/**
 * Radio.h holds all declarations and varaibles related to the radio.ccp file.
 */

#ifndef RADIO_h
#define RADIO_h

#include <Arduino.h>

class RADIO
{
  public:

  //Constructor
  RADIO();
  
  //Returns the transmission's Altitude.
  float getRadioAltitude(uint8_t buf);
    
  //Returns the transmission's CR variable.
  float getCommandReceived(uint8_t buf);
  
  //Returns the transmission's CS variable.
  float getCommandSent(uint8_t buf);
    
  //Returns the transmission's craft ID.
  float getCraftID(uint8_t buf);
    
  //Returns the transmission's Latitude.
  float getRadioLatitude(uint8_t buf);
    
  //Returns the transmission's Longitude.
  float getRadioLongitude(uint8_t buf);
    
  //Returns the transmission's Latitude.
  float getLoRaEvent(uint8_t buf);
  
  //Returns the transmission's Release Status.
  float getReleaseStatus(uint8_t buf);
  
  //Returns the transmission's time stamp.
  float getTimeStamp(uint8_t buf, int selector);
	
  //Runs initialzation script for the Radio.
  void initialize();

  //Passively watches for incoming radio transmissions from Mission Control and other crafts.
  void manager();
  
  //Receives incoming transmission.
  void radioReceive();
  
  //Responds to the RollCall signal sent from Mission Control.
  void rollCall();
  
  //Sends the desired signal out over the radio antenna.
  void broadcast();

  //Blinks the LED on the LoRa uC to show a signal has been received.
  void blinkLED();

  //Compares current node against others. Prevents duplicates. 
  void nodeCheckIn();
	
	
  
  //Chip select pin for the radio.
  const byte RFM95_CS = 8;
  
  //Intialization pin for radio.
  const byte RFM95_INT = 7;
  
  //Reset pin onboard the radio.
  const byte RFM95_RST = 4;

  //Interrupt pin to trigger RollCall.
  const byte interruptPinRollCall = 3;
  
  //Pins used to blink an LED to signal receival packet.
  const byte LED = 13;
	
	//Radio frequency used throught the Eagle Eye Program. CHECK WITH HABET BEFORE EACH FLIGHT!!!!!
	#define RF95_FREQ 433.0
  
  //Holds the ID of the craft that just broadcasted. THIS IS ANOTHER NODE, NOT MISSION CONTROL. 
  float receivedID = 0.0;

  //State of RollCall.
  enum rollCallStatus {NOTSTARTED, RUNNING, COMPLETE};
  enum rollCallStatus RCstate = NOTSTARTED;

  //Holds RCstate's (enum) text value. 
  String RCString = "NONSTARTED";
  
  //List of nodes currently logged into network. 
  // MC - 1
  // EE - 2
  float nodeList[10] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  //State of Radio program. 
  //   ROLLCALL - Currently in RollCall process. 
  //   STANDBY  - RollCall completed, waiting for user to send out start signal. 
  //   NORMAL   - Radio is running in its normal operation state. 
  enum RadioStatus {NONE, ROLLCALL, STANDBY, NORMAL};
  enum RadioStatus OperationMode = NONE;

  //Holds OperationMode's (enum) text value. 
  String OpModeString = "NOTSTARTED";

  //Holds the current received radio signal. 
  String radioInput = "";

  //Holds the current sent radio signal.
  String radioOutput = "";
  
  //Stores all information related to the network of the Eagle Eye program.
	//   This struct reads specific indexes and than rebroadcasts the updated transmission to
	//   the other nodes in the network. 
	struct Network_Data {
		
		/**
		 * The first four varaibles are accessed and overseen by the Eagle Eye craft.
		 */
		
		//Each of these is defined in the Data.h struct. Refer to its documentation as needed.
		float L_TS = 0.0;
		float Altitude = 0.0;
		float Latitude = 0.0;
		float Longitude = 0.0;
		float LE = 0.0;
		
		/**
		 * The below varaible is overseen by HABET_Detach.
		 */
		
		//HABET's ms Time stamp.
		float H_TS = 0.0;
		
		//Release status '0' -> not released, '1' -> released.
		float Release_Status = 0.0;
		
		/**
		 * The last 3 variables are overseen by Mission Control.
		 */
		
		//Mission Control's ms Time stamp.
		float MC_TS = 0.0;
		
		//Command_Sent will be what triggers a command on another craft (Eagle Eye). 
		float Command_Sent = 0.0;
		
		//Command_Received will be turned 1 when the Command_Sent receahes its destination. 
		//   Used as a handhshake, but primary purpose is to be able to verify that an action 
		//   reached its destination via Mission Control.
		float Command_Received = 0.0;
		
		/**
		 * This varaible is updated by each craft right before the array is broadcasted.
		 */
		
		//Craft_ID is used to tell which craft is currently broadcasting the signal. This allows
		//   for Mission Control to have a sense of if information is being relayed through nodes,
		//   or if we have a direct line of communication with each node.
		float Craft_ID = 0.0;
	};
	struct Network_Data Network;

  //Timer is used to for the 10 second interval that the craft will broadcast when in normal. 
  //   operating mode. This value is in milliseconds.  
  unsigned long start = 0;

  //Timer is used to for the 10 second interval that the craft will broadcast on for RollCall. 
  //   This value is in milliseconds.  
  unsigned long RCBroadcast = 0;

};

#endif
