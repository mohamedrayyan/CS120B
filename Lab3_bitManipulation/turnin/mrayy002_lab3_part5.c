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
	DDRB =0XFE;
	DDRD =0x00;
    /* Insert your solution below */
	unsigned short int w =0x00;
    while (1) {
	w =(PIND +(PINB &0x01));
	if(w >=70) {
		PORTB =0x02;
	}
	else if((w >5) &&(w <70)) {
		PORTB =0x04;
	}
	else if(w <=5) {
		PORTB =0x00;
	}
    }
    return 0;
}

