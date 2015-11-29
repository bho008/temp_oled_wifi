/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include "config.h"
#include <avr/io.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <stdio.h>
#include <stdlib.h>
//#include "myI2C.h"
#define F_CPU 10000000
//#include "data.c"
//#include "oled_setup.h"

/*End of auto generated code by Atmel studio */


//Beginning of Auto generated function prototypes by Atmel Studio
void setup();
void loop();
//End of Auto generated function prototypes by Atmel Studio


// to be put into a function -----------------------
//========================
unsigned char myFont[][8]={
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
	{0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
	{0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
	{0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
	{0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
	{0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
	{0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
	{0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
	{0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
	{0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
	{0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
	{0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
	{0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
	{0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
	{0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
	{0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
	{0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
	{0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
	{0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
	{0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
	{0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
	{0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
	{0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
	{0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
	{0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
	{0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
	{0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
	{0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
	{0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
	{0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
	{0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
	{0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
	{0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
	{0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
	{0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
	{0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
	{0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
	{0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
	{0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
	{0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
	{0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
	{0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
	{0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
	{0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
	{0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
	{0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
	{0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
	{0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
	{0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
	{0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
	{0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
	{0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
	{0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
	{0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
	{0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
	{0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
	{0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
	{0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
	{0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
	{0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
	{0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
	{0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
	{0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
	{0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
	{0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
	{0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
	{0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
	{0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
	{0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
	{0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
	{0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
	{0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
	{0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
	{0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
	{0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
	{0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
	{0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
	{0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
	{0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00}
};


void i2c_OLED_send_cmd(uint8_t);
void sendcommand(unsigned char);
void clear_display(void);
void SendChar(unsigned char);
void setXY(unsigned char row,unsigned char col);
void sendStr( const char *string);
void init_OLED(void);
void i2c_init();
void i2c_OLED_init(void);
void i2c_OLED_send_byte(uint8_t);
void waitTransmissionI2C();

unsigned char* float_to_uChar(float);


unsigned char* float_to_inFloat(float );
unsigned char fill_OLED=0x55;


const char fill_string1[] = "temp: ";
const char fill_string2[] = "itemp: ";
const char fill_string3[] = "low: ";
const char fill_string4[] = "max: ";
//extern unsigned char myFont[][8];
//extern unsigned char logo[];
//extern unsigned char ip[];

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

void setup() {
  // put your setup code here, to run once:
	digitalWrite( 8 , LOW );
	pinMode( 8  , OUTPUT );
	digitalWrite( 10 , LOW );
	pinMode( 10 , OUTPUT );
	
	// start serial port
	Serial.begin(115200);
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
	
}

void loop() {
  // put your main code here, to run repeatedly:
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




//==========================================================//
void print_a_char(unsigned char ascii=0)
{
  unsigned char i=0;
  for(i=0;i<8;i++)
  {
    SendChar(myFont[ascii-0x20][i]);
  }
}

//==========================================================//
void sendcommand(unsigned char com)
{
  i2c_OLED_send_cmd(com);  
  /*
  Wire.beginTransmission(OLED_address);     //begin transmitting
  Wire.write(0x80);                          //command mode
  Wire.write(com);
  Wire.endTransmission();                    // stop transmitting
  */
}

//==========================================================//
void clear_display(void)
{
  unsigned char i,k;
  for(k=0;k<8;k++)
  {  
    setXY(k,0);    
    {
      for(i=0;i<128;i++)     //clear all COL
      {
        SendChar(0);         //clear all COL
        //delay(10);
      }
    }
  }
}

//==========================================================//
void SendChar(unsigned char data)
{
  i2c_OLED_send_byte(data);
  /*
  Wire.beginTransmission(OLED_address); // begin transmitting
  Wire.write(0x40);//data mode
  Wire.write(data);
  Wire.endTransmission();    // stop transmitting
  */
}

//==========================================================//
void setXY(unsigned char row,unsigned char col)
{
  sendcommand(0xb0+row);                //set page address
  sendcommand(0x00+(8*col&0x0f));       //set low col address
  sendcommand(0x10+((8*col>>4)&0x0f));  //set high col address
}


//==========================================================//
void sendStr(const char *string)
{
  unsigned char i=0;
  //setXY(0,0);    
  while(*string)
  {
    for(i=0;i<8;i++)
    {
      SendChar(myFont[*string-0x20][i]);

      // SendChar(*string);
      delay(10);
    }
    *string++;
  }
}

//==========================================================//
void init_OLED(void)
{
i2c_OLED_init();

}

void  i2c_OLED_init(void){
  i2c_OLED_send_cmd(0xae);    //display off
  i2c_OLED_send_cmd(0x2e);    //deactivate scrolling
  i2c_OLED_send_cmd(0xa4);          //SET All pixels OFF
//  i2c_OLED_send_cmd(0xa5);            //SET ALL pixels ON
  delay(50);
  i2c_OLED_send_cmd(0x20);            //Set Memory Addressing Mode
  i2c_OLED_send_cmd(0x02);            //Set Memory Addressing Mode to Page addressing mode(RESET)
//  i2c_OLED_send_cmd(0xa0);      //colum address 0 mapped to SEG0 (POR)*** wires at bottom
  i2c_OLED_send_cmd(0xa1);    //colum address 127 mapped to SEG0 (POR) ** wires at top of board
//  i2c_OLED_send_cmd(0xC0);            // Scan from Right to Left (POR)         *** wires at bottom
  i2c_OLED_send_cmd(0xC8);          // Scan from Left to Right               ** wires at top
  i2c_OLED_send_cmd(0xa6);            // Set WHITE chars on BLACK backround

//  i2c_OLED_send_cmd(0xa7);            // Set BLACK chars on WHITE backround
  i2c_OLED_send_cmd(0x81);            // 81 Setup CONTRAST CONTROL, following byte is the contrast Value
  i2c_OLED_send_cmd(0xff);            // af contrast value between 1 ( == dull) to 256 ( == bright)
  delay(20);
  i2c_OLED_send_cmd(0xaf);          //display on
  delay(20);
}


// ************************************************************************************************************
// I2C general functions
// ************************************************************************************************************

static uint32_t neutralizeTime = 0;
static int16_t  i2c_errors_count = 0;

#define I2C_SPEED 100000L     //100kHz normal mode, this value must be used for a genuine WMP

#define I2C_PULLUPS_ENABLE         PORTC |= 1<<4; PORTC |= 1<<5;   // PIN A4&A5 (SDA&SCL)
#define I2C_PULLUPS_DISABLE        PORTC &= ~(1<<4); PORTC &= ~(1<<5);

void i2c_init(void) {
  #if defined(INTERNAL_I2C_PULLUPS)
    I2C_PULLUPS_ENABLE
  #else
    I2C_PULLUPS_DISABLE
  #endif
  TWSR = 0;                                    // no prescaler => prescaler = 1
  TWBR = ((F_CPU / I2C_SPEED) - 16) / 2;   // change the I2C clock rate
  TWCR = 1<<TWEN;                              // enable twi module, no interrupt
}

void i2c_rep_start(uint8_t address) {
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN) ; // send REPEAT START condition
  waitTransmissionI2C();                       // wait until transmission completed
  TWDR = address;                              // send device address
  TWCR = (1<<TWINT) | (1<<TWEN);
  waitTransmissionI2C();                       // wail until transmission completed
}

void i2c_stop(void) {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
  //  while(TWCR & (1<<TWSTO));                // <- can produce a blocking state with some WMP clones
}

void i2c_write(uint8_t data ) { 
  TWDR = data;                                 // send data to the previously addressed device
  TWCR = (1<<TWINT) | (1<<TWEN);
  waitTransmissionI2C();
}

uint8_t i2c_read(uint8_t ack) {
  TWCR = (1<<TWINT) | (1<<TWEN) | (ack? (1<<TWEA) : 0);
  waitTransmissionI2C();
  uint8_t r = TWDR;
  if (!ack) i2c_stop();
  return r;
}

uint8_t i2c_readAck() {
  return i2c_read(1);
}

uint8_t i2c_readNak(void) {
  return i2c_read(0);
}

void waitTransmissionI2C() {
  uint16_t count = 255;
  while (!(TWCR & (1<<TWINT))) {
    count--;
    if (count==0) {              //we are in a blocking state => we don't insist
      TWCR = 0;                  //and we force a reset on TWINT register
      neutralizeTime = micros(); //we take a timestamp here to neutralize the value during a short delay
      i2c_errors_count++;
      break;
    }
  }
}

size_t i2c_read_to_buf(uint8_t add, void *buf, size_t size) {
  i2c_rep_start((add<<1) | 1);  // I2C read direction
  size_t bytes_read = 0;
  uint8_t *b = (uint8_t*)buf;
  while (size--) {
    /* acknowledge all but the final byte */
    *b++ = i2c_read(size > 0);
    /* TODO catch I2C errors here and abort */
    bytes_read++;
  }
  return bytes_read;
}

size_t i2c_read_reg_to_buf(uint8_t add, uint8_t reg, void *buf, size_t size) {
  i2c_rep_start(add<<1); // I2C write direction
  i2c_write(reg);        // register selection
  return i2c_read_to_buf(add, buf, size);
}

/* transform a series of bytes from big endian to little
   endian and vice versa. */
void swap_endianness(void *buf, size_t size) {
  /* we swap in-place, so we only have to
  * place _one_ element on a temporary tray
  */
  uint8_t tray;
  uint8_t *from;
  uint8_t *to;
  /* keep swapping until the pointers have assed each other */
  for (from = (uint8_t*)buf, to = &from[size-1]; from < to; from++, to--) {
    tray = *from;
    *from = *to;
    *to = tray;
  }
}

void i2c_writeReg(uint8_t add, uint8_t reg, uint8_t val) {
  i2c_rep_start(add<<1); // I2C write direction
  i2c_write(reg);        // register selection
  i2c_write(val);        // value to write in register
  i2c_stop();
}


void i2c_OLED_send_cmd(uint8_t command) {
  TWBR = ((F_CPU / 400000L) - 16) / 2; // change the I2C clock rate
  i2c_writeReg(OLED_address, 0x80, (uint8_t)command);
}

void i2c_OLED_send_byte(uint8_t val) {
  TWBR = ((F_CPU / 400000L) - 16) / 2; // change the I2C clock rate
  i2c_writeReg(OLED_address, 0x40, (uint8_t)val);
}


unsigned char* float_to_uChar(float inFloat){
  unsigned char buf[10];
  unsigned char temp = 0;
  float temp_inFloat = inFloat;
  int i = 0;
  //for(unsigned i = 0; i < 4; i++){
  if(inFloat / 100 >= 1){
    temp = 0;
    while(inFloat > 100){
      inFloat-= 100;
      temp++;
    }
    buf[i] = temp + 48;
    i++;
    //Serial.print("buf[0]: ");
    //Serial.print(buf[0]);
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
                    //Serial.print("inFloat: ");
                    //Serial.print(inFloat);
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
    //Serial.print("inFloat: ");
    //Serial.print(inFloat);
  }
  if(temp_inFloat < 100.00)
    buf[5] = 0;

  delay(1);
    /*
  for(unsigned i=0; i < 6; i++){
    Serial.print(" ");
    Serial.print(buf[i]);
    Serial.print(" ");
  }
  */
  return buf;
}