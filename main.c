#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include "LCD.c"
#include "timer.c"
#include "LCD_sm.c"
#include "LED_sm.c"
#include "player1_sm.c"
#include "player2_sm.c"
#include "enemy_sm.c"
#include "bounds_sm.c"
#include "buttons_sm.c"
#include "keypad_sm.c"

unsigned char button_pressed(unsigned char button){
	if(button < 6) return (button == buttons);
	else if(button == key) return 0x01;
	else return 0x00;
}

int main(void)
{
	DDRD = 0xFF; PORTD = 0x00;
	DDRC = 0x03; PORTC = 0xF8;
    DDRA = 0xF0; PORTA = 0x0F;
    DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char i = 0;
	
	tasks[i].state = Keypad_Start;
	tasks[i].period = Keypad_period;
	tasks[i].elapsed_time = Keypad_period;
	tasks[i].TickFct = &Keypad;
	i++;
	
    tasks[i].state = Buttons_Start;
    tasks[i].period = Buttons_period;
    tasks[i].elapsed_time = Buttons_period;
    tasks[i].TickFct = &Buttons;
	i++;
	
	tasks[i].state = Player1_Start;
	tasks[i].period = Player1_period;
	tasks[i].elapsed_time = Player1_period;
	tasks[i].TickFct = &Player1;
	i++;
    
    tasks[i].state = Player2_Start;
    tasks[i].period = Player2_period;
    tasks[i].elapsed_time = Player2_period;
    tasks[i].TickFct = &Player2;
    i++;
	
    tasks[i].state = Enemy_Start;
    tasks[i].period = Enemy_period;
    tasks[i].elapsed_time = Enemy_period;
    tasks[i].TickFct = &Enemy;
    i++;
	
    tasks[i].state = Bounds_Start;
    tasks[i].period = Bounds_period;
    tasks[i].elapsed_time = Bounds_period;
    tasks[i].TickFct = &Bounds;
	i++;
    
    tasks[i].state = LCD_Start;
    tasks[i].period = LCD_period;
    tasks[i].elapsed_time = LCD_period;
    tasks[i].TickFct = &LCD;
	i++;
    
    tasks[i].state = LED_Start;
    tasks[i].period = LED_period;
    tasks[i].elapsed_time = LED_period;
    tasks[i].TickFct = &LED;
	i++;

	LCD_init();
	custom_chars();
	
	reset();
	
    TimerSet(GCD);
	TimerOn();
	
    while(1){}
}