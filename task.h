#ifndef _TASK_
#define _TASK_

typedef struct task{
	unsigned char state;
	unsigned long period;
	unsigned long elapsed_time;
	int (*TickFct)(int);
}task;

unsigned short numtasks = 8;
task tasks[8];

#define INPUTPERIOD 50;

unsigned long LCD_period = INPUTPERIOD;
unsigned long Keypad_period = INPUTPERIOD;
unsigned long Buttons_period = INPUTPERIOD;
unsigned long Player1_period = INPUTPERIOD;
unsigned long Player2_period = INPUTPERIOD;
unsigned long Enemy_period = 500;
unsigned long Bounds_period = INPUTPERIOD;
unsigned long LED_period = 100;

unsigned long GCD = 50;

#endif