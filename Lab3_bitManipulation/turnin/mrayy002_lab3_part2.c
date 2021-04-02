/*	Author: mrayy002
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char check() {
	unsigned char s =(PINA &0x0F);
	if((s ==1) ||(s==2)) {
		s =0x20;
	}
	else if((s ==3) ||(s ==4)) {
		s =0x30;
	}
	else if((s ==5) ||(s ==6)) {
		s =0x38;
	}
	else if((s >=7) &&(s <=9)) {
		s =0x3c;
	}
	else if((s >=10) &&(s <=12)) {
		s =0x3E;
	}
	else if((s >=13) &&(s <=15)) {
		s =0x3F;
	}

	if((PINA &0x0F) <=4) {
		s =s |0x40;
	}

	return s;
}
/*
	if((PINA &0x01) ==0x01 ||(PINA &0x02) ==0x02) {
		s =0x20;
	}
	else if((PINA &0x03) ==0x03 ||(PINA &0x04) ==0x04) {
		s =0x30;
	}
	else if((PINA &0x05) ==0x05 ||(PINA &0x06) ==0x06) {
		s =0x38;
	}
	else if((PINA &0x07) ==0x07 ||(PINA &0x08) ==0x08 ||(PINA &0x09)) {
		s =0x3C;
	}
*/	

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRC =0xFF;
    /* Insert your solution below */
    while (1) {
	PORTC =check();
    }
    return 0;
}
