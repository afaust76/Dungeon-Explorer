#ifndef _GLOBALS_
#define _GLOBALS_

#define ATTACK1 '0'
#define SELECT1 'D'
#define START1 'C'
#define LEFT1 '#'
#define RIGHT1 '*'

#define ATTACK2 2
#define SELECT2 4
#define START2 5
#define LEFT2 1
#define RIGHT2 3

#define FORWARD 0x00
#define BACKWARD 0x01

unsigned char game_paused;
unsigned char level_won;
unsigned char left_bound;
unsigned char lvl_length;
unsigned char game_over;
unsigned char current_level[200];
unsigned char pl1pos;
unsigned char pl2pos;
unsigned char pl1hp;
unsigned char pl2hp;
unsigned char en1pos;
unsigned char en2pos;

unsigned char button_pressed(unsigned char button);

#endif