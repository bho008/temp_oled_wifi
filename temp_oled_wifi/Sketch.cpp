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
#include "Temp_SM.h"
//#include <SD.h>
//#include <SPI.h>
//#include <Fat16.h>

#include <TinyGPS++.h>
#include <TaskScheduler.h>


//xm37-1612

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void setup();
void loop();
//End of Auto generated function prototypes by Atmel Studio


// to be put into a function -----------------------

// set up variables using the SD utility library functions:
//Sd2Card card;
//SdVolume volume;
//SdFile root;

//const uint8_t CHIP_SELECT = SS;
//SdCard card;
//Fat16 file;

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
//const int chipSelect = 10;


unsigned char* float_to_inFloat(float );
unsigned char fill_OLED=0x55;


const char fill_string1[] = "temp: ";
const char fill_string2[] = "itemp: ";
const char fill_string3[] = "low: ";
const char fill_string4[] = "max: ";

extern float tempC;// = sensors.getTempC(tempDeviceAddress);
extern float tempF;// = DallasTemperature::toFahrenheit(tempC);

extern unsigned char* tempF_uchar;
extern char uchar[10];


//myI2c oled_screen;

TinyGPSPlus gps;
#define gpsTX 7
#define gpsRX 6
SoftwareSerial gpsPort(gpsRX,gpsTX);


Scheduler runner;

//Tick functions
void TickFct1();
void TickFct_OLED_output();

//Tasks
Task t1(300, TASK_FOREVER, &TickFct1, &runner, true);
Task t2(200, TASK_FOREVER, &TickFct_OLED_output, &runner, true);


int testOutput = 0;
enum TickFct1_states{wait_TickFct1, blink_TickFct1}TickFct1_state;
void TickFct1(){
	switch(TickFct1_state){
		case wait_TickFct1:
			digitalWrite(2, HIGH);
						TickFct1_state = blink_TickFct1;

			break;
			
		case blink_TickFct1:
		digitalWrite(2, LOW);
					TickFct1_state = wait_TickFct1;

		break;
			
		default:
			TickFct1_state = wait_TickFct1;
			break;
	}
}

enum TickFct_OLED_output_states{}TickFct_OLED_output_state;
void TickFct_OLED_output(){
	
}

void displayInfo()
{
	Serial.print(F("Location: "));
	if (gps.location.isValid())
	{
		Serial.print(gps.location.lat(), 6);
		Serial.print(F(","));
		Serial.print(gps.location.lng(), 6);
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.print(F("  Date/Time: "));
	if (gps.date.isValid())
	{
		Serial.print(gps.date.month());
		Serial.print(F("/"));
		Serial.print(gps.date.day());
		Serial.print(F("/"));
		Serial.print(gps.date.year());
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.print(F(" "));
	if (gps.time.isValid())
	{
		if (gps.time.hour() < 10) Serial.print(F("0"));
		Serial.print(gps.time.hour());
		Serial.print(F(":"));
		if (gps.time.minute() < 10) Serial.print(F("0"));
		Serial.print(gps.time.minute());
		Serial.print(F(":"));
		if (gps.time.second() < 10) Serial.print(F("0"));
		Serial.print(gps.time.second());
		Serial.print(F("."));
		if (gps.time.centisecond() < 10) Serial.print(F("0"));
		Serial.print(gps.time.centisecond());
	}
	else
	{
		Serial.print(F("INVALID"));
	}

	Serial.println();
}


void connectUDP(){
	Serial.println("AT+CIPCLOSE\r\n");
	delay(100);
	Serial.println("AT+CIPSTART=\"UDP\",\"192.168.8.255\",11000");
	delay(100);
	if(Serial.find("OK")){
		//connectUDP();
		digitalWrite(A3, HIGH);
		delay(500);
		digitalWrite(A3, LOW);
		delay(500);
		digitalWrite(A3, HIGH);
	}
	else
	connectUDP();
}


void setup() {
	// put your setup code here, to run once:
	
	pinMode(A3, OUTPUT);
	digitalWrite(A3, LOW);
	pinMode(2, OUTPUT);
	digitalWrite(2, HIGH);
	
	delay(100);
	gpsPort.begin(9600);
	gpsPort.println("begin gps Serial");
	
	delay(100);

	Serial.begin(38400);
	
	connectUDP();

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
}

char *empty = "                      ";
void sendUDP(){
	Serial.println("AT+CIPSEND=32\r\n");
	//delay(10);
	if(Serial.find(">")){
		Serial.print("#0=");
		Serial.print(tempF);
		Serial.print(",");
		Serial.print(gps.location.lat(),6);
		Serial.print(",");
		Serial.print(gps.location.lng(),6);
		Serial.print(";");
		Serial.print(empty);
		
		Serial.println("\r\n");
		
		
	}
	else if(Serial.find("link is not valid")){
		connectUDP();
	}
}

char* id = "#0=";
char buffer_32[32];


void sendUDP_buffer(){
	Serial.println("AT+CIPSEND=32\r\n");
	if(Serial.find(">")){
		//Serial.print(buffer_32);
		for(int i = 0; i < 32; i++){
			Serial.print(buffer_32[i]);
		}
		Serial.println("\r\n");
	}
	else if(Serial.find("link is not valid")){
		connectUDP();
	}
}


void loop() {
	// put your main code here, to run repeatedly:

	 runner.execute();
	tempSM();
	
	
	sendUDP();

	
	while (gpsPort.available() > 0)
	if (gps.encode(gpsPort.read()))
	//displayInfo();

	if (millis() > 5000 && gps.charsProcessed() < 10)
	{
		Serial.println(F("No GPS detected: check wiring."));
		while(true);
	}
	
	char buf[10];
	
	sprintf(buf,"%d",counter);
	setXY(7, 1);
	sendStr(buf);
	
	counter++;
	delay(300);
}




