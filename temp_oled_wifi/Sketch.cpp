/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <stdint.h>

#include "config.h"
#include <avr/io.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdio.h>
#include <stdlib.h>
#include "SoftwareSerial.h"
//#include "dbg_putchar.h"
#include "myI2C.h"
//#include "delay.h"
#define F_CPU 8000000
//#include "data.c"
//#include "oled_setup.h"

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void setup();
void loop();
//End of Auto generated function prototypes by Atmel Studio


// to be put into a function -----------------------

unsigned char* float_to_uChar(float);


unsigned char* float_to_inFloat(float );
unsigned char fill_OLED=0x55;


const char fill_string1[] = "temp: ";
const char fill_string2[] = "itemp: ";
const char fill_string3[] = "low: ";
const char fill_string4[] = "max: ";

float max_temp = 0;
float low_temp = 0;
int currTime = 0;
uint8_t counter = 0;

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 9
#define TEMPERATURE_PRECISION 9
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
//

//myI2c oled_screen;
#define wifiTX 7
#define wifiRX 6
SoftwareSerial wifiPort(wifiRX,wifiTX);

void setup() {
	// put your setup code here, to run once:
	//Serial.begin(57600);
	//dbg_tx_init();
	
	delay(100);
	wifiPort.begin(38400);
	wifiPort.println("begin wifiport Serial");
	delay(100);
	// start serial port
	Serial.begin(38400);
	Serial.println("Dallas Temperature IC Control Library Demo");
	
	

	//  Wire.begin();
	i2c_init();
	init_OLED();
	delay(10);
	clear_display();
	delay(50);

	sendcommand(0x20);            //Set Memory Addressing Mode
	sendcommand(0x02);            //Set Memory Addressing Mode ab Page addressing mode(RESET)

	sendcommand(0xa6);            //Set Normal Display (default)


	setXY(1,1);
	sendStr(fill_string1);
	setXY(2,1);
	sendStr(fill_string2);

	setXY(4, 1);
	sendStr(fill_string3);
	setXY(5, 1);
	sendStr(fill_string4);
	
	delay(10);
	//dbg_putchar('a');
}

void loop() {
	// put your main code here, to run repeatedly:
	
				wifiPort.println("hello");

	
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
			Serial.print(" #");
			//Serial.print(i,DEC);
			//Serial.print("=");


			float tempC = sensors.getTempC(tempDeviceAddress);
			float tempF = DallasTemperature::toFahrenheit(tempC);
			//Serial.print(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
			setXY(1, 7);
			unsigned char* tempF_uchar;
			tempF_uchar = float_to_uChar(tempF);
			char uchar[10];
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
	
	//Serial.println("");
	char buf[10];
	
	sprintf(buf,"%d",counter);
	setXY(7, 1);
	sendStr(buf);
	
	counter++;
	delay(1000);
}



unsigned char* float_to_uChar(float inFloat){
	unsigned char buf[10];
	unsigned char temp = 0;
	float temp_inFloat = inFloat;
	int i = 0;
	if(inFloat / 100 >= 1){
		temp = 0;
		while(inFloat > 100){
			inFloat-= 100;
			temp++;
		}
		buf[i] = temp + 48;
		i++;
	}
	if(inFloat / 10 >= 1){
		temp = 0;
		while(inFloat >= 10){
			inFloat-= 10;
			temp++;
		}
		buf[i] = temp+48;
		i++;
	}
	else{
		buf[i] = 48;
		i++;
	}
	if(inFloat >= 0){
		temp = 0;
		while(inFloat >= 1){
			inFloat--;
			temp++;
		}
		buf[i] = temp + 48;
		i++;
	}
	
	buf[i] = '.';
	i++;
	
	if(inFloat >= 0.1){
		temp = 0;
		while(inFloat >= 0.1){
			inFloat -= 0.1;
			temp+= 1;
		}
		buf[i] = temp + 48;
		i++;
	}
	else {
		buf[i] = '0';
		i++;
	}
	temp = 0;
	if(inFloat >= 0.01){
		while(inFloat >= 0.01){
			inFloat -= 0.01;
			temp++;
		}
		buf[i] = temp+48;
		i++;

	}
	if(temp_inFloat < 100.00)
	buf[5] = 0;

	delay(1);

	return buf;
}

