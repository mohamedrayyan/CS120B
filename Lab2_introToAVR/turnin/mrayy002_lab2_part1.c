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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRB =0xFF;
	PORTB =0x00;
	unsigned char tmpB =0x00;
	unsigned char tmpA =0x00;
    /* Insert your solution below */
	tmpB =PINB;
    while (1) {
	if((PINA &0x01) ==0x01 && ((PINA &0x02) !=0x02)) {
		tmpB =((tmpB &0x00) |0x01);
		PORTB =tmpB;
	}
	else {
		tmpB =tmpB &0x00;
		PORTB =tmpB;
	}
    }
    return 0;
}
