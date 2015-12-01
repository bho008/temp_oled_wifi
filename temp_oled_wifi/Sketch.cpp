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
#include <SD.h>
#include <SPI.h>

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

	
	tempSM();
	
	//Serial.println("");
	char buf[10];
	
	sprintf(buf,"%d",counter);
	setXY(7, 1);
	sendStr(buf);
	
	counter++;
	delay(1000);
}




