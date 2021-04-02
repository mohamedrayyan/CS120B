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

enum State{Start,B0ON,B1ON,B1ON1,B0ON1} state =Start;

void tick() {
	switch(state) {
		case Start: {
			state =B0ON;
			break;
		}
		case B0ON: {
			if((PINA &0x01) ==0x00) {
				state =B0ON;
			}
			else if((PINA &0x01) ==0x01) {
				state =B1ON;
			}
			break;
		}
		case B1ON: {
			if((PINA &0x01) ==0x01) {
				state =B1ON;
			}
			else if((PINA &0x01) ==0x00) {
				state =B1ON1;
			}
			break;
		}
		case B1ON1: {
			if((PINA &0x01) ==0x00) {
				state =B1ON1;
			}
			else if((PINA &0x01) ==0x01) {
				state =B0ON1;
			}
			break;
		}
		case B0ON1: {
			if((PINA &0x01) ==0x01) {
				state =B0ON1;
			}
			else if((PINA &0x01) ==0x00) {
				state =B0ON;
			}
			break;
		}
	}
	switch(state) {
		case B1ON: {
			PORTB =0x02;
			break;
		}
		case B0ON1: {
			PORTB =0x01;
			break;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0X00;
	DDRB =0xFF;
	PORTB =0x01;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 0;
}
