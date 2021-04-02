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
	unsigned char tmpC = 0x00;
	unsigned char i =0;
	for(i =0; i <4; i++) {
		(((PINA >>i) &0x01) ==0x00)? tmpC++: 0;
	}
	return tmpC;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRC =0xFF;
	PORTC =0x00;
    /* Insert your solution below */
    while (1) {
	PORTC =check();	
    }
    return 0;
}
