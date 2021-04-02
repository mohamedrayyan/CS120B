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

enum States{Start} state =Start;
unsigned char tmpB =0x00;
void tick() {
	switch(state) {
		case Start: {
			state =Start;
			PORTB =tmpB;
			break;
		}
	}
	switch(state) {
		case Start: {
			tmpB =tmpB <<1;
			if(tmpB >0x04) {
				tmpB =0x01;
			}
			break;
		}
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB =0xFF;
	PORTB =0x00;
	TimerSet(1000);
	TimerOn();
	tmpB =0x01;
    /* Insert your solution below */
    while (1) {
	    tick();
	    while(!TimerFlag);
	    TimerFlag =0;
    }
    return 1;
}
