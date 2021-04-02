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
#include "pwm.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states{start, pwr, inc, dec} state =start;
double seq[8] ={261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
unsigned char i =0;
unsigned char s =0;
void tick() {
	switch(state) {
		case start: {
			if((~PINA &0x02)) {
				state =pwr;
			}
			if((~PINA &0x04) &&(s)) {
				state =inc;
			}
			else if((~PINA &0x08) &&(s)) {
				state =dec;
			}
			break;
		}
		case pwr: {
			if((~PINA &0x02)) {
				state =pwr;
			}
			else {
				state =start;
				s =!s;
				if(s) {
					set_PWM(seq[i]);
				}
				else {
					i =0x00;
					set_PWM(0.00);
				}
			}
			break;
		}
		case inc: {
			if((~PINA &0x04) &&(s)) {
				state =inc;
			}
			else {
				state =start;
				if(i+1 <=7) {
					i++;
				}
				set_PWM(seq[i]);
			}
			break;
		}
		case dec: {
			if((~PINA &0x08) &&(s)) {
				state =dec;
			}
			else {
				state =start;
				if(i-1 >=0) {
					i--;
				}
				set_PWM(seq[i]);
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
	s =0;
    /* Insert your solution below */
	PWM_on();
    while (1) {
	tick();
    }
    return 1;
}
