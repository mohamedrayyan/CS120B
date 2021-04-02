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
unsigned char key =0x00;
char s1[] ={"CS120B is Legend... wait for it DARY!"};
//---------------------------------------------
enum displayStates{display1,display2};
	unsigned char j =0x00;
	unsigned char k =16;
	unsigned char q =0;
	unsigned char z =0x00;
int displayTick(int state) {
	unsigned char p =strlen(s1);
	switch(state) {
		case 0: {
			if(k >=1) {state =0; q =0;}
			else if(k <1) {state =1;}
			break;
		}
		case 1: {
			if(z ==p) {
				q =0;
				j =0;
				z =0;
				k =16;
				state =0;
			}
			break;
		}
	}
	switch(state) {
		case 0: {
			char s1Tmp[j+2];
			for(;q <j; q++) {
				s1Tmp[q] =s1[q];
			}
			s1Tmp[j+1] ='\0';
			LCD_ClearScreen();
			LCD_DisplayString(k,s1Tmp);

			k--;
			if(j <p) {
				j++;
			}
			q =0;
			break;
		}
		case 1: {
			z++;
			q =z;
			if(j <p) {j++;}

			char s1Tmp[j-q+1];
			
			strncpy(s1Tmp,s1+q,(j-q));
			s1Tmp[j-q]='\0';
			LCD_ClearScreen();
			LCD_DisplayString(1,s1Tmp);
			break;
		}
			
	}
	return state;
}
enum keypadStates{getKey};
int keypadTick(int state) {
	switch(state) {
		case 0: {
			state =0;
			break;
		}
	}
	switch(state) {
		case 0: {key =GetKeypadKey();break;}
	}
	return state;
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB =0xFF;
	PORTB =0x00;
	DDRD =0xFF;
	PORTB =0x00;
	DDRA =0xFF;
	PORTA =0x00;
    /* Insert your solution below */
	static task task1,task2;
	task *tasks[] ={&task1,&task2};
	unsigned char numTasks =sizeof(tasks)/sizeof(task*);

	task1.state =0;
	task1.period =500;
	task1.elapsedTime =task1.period;
	task1.TickFct =&keypadTick;
//--------------------------------------------
	task2.state =0;
	task2.period =300;
	task2.elapsedTime =task2.period;
	task2.TickFct =&displayTick;

	unsigned long GCD =tasks[0]->period;
	for(unsigned char i =0; i <numTasks; i++) {
		GCD =findGCD(GCD,tasks[i]->period);
	}

	TimerSet(GCD);
	TimerOn();
	LCD_init();

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
