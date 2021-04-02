
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

enum States{Start,Freeze,Pressed,Pressed1} state;
unsigned char seq[9] ={1,2,4,2};
unsigned char i =0x00;
unsigned char p =0;
void tick() {
	switch(state) {
		case Start: {
			PORTB =seq[i];
			if((~PINA &0x01) ==0x00) {
				p =0;
			}
			if((~PINA &0x01) && !p) {
				state =Pressed;
				PORTB =seq[i+1];
			}
			i++;
			if(i >=4) {
				i =0;
			}
			break;
		}
		case Freeze: {
			if((~PINA &0x01)) {
				state =Start;
				p =!p;
			}
			else {
				state =Freeze;
			}
			break;
		}
		case Pressed: {
			PORTB =seq[i];
			if((~PINA &0x01)) {
				state =Pressed;
			}
			else {
				state =Freeze;
			}
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
	state =Start;
    /* Insert your solution below */
    while (1) {
	    tick();
	    while(!TimerFlag);
	    TimerFlag =0;
    }
    return 1;
}
