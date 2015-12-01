/*
 * float_to_uchar.h
 *
 * Created: 11/30/2015 11:19:57 PM
 *  Author: brian
 */ 


#ifndef FLOAT_TO_UCHAR_H_
#define FLOAT_TO_UCHAR_H_

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




#endif /* FLOAT_TO_UCHAR_H_ */