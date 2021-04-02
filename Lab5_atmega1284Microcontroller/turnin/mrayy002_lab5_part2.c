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
			if((~PINA &0x03) ==0x03) {
				state =Reset;
			}
			else if((~PINA &0x03) ==0x01) {
				state =Incr;
			}
			else if((~PINA &0x03) ==0x02) {
				state =Decr;
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
			if(((~PINA &0x03) ==0x00)) {
				state =Start;
			}
			else if((~PINA &0x03) ==0x03) {
				state =Reset;
			}
			break;
		}
		case Reset: {
			if((~PINA &0x03) ==0x00) {
				state =Start;
			}
			else if((~PINA &0x03) ==0x03) {
				state =Reset;
			}
			break;
		}
	}
	switch(state) {
		case Incr: {
			if(PINC <9) {
				PORTC =PINC +1;
			}
			break;
		}
		case Decr: {
			if(PINC >0) {
				PORTC =PINC -1;
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
	PORTA =0xFF;
	DDRC =0xFF;
	PORTC =0x00;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 0;
}
