#include <avr/io.h>
#include <string.h>
#include "io.h"
#include "keypad.h"
#include "scheduler.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//---------------Shared Variables--------------
unsigned char len =16;
unsigned char j =0x01;
unsigned char key;
//---------------------------------------------
enum keypadStates{getKey,dispKey};
int keypadTick(int state) {
	switch(state) {
		case 0: {
			key =GetKeypadKey();
			if(key =='\0') {
				state =0;
			}
			else {state =1;}
			break;
		}
		case 1: {state =0;break;}
		default: {state =0;}
	}
	switch(state) {
		case 0: {
			break;
		}
		case 1: {
			LCD_Cursor(j);
			LCD_WriteData(key);
			j++;
			if(j >len) {j =0x01;}
			break;
		}
	}
	return state;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB =0xFF;
	PORTB =0x00;
	DDRD =0xFF;
	PORTB =0x00;
	DDRC =0xF0;
	PORTC =0x0F;
    /* Insert your solution below */
	static task task1;
	task *tasks[] ={&task1};
	unsigned char numTasks =sizeof(tasks)/sizeof(task*);

	task1.state =0;
	task1.period =150;
	task1.elapsedTime =task1.period;
	task1.TickFct =&keypadTick;
//--------------------------------------------

	unsigned long GCD =tasks[0]->period;
	for(unsigned char i =0; i <numTasks; i++) {
		GCD =findGCD(GCD,tasks[i]->period);
	}

	TimerSet(GCD);
	TimerOn();
	LCD_init();

	LCD_DisplayString(1,"Congratulations!");

	while(1) {
		for(unsigned char i =0; i <numTasks; i++) {
			if(tasks[i]->elapsedTime ==tasks[i]->period) {
				tasks[i]->state =tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime =0;
			}
			tasks[i]->elapsedTime +=GCD;
		}
		while(!TimerFlag);
		TimerFlag =0;
	}
	return 0;
}
