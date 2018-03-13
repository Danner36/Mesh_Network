/**
 * Radio.h holds all declarations and varaibles related to the radio.ccp file.
 */

#ifndef Radio_h
#define Radio_h

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
	float getCraftID(char buf[]);
  	
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
	
	
	
	
	//Chip select pin for the radio.
	const byte RFM95_CS = 8;
	
	//Intialization pin for radio.
	const byte RFM95_INT = 7;
	
	//Reset pin onboard the radio.
	const byte RFM95_RST = 4;
	
	//Radio frequency used throught the Eagle Eye Program. CHECK WITH HABET BEFORE EACH FLIGHT!!!!!
	#define RF95_FREQ 433.0
 	
	//Status of the craft replying to Mission Control with its node #.
	bool checkedIn = false;

  //Status of Start singal. True is recevied. False if not. 
  bool startSignal = false;

  //Holds the ID of the craft that just broadcasted.  
  float receivedID = 0.0;

	
	//Stores all information related to the network of the Eagle Eye program.
	//   This struct reads specific indexes and than rebroadcasts the updated transmission to
	//   the other nodes in the network. 
	struct Network_Data {
		
		/**
		 * The first four varaibles are accessed and overseen by the Eagle Eye craft.
		 */
		
		//Each of these is defined in the Data.h struct. Refer to its documentation as needed.
		float L_TS = 0.0;
		float Altitude = 20000.0;
		float Latitude = -43.123456;
		float Longitude = 93.123456;
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

  //Used in the computation of the radio system. 
  unsigned int start = 0;
  
};

#endif
