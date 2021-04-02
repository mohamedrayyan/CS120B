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
	unsigned char s =(~PINA &0x0F);
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
		s =0x3C;
	}
	else if((s >=10) &&(s <=12)) {
		s =0x3D;
	}
	else if((s >=13) &&(s <=15)) {
		s =0x3F;
	}
	if((~PINA &0x0F) <=4) {
		s =s |0x40;
	}
	return s;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	PORTA =0xFF;
	DDRC =0xFF;
	PORTC =0x00;
    /* Insert your solution below */
    while (1) {
	PORTC =check();
    }
    return 0;
}
