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

enum State{Start,Incr,Decr,Hold,Reset} state =Start;

void tick() {
	switch(state) {
		case Start: {
			if(((PINA &0x01) ==0x01) &&((PINA &0x02) ==0x00)) {
				state =Incr;
			}
			else if(((PINA &0x02) ==0x02) &&((PINA &0x01) ==0x00)) {
				state =Decr;
			}
			else if((PINA &0x03) ==0x03) {
				state =Reset;
			}
			else {
				state =Start;
			}
			break;
		}
		case Incr: {
			state =Hold;	
			break;
		}
		case Decr: {
			state =Hold;
			break;
		}
		case Hold: {
			if((PINA &0x01) ^((PINA &0x02) >>1)) {
				state =Hold;
			}
			else if(((PINA &0x03) ==0x00)) {
				state =Start;
			}
			else if(((PINA &0x03) ==0x03)) {
				state =Reset;
			}
			break;
		}
		case Reset: {
			state =Start;
			break;
		}
	}
	switch(state) {
		case Incr: {
			if(PINC <9) {
				PORTC =1+PORTC;
			}
			break;
		}
		case Decr: {
			if(PINC >0) {
				PORTC =PORTC-1;
			}
			break;
		}
		case Reset: {
			PORTC =0x00;
			break;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRC =0xFF;
	PORTC =0x07;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 0;
}
