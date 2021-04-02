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

enum TL_states{start1} TL_state =start1;
enum BL_states{start2} BL_state =start2;
enum CL_states{start3} CL_state =start3;
enum toggle{start4} toggle_state =start4;

unsigned char threeLEDS =0x00;
unsigned char blinkLEDS =0x00;
unsigned char togglLEDS =0x00;
unsigned char toggle =0x01;
unsigned char i =0;
unsigned char k =0;
unsigned char p =0;

void TL_tick() {
	switch(TL_state) {
		case start1: {
			threeLEDS =0x01 <<i;
			i++;
			if(i >2) {
				i =0;
			}
			break;
		}
	}
}
void BL_tick() {
	switch(BL_state) {
		case start2: {
			if(k %2 ==0) {
				blinkLEDS =0x00;
			}
			else {
				blinkLEDS =0x08;
			}
			k++;
			break;
		}
	}
}
void CL_tick() {
	switch(CL_state) {
		case start3: {
			PORTB =threeLEDS |blinkLEDS |togglLEDS;
			break;
		}
	}
}
void toggle_tick() {
	switch(toggle_state) {
		case start4: {
			if(p %2) {
				togglLEDS =0x10;
			}
			else {
				togglLEDS =0x00;
			}
			p++;
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
    /* Insert your solution below */
	unsigned long TL_et =0;
	unsigned long BL_et =0;
	unsigned long tl_et =0;
	const unsigned long timerPeriod =2;
	TimerSet(2);
	TimerOn();
	i =0x00;
    while (1) {
	if(TL_et >350) {
		TL_tick();
		TL_et =0;
	}
	if(BL_et >=550) {
		BL_tick();
		BL_et =0;
	}
	if(tl_et >2) {
		if(~PINA &0x04) {
			toggle_tick();
		}
		tl_et =0;
	}
	CL_tick();
	while(!TimerFlag) {}
	TimerFlag =0;
	TL_et +=timerPeriod;
	BL_et +=timerPeriod;
	tl_et +=timerPeriod;
    }
    return 1;
}
