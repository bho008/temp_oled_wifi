/*
* Temp_SM.h
*
* Created: 11/30/2015 11:14:09 PM
*  Author: brian
*/


#ifndef TEMP_SM_H_
#define TEMP_SM_H_

#include "float_to_uchar.h"

float max_temp = 0;
float low_temp = 0;
int currTime = 0;

 float tempC = 0;// = sensors.getTempC(tempDeviceAddress);
 float tempF = 0;
int counter = 0;

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 9
#define TEMPERATURE_PRECISION 9
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
//

unsigned char* tempF_uchar;
char uchar[10];

void tempSM(){
	#ifdef BUSFAIL
	Serial.print(" Test:");

	if (sensors.reset()) {
		
		Serial.print("good");
		
		} else {
		
		if (sensors.busFail()) {
			
			Serial.print("fail");
			
			} else {
			
			Serial.print("empty");
			
		}
		
	}

	#endif

	int numberOfDevices; // Number of temperature devices found

	DeviceAddress tempDeviceAddress; // We'll use this variable to store a found device address

	// For testing purposes, reset the bus every loop so we can see if any devices appear or fall off
	sensors.begin();

	// Grab a count of devices on the wire
	numberOfDevices = sensors.getDeviceCount();

	//Serial.print(" Parasite:");
	if (sensors.isParasitePowerMode()) Serial.print("ON ");
	else //Serial.print("OFF ");

	//Serial.print("Count:");
	//Serial.print(numberOfDevices, DEC);
	// report parasite power requirements

	sensors.requestTemperatures(); // Send the command to get temperatures

	// Loop through each device, print out temperature data
	for(int i=0;i<numberOfDevices; i++)
	{
		// Search the wire for address
		if(sensors.getAddress(tempDeviceAddress, i))
		{
			// Output the device ID
			//Serial.print(" #");
			//Serial.print(i,DEC);
			//Serial.print("=");


			 tempC = sensors.getTempC(tempDeviceAddress);
			 tempF = DallasTemperature::toFahrenheit(tempC);
			//Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
			setXY(1, 7);
			
			tempF_uchar = float_to_uChar(tempF);
			uchar[10];
			for(unsigned int i = 0; i < 7; i++){
				uchar[i] = (unsigned char)tempF_uchar[i];
				if(uchar[i] > 57)
				uchar[i] = 0;
			}

			sendStr(uchar);

			if(low_temp > tempF || low_temp == 0){
				low_temp = tempF;
				setXY(4, 6);
				sendStr(uchar);
			}
			if(max_temp < tempF){
				max_temp = tempF;
				setXY(5, 6);
				sendStr(uchar);
			}

			


		}
		//else ghost device! Check your power requirements and cabling
		
	}

}

#endif /* TEMP_SM_H_ */