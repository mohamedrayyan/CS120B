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
#include <stdlib.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRB =0x00;
	DDRC =0x00;
	DDRD =0xFF;
	PORTD =0x00;
	unsigned char total =0x00;
	unsigned char tempD =0x00;
    /* Insert your solution below */
    while (1) {
	total =PINA +PINB +PINC;
	tempD =abs(PINA -PINC);
	if(total >=140) {
		total++;
	}
	else if(tempD >=80) {
		tempD =total;
	}
	PORTD =(total |tempD);
    }
    return 0;
}
