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
#include "pwm.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states{start, pre, on, post} state =start;
double seq[19] ={261, 294, 329, 349, 392, 440, 493, 523, 493, 449, 392, 349, 329, 294, 261, 294, 261};
double time[19] ={1915, 1700, 1519, 1432, 1275, 1136, 1014, 956, 1014, 1136, 1275, 1432, 1519, 1700, 1915, 1700, 1915};
unsigned char i =0;
unsigned char t =0;

void tick() {
	switch(state) {
		case start: {
			if((~PINA &0x01)) {
				state =pre;
			}
			break;
		}
		case pre: {
			if((~PINA &0x01)) {
				state =pre;
			}
			else {
				state =on;
			}
			break;
		}
		case on: {
			set_PWM(seq[i]);
			if(t++ >(time[i] /400)) {
				i++;
			}
			if(i >18) {
				i =0;
				if((~PINA &0x01)) {
					state =post;
				}
				else {
					state =start;
				}
				set_PWM(0.00);
			}
			break;
		}
		case post: {
			if((~PINA &0x01) ==0x00) {
				state =start;
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
	t =0;
    /* Insert your solution below */
	TimerSet(400);
	TimerOn();
	PWM_on();
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag =0;

    }
    return 1;
}
