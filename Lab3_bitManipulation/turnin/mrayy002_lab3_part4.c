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

int main() {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRB =0xFF;
	DDRC =0xFF;
    /* Insert your solution below */
    while (1) {
	PORTC =((PINA <<4) &0xF0);
	PORTB =((PINA >>4) &0x0F);
    }
    return 0;
}

