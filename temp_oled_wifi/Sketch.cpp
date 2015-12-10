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

#define button_temp_change 5

void sendUDP();

Scheduler runner;

//Tick functions
void TickFct1();
void TickFct_OLED_output();
void TickFct_buttons();
void TickFct_time();
void TickFct_gps();
void TickFct_UDP();
void TickFct_Temp();

//Tasks
Task t1(1000, TASK_FOREVER, &TickFct1, &runner, true);
Task t2(200, TASK_FOREVER, &TickFct_OLED_output, &runner, true);
Task t3(10, TASK_FOREVER, &TickFct_buttons, &runner, true);
Task t4(1000, TASK_FOREVER, &TickFct_time, &runner, true);
Task t5(1000, TASK_FOREVER, &TickFct_gps, &runner, true);
Task t6(1000, TASK_FOREVER, &TickFct_UDP, &runner, true);
Task t7(1000, TASK_FOREVER, &TickFct_Temp, &runner, true);


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


enum TickFct_OLED_output_states{oled_wait, oled_display_temp_template, oled_display_title, oled_display_temp_f, oled_display_temp_c}TickFct_OLED_output_state;
void TickFct_OLED_output(){
	switch(TickFct_OLED_output_state){
		case oled_wait:
		TickFct_OLED_output_state = oled_display_temp_template;
		break;
		
		case oled_display_temp_template:
		setXY(1,1);
		sendStr(fill_string1);
		setXY(2,1);
		sendStr(fill_string2);

		setXY(4, 1);
		sendStr(fill_string3);
		setXY(5, 1);
		sendStr(fill_string4);
		TickFct_OLED_output_state = oled_display_temp_f;
		break;
		
		case oled_display_temp_f:
		setXY(1, 7);

		tempF_uchar = float_to_uChar(tempF);
		uchar[10];
		for(unsigned int i = 0; i < 7; i++){
			uchar[i] = (unsigned char)tempF_uchar[i];
			if(uchar[i] > 57)
			uchar[i] = 0;
		}
		sendStr(uchar);  //print current temp

		if(low_temp > tempF || low_temp == 0){
			low_temp = tempF;
			setXY(4, 6);
			sendStr(uchar); //print lowest temp
		}
		if(max_temp < tempF){
			max_temp = tempF;
			setXY(5, 6);
			sendStr(uchar); //print highest temp
		}
		
		break;
		
		case oled_display_temp_c:
				setXY(1, 7);

		tempF_uchar = float_to_uChar(tempC);
		uchar[10];
		for(unsigned int i = 0; i < 7; i++){
			uchar[i] = (unsigned char)tempF_uchar[i];
			if(uchar[i] > 57)
			uchar[i] = 0;
		}
		sendStr(uchar);  //print current temp

		if(low_temp > tempF || low_temp == 0){
			low_temp = tempF;
			setXY(4, 6);
			sendStr(uchar); //print lowest temp
		}
		if(max_temp < tempF){
			max_temp = tempF;
			setXY(5, 6);
			sendStr(uchar); //print highest temp
		}
		break;
		
		
		
		default:
		TickFct_OLED_output_state = oled_wait;
		break;
	}
}

enum time_states{oled_time_since_on}time_state;
void TickFct_time(){
	switch(time_state){
		case oled_time_since_on:
		char buf[10];
		
		sprintf(buf,"%d",counter);
		setXY(7, 1);
		sendStr(buf);
		
		counter++;
		break;
		
		default:
		time_state = oled_time_since_on;
		break;
	}
}

int button1 = 0;
enum buttons_states{wait_buttons, change_temp_display, still_pressed}buttons_state;
void TickFct_buttons(){
	button1 = !digitalRead(button_temp_change);
	switch(buttons_state){
		case wait_buttons:
		
		if(button1)
		buttons_state = change_temp_display;
		break;
		
		case change_temp_display:
		if(TickFct_OLED_output_state == oled_display_temp_c)
		TickFct_OLED_output_state = oled_display_temp_f;
		else
		TickFct_OLED_output_state = oled_display_temp_c;
		
		if(button1)
		buttons_state = still_pressed;
		else
		buttons_state = wait_buttons;
		break;
		
		case still_pressed:
		if(!button1)
		buttons_state = wait_buttons;
		
				digitalWrite(2, HIGH);

		break;
		default:
		buttons_state = wait_buttons;
		break;
	}
}

int led3_output = 0;
void TickFct_gps(){
	while (gpsPort.available() > 0)
	gps.encode(gpsPort.read());
	setXY(7, 5);
	char satval[10];
	sendStr(itoa(gps.satellites.value(), satval,10));
	setXY(7, 7);
	sendStr(itoa(gps.time.second(), satval, 10));
	if(gps.satellites.value() > 4){
		if(led3_output)
			led3_output = 0;
		else
			led3_output = 1;
			
		digitalWrite(3, led3_output);
	}
}

void TickFct_UDP(){
	sendUDP();
}

void TickFct_Temp(){
	tempSM();
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
	pinMode(button_temp_change, INPUT);
	digitalWrite(button_temp_change, HIGH);
	pinMode(3, OUTPUT);
	digitalWrite(3, LOW);
	
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

	/*
	setXY(1,1);
	sendStr(fill_string1);
	setXY(2,1);
	sendStr(fill_string2);

	setXY(4, 1);
	sendStr(fill_string3);
	setXY(5, 1);
	sendStr(fill_string4);
	*/
	runner.init();
	runner.addTask(t1);
	runner.addTask(t2);
	runner.addTask(t3);
	runner.addTask(t4);
	runner.addTask(t5);
	runner.addTask(t6);
	runner.addTask(t7);
	
	t1.enable();
	t2.enable();
	t3.enable();
	t4.enable();
	t5.enable();
	t6.enable();
	t7.enable();
	
	//t1.setInterval(100);
	//delay(10);
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
	
	
	//sendUDP();

	/*
	while (gpsPort.available() > 0)
	if (gps.encode(gpsPort.read()))
	//displayInfo();

	if (millis() > 5000 && gps.charsProcessed() < 10)
	{
		Serial.println(F("No GPS detected: check wiring."));
		while(true);
	}
	*/
	
	/*
	char buf[10];
	
	sprintf(buf,"%d",counter);
	setXY(7, 1);
	sendStr(buf);
	
	counter++;
	*/
	//delay(300);
}




