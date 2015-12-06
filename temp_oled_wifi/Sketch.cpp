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

// change this to match your SD shield or module;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 10;


unsigned char* float_to_inFloat(float );
unsigned char fill_OLED=0x55;


const char fill_string1[] = "temp: ";
const char fill_string2[] = "itemp: ";
const char fill_string3[] = "low: ";
const char fill_string4[] = "max: ";

extern float tempC;// = sensors.getTempC(tempDeviceAddress);
extern float tempF;// = DallasTemperature::toFahrenheit(tempC);

//myI2c oled_screen;
#define gpsTX 7
#define gpsRX 6
SoftwareSerial gpsPort(gpsRX,gpsTX);

//File mySDFile;
//const int SDSelect = 10;

void connectUDP(){
	Serial.println("AT+CIPCLOSE\r\n");
	delay(100);
	Serial.println("AT+CIPSTART=\"UDP\",\"192.168.8.102\",11000");
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
	//Serial.begin(57600);
	//dbg_tx_init();
	
	pinMode(A3, OUTPUT);
	digitalWrite(A3, LOW);
	
	delay(100);
	gpsPort.begin(9600);
	gpsPort.println("begin gps Serial");
	//AT+CIPSTART="UDP","192.168.8.102",110000
	//String connect = "AT+CIPSTART="UDP","192.168.8.102",110000";
	
	delay(100);
	// start serial port
	// serial to be used to communicate with wifi port
	Serial.begin(38400);
	Serial.println("Dallas Temperature IC Control Library Demo");
	
	connectUDP();
	
	Serial.println("AT\r\n");
	if(Serial.find("OK")){
		Serial.println("command worked");
		digitalWrite(A3, HIGH);
	}
	//Serial.println(Serial.read());
	
	
	

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
	
	/*
	Serial.print("Initializing SD card...");
	// On the Ethernet Shield, CS is pin 4. It's set as an output by default.
	// Note that even if it's not used as the CS pin, the hardware SS pin
	// (10 on most Arduino boards, 53 on the Mega) must be left as an output
	// or the SD library functions will not work.
	pinMode(SDSelect, OUTPUT);
	
	if (!SD.begin(10)) {
		Serial.println("initialization failed!");
		return;
	}
	Serial.println("initialization done.");
	
	// open the file. note that only one file can be open at a time,
	// so you have to close this one before opening another.
	mySDFile = SD.open("test.txt", FILE_WRITE);
	
	// if the file opened okay, write to it:
	if (mySDFile) {
		Serial.print("Writing to test.txt...");
		mySDFile.println("testing 1, 2, 3.");
		// close the file:
		mySDFile.close();
		Serial.println("done.");
		} else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}
	*/
}

void sendUDP(){
	Serial.println("AT+CIPSEND=6\r\n");
	if(Serial.find(">")){
		Serial.print(tempF);
		Serial.print("\r\n");
	}
}

void loop() {
	// put your main code here, to run repeatedly:
	
	gpsPort.println("hello");
	Serial.println("AT\r\n");
	

	
	tempSM();
	sendUDP();
	//Serial.print("external tempC:" );
	//Serial.println(tempC);
	
	//Serial.println("");
	char buf[10];
	
	sprintf(buf,"%d",counter);
	setXY(7, 1);
	sendStr(buf);
	
	counter++;
	delay(300);
}




