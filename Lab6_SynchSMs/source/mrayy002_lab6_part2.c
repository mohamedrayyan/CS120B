
/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{start,led1,led2,led4,l2,pressed,freeze} state;
unsigned char p =0;
void tick() {
	switch(state) {
		case start: {
			state =led1;
			break;
		}
		case led1: {
			if((~PINA &0x01) ==0x00) {
				p =0;
			}
			if((~PINA &0x01) &&(!p)) {
				state =pressed;
			}
			else {
				state =led2;
			}
			break;
		}
		case led2: {
			if((~PINA &0x01) ==0x00) {
				p =0;
			}
			if((~PINA &0x01) &&(!p)) {
				state =pressed;
			}
			else {
				state =led4;
			}
			break;
		}
		case led4: {
			if((~PINA &0x01) ==0x00) {
				p =0;
			}
			if((~PINA &0x01) &&(!p)) {
				state =pressed;
			}
			else {
				state =l2;
			}
			break;
		}
		case l2: {
			if((~PINA &0x01) ==0x00) {
				p =0;
			}
			if((~PINA &0x01) &&(!p)) {
				state =pressed;
			}
			else {
				state =led1;
			}
			break;
		}
		case freeze: {
			if((~PINA &0x01)) {
				state =led1;
			}
			break;
		}
		case pressed: {
			if((~PINA &0x01) ==0x00) {
				state =freeze;
				p =1;
			}
			break;
		}
	}
	switch(state) {
		case led1: {
			PORTB =0x01;
			break;
		}
		case led2: {
			PORTB =0x02;
			break;
		}
		case led4: {
			PORTB =0x04;
			break;
		}
		case l2: {
			PORTB =0x02;
			break;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA =0x00;
	PORTA =0xFF;
	DDRB =0xFF;
	PORTB =0x00;
	TimerSet(300);
	TimerOn();
	state =start;
    /* Insert your solution below */
    while (1) {
	    tick();
	    while(!TimerFlag);
	    TimerFlag =0;
    }
    return 1;
}
