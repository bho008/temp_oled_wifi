#ifndef oled_setup_h
#define oled_sedup_h
//#include "I2C.h"
#include "Arduino.h"

#define OLED_address  0x3c
#define INTERNAL_I2C_PULLUPS
#include <avr/pgmspace.h>
#include <avr/io.h>

class OLED_I2C {
	private:
		
	public: 

		void print_a_char(unsigned char);
		void init();
		void sendcommand(unsigned char);
		void clear_display(void);
		void SendChar(unsigned char);
		void setXY(unsigned char row,unsigned char col);
		void sendStr(unsigned char *string);
		void init_OLED(void);
		void i2c_OLED_init(void);
	
};

extern OLED_I2C oled;

#endif