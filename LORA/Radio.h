/**
 * Radio.h holds all declarations and varaibles related to the radio.ccp file.
 */

#ifndef Radio_h
#define Radio_h

#include <Arduino.h>

class RADIO
{
  public:
  
	// Constructor
	RADIO();
  	
	// Returns the transmission's Altitude.
	float getRadioAltitude(char buf[]);
  	
	// Returns the transmission's CR variable.
	float getStartStop(char buf[]);
	
	// Returns the transmission's CS variable.
	float getTargetThrottle(char buf[]);
  	
	// Returns the transmission's craft ID.
	float getCraftID(char buf[]);
  	
	// Returns the transmission's Latitude.
	float getRadioLatitude(char buf[]);
  	
	// Returns the transmission's Longitude.
	float getRadioLongitude(char buf[]);
  	
	// Returns the transmission's Latitude.
	float getLoRaEvent(char buf[]);
	
	// Returns the transmission's time stamp.
	float getTimeStamp(char buf[], int selector);
	
	// Runs initialzation script for the Radio.
	void initialize();

	// Passively watches for incoming radio transmissions from Mission Control and other crafts.
	void manager();
	
	// Receives incoming transmission.
	void radioReceive();
	
	// Responds to the RollCall signal sent from Mission Control.
	void rollCall();
	
	// Sends the desired signal out over the radio antenna.
	void broadcast();

	// Blinks the LED on the LoRa uC to show a signal has been received.
	void blinkLED();

	// Returns craft movement state in string format for UI. 
	String getFunctionalSTATE();

	// Returns craft operational state in string format for UI. 
	String getOpSTATE();

	// Returns craft Rollcall state in string format for UI. 
	String getRCSTATE();
	  
	// Parses and returns the radio Target Latitude.
	float getRadioTargetLat(char buf[]);

	// Parses and returns the radio Target Latitude.
	float getRadioTargetLon(char buf[]);
	

  
	
	// Chip select pin for the radio.
	const byte RFM95_CS = 8;
	
	// Intialization pin for radio.
	const byte RFM95_INT = 7;
	
	// Reset pin onboard the radio.
	const byte RFM95_RST = 4;

	// Craft ID (Used to set start times)
	const byte NODE_ID = 2;
	
	// Radio frequency used throught the Eagle Eye Program. CHECK WITH HABET BEFORE EACH FLIGHT!!!!!
	#define RF95_FREQ 433.0
 	
	// Status of the craft replying to Mission Control with its node #.
	bool checkedIn = false;

	// Holds the ID of the craft that just broadcasted.  
	float receivedID = 0.0;

	// Holds the current received radio signal. 
	String radioInput = "";

	// Holds the current sent radio signal.
	String radioOutput = "";

	// State of Radio program. 
    // ROLLCALL - Currently in RollCall process. 
    // STANDBY  - RollCall completed, waiting for user to send out start signal. 
    // NORMAL   - Radio is running in its normal operation state. 
    enum RadioStatus {NONE, ROLLCALL, STANDBY, NORMAL};
    enum RadioStatus OperationMode = NONE;

    // State of RollCall.
    enum rollCallStatus {NOTSTARTED, RUNNING, COMPLETE};
    enum rollCallStatus RCstate = NOTSTARTED;
  
	// Stores all information related to the network of the Eagle Eye program.
	// This struct reads specific indexes and than rebroadcasts the updated transmission to
	// the other nodes in the network. 
	struct Network_Data {
		
		/**
		 * The first four varaibles are accessed and overseen by the Eagle Eye craft.
		 */
		
		// Each of these is defined in the Data.h struct. Refer to its documentation as needed.
		float L_TS = 0.0;
		float Altitude = 0.0;
		float Latitude = 0.0;
		float Longitude = 0.0;
		float LE = 0.0;
		
		/**
		 * The last 3 variables are overseen by Mission Control.
		 */
		
		// Mission Control's ms Time stamp.
		float MC_TS = 0.0;
		
		// This variable is the on / off switch for the craft as far as operational movement goes.
        // Having this be on the off state (0.0) does not stop data collection, only servo and 
        // motor movement. 
		float StartStop = 0.0;

	    // User inputted target latitude for the craft. 
	    float TargetLat = 0.0;

	    // User inputted target longitude for the craft. 
	    float TargetLon = 0.0;

	    // Holds the craft's target throttle position. This is not what the craft is currently at, 
	    // but what we want the craft's to have its upper limit be. For example, it will not be 
	    // at a constant 40% if we set it to '40.0', but it will be able to iterate up and down from
	    // that percentage of thrust. 
	    float TargetThrottle = 0.0;
    
		/**
		 * This varaible is updated by each craft right before the array is broadcasted.
		 */
		
		// Craft_ID is used to tell which craft is currently broadcasting the signal. This allows
		// for Mission Control to have a sense of if information is being relayed through nodes,
		// or if we have a direct line of communication with each node.
		float Craft_ID = 0.0;
	};
  struct Network_Data Network;

  // Used in the computation of the radio system. 
  unsigned long start = 0;
  
};

#endif

