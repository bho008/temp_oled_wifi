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
#define button_title 8
#define light_sensor A0
int light_reading = 0;
void sendUDP();

uint8_t padding = 0;

Scheduler runner;

//Tick functions
void TickFct1();
void TickFct_OLED_output();
void TickFct_buttons();
void TickFct_time();
void TickFct_gps();
void TickFct_UDP();
void TickFct_Temp();
void TickFct_light();

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

uint8_t switched_temp = 0;
enum TickFct_OLED_output_states{oled_display_title, oled_wait, oled_display_temp_template,  oled_display_temp_f, oled_display_temp_c}TickFct_OLED_output_state;
void TickFct_OLED_output(){
	switch(TickFct_OLED_output_state){
		case oled_wait:
		break;
		
		case oled_display_temp_template:
		setXY(1,1);
		sendStr("  Fahrenheit");
		setXY(2,1);
		sendStr(fill_string1);

		setXY(4, 1);
		sendStr(fill_string3);
		setXY(5, 1);
		sendStr(fill_string4);
		TickFct_OLED_output_state = oled_display_temp_f;
		break;
		
		case oled_display_temp_f:
		setXY(2, 7);

		tempF_uchar = float_to_uChar(tempF);
		uchar[10];
		for(unsigned int i = 0; i < 7; i++){
			uchar[i] = (unsigned char)tempF_uchar[i];
			if(uchar[i] > 57)
			uchar[i] = 0;
		}
		sendStr(uchar);  //print current temp

		if(low_temp > tempF || low_temp == 0 || switched_temp){
			low_temp = tempF;
			setXY(4, 6);
			sendStr(uchar); //print lowest temp
		}
		if(max_temp < tempF || switched_temp){
			max_temp = tempF;
			setXY(5, 6);
			sendStr(uchar); //print highest temp
		}
		switched_temp = 0;
		break;
		
		case oled_display_temp_c:
		setXY(2, 7);

		tempF_uchar = float_to_uChar(tempC);
		uchar[10];
		for(unsigned int i = 0; i < 7; i++){
			uchar[i] = (unsigned char)tempF_uchar[i];
			if(uchar[i] > 57)
			uchar[i] = 0;
		}
		sendStr(uchar);  //print current temp

		if(low_temp > tempF || low_temp == 0 || switched_temp){
			low_temp = tempF;
			setXY(4, 6);
			sendStr(uchar); //print lowest temp
		}
		if(max_temp < tempF || switched_temp){
			max_temp = tempF;
			setXY(5, 6);
			sendStr(uchar); //print highest temp
		}
		switched_temp = 0;
		break;
		
		case oled_display_title:
		clear_display();
		setXY(1, 1);
		sendStr(" UCR CS 122A");
		//sendStr("UCR CS 122A\nFall 2015\nBrian Ho\n(Stephanie Tong)\nP.O.T.A.T.O.");
		setXY(2,1);
		sendStr("  Fall 2015");
		setXY(3,1);
		sendStr("   Brian Ho");
		setXY(4,1);
		sendStr("(Stephanie");
		setXY(5,1);
		sendStr("        Tong)");
		setXY(6,1);
		sendStr(" P.O.T.A.T.O.");
		TickFct_OLED_output_state = oled_wait;
		break;
		
		default:
		TickFct_OLED_output_state = oled_display_title;
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
		if(counter == 10){
			padding++;
		}
		else if(counter == 100){
			padding++;
		}
		else if(counter == 1000){
			padding++;
		}
		break;
		
		default:
		time_state = oled_time_since_on;
		break;
	}
}

int button1 = 0;
int button2 = 0;
enum buttons_states{wait_buttons, change_temp_display, still_pressed, change_title_display}buttons_state;
void TickFct_buttons(){
	button1 = !digitalRead(button_temp_change);
	button2 = !digitalRead(button_title);
	switch(buttons_state){
		case wait_buttons:
		//switched_temp = 0;
		if(button1 && !(TickFct_OLED_output_state == oled_wait))
		buttons_state = change_temp_display;
		
		if(button2){
			buttons_state = change_title_display;
		}
		break;
		
		case change_title_display:
		if(TickFct_OLED_output_state == oled_wait){
			TickFct_OLED_output_state = oled_display_temp_template;
			switched_temp = 1;

			clear_display();
		}
		else{
			TickFct_OLED_output_state = oled_display_title;
			clear_display();
		}
		if(button2){
			buttons_state = still_pressed;
		}
		else{
			buttons_state = wait_buttons;

		}
		
		break;
		case change_temp_display:
		switched_temp = 1;

		if(TickFct_OLED_output_state == oled_display_temp_c){
			TickFct_OLED_output_state = oled_display_temp_f;
			setXY(1,1);
			sendStr("  Fahrenheit");
		}
		else{
			setXY(1,1);
			sendStr("              ");
			setXY(1,1);

			sendStr("   Celcius");
			TickFct_OLED_output_state = oled_display_temp_c;
		}
		
		if(button1)
		buttons_state = still_pressed;
		else{
			buttons_state = wait_buttons;

		}
		break;
		
		case still_pressed:
		if(!button1)
		buttons_state = wait_buttons;
		
		digitalWrite(2, HIGH);
		if(!button2){
			buttons_state = wait_buttons;
		}

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
	setXY(7, 13);
	char satval[10];
	sendStr(itoa(gps.satellites.value(), satval,8));
	/*
	char timeval[10];
	if(gps.time.second() < 9){
	setXY(7, 9);
	sendStr("0");
	setXY(7,10);
	}
	else
	setXY(7, 9);
	sendStr(itoa(gps.time.second(), timeval, 8));
	*/
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
	setXY(7, 6);
	//sendStr("      ");
	light_reading = analogRead(light_sensor);
	
	if(light_reading < 1000){
		setXY(7, 9);
		sendStr(" ");
	}

	char lightBuff[8];
		setXY(7, 6);

	sendStr(itoa(light_reading, lightBuff, 10));
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
	
	pinMode(button_title, INPUT);
	digitalWrite(button_title, HIGH);
	
	//initialize light sensor
	pinMode(light_sensor, INPUT);
	
	
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




