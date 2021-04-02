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

unsigned char count() {
	unsigned char i =0;
	unsigned char c =0;
	for(i =0; i <8; i++) {
		if(((PINA >>i) &0x01) ==0x01) {
			c++;
		}
		if(((PINB >>i) &0x01) ==0x01) {
			c++;
		}
	}
	return c;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRB =0x00;
	DDRC =0xFF;
    /* Insert your solution below */
    while (1) {
	PORTC =count();
    }
    return 0;
}
