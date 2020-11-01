#include "globals.h"
#include "LCD.h"

const unsigned char lvl0[] = "TEMPORARY GAME SCREEN 0 ";
const unsigned char lvl1[] = "|   7   7   7   7   7   7   7   7   7   7   7   || 00                                          6 |";
const unsigned char lvl2[] = "|   7   7   7   7   7   7   7   7   7   7   7   || 00                                          6 |";
const unsigned char lvl3[] = "|   7   7   7   7   7   7   7   7   7   7   7   || 00                                          6 |";

const unsigned char lvl0_length = 12;
const unsigned char lvl1_length = 49;
const unsigned char lvl2_length = 49;
const unsigned char lvl3_length = 49;

const unsigned char start_screen[] = "DUNGEON EXPLORER   Press Start";
const unsigned char new_game[] = "  < New Game >";
const unsigned char load_game[] = "  < Load Game >";
const unsigned char resume[] = "     PAUSED        < Resume >";
const unsigned char quit[] = "     PAUSED         < Quit >";
const unsigned char WIP[] = "Work in progressPress Select";
const unsigned char no_save[] = " No Saved Game      Detected";
unsigned char save_game[] = "     Lvl:X       P1HP:Y P2HP:Z";
const unsigned char go_back[] = "  Press SELECT     to go back";
const unsigned char save_game_yes[] = " Save progress?      < Yes >";
const unsigned char save_game_no[] = " Save progress?      < No >";
const unsigned char game_saved[] = "   GAME SAVED";
const unsigned char game_won[] = "Congratulations!    You win!";
const unsigned char fail_screen[] = "    GAME OVER";

unsigned char game_data;
unsigned char data_valid;
unsigned char level;

void print_game_screen(){
	LCD_ClearScreen();
	unsigned char cursor = 1;
	for(unsigned char i = left_bound; (i < left_bound + 16) &&
	(i < left_bound + lvl_length); i++){
		LCD_Cursor(cursor);
		if(current_level[i] >= '0' && current_level[i] <= '7')
		LCD_WriteData(current_level[i] - 48);
		else LCD_WriteData(current_level[i]);
		cursor++;
	}
	for(unsigned char i = left_bound + lvl_length;
	(i < left_bound + lvl_length + 16) &&
	(i < left_bound + lvl_length + lvl_length); i++){
		LCD_Cursor(cursor);
		if(current_level[i] >= '0' && current_level[i] <= '7')
		LCD_WriteData(current_level[i] - 48);
		else LCD_WriteData(current_level[i]);
		cursor++;
	}
}

void setlevel(unsigned char lvl){
	const unsigned char * string;
	if(lvl == 0x00){
		level = 0x00;
		lvl_length = lvl0_length;
		string = lvl0;
	}
	else if(lvl == 0x01){
		level = 0x01;
		lvl_length = lvl1_length;
		string = lvl1;
	}
	else if(lvl == 0x02){
		level = 0x02;
		lvl_length = lvl2_length;
		string = lvl2;
	}
	else{
		level = 0x03;
		lvl_length = lvl3_length;
		string = lvl3;
	}
	for(unsigned char i = 0; i < (2*lvl_length); i++){
		current_level[i] = string[i];
	}
	pl1pos = 52;
	pl2pos = 51;
	en1pos = 0;
	en2pos = 0;
	left_bound = 0;
}

void reset(){
	game_paused = 1;
	game_over = 0;
	level_won = 0;
	pl1hp = 3;
	pl2hp = 3;
	data_valid = 1;
	setlevel(0x01);
}

enum LCD_State{LCD_Start, LCD_StartScreen, LCD_NewGame1, LCD_NewGame2,
	LCD_LoadGame1, LCD_LoadGame2, LCD_GameScreen1, LCD_GameScreen2,
	LCD_GameWon1, LCD_GameWon2, LCD_GameOver, LCD_Resume1, LCD_Resume2, LCD_Quit1,
	LCD_Quit2, LCD_SavedGame1, LCD_SavedGame2, LCD_GoBack1, LCD_GoBack2,
	LCD_SaveYes1, LCD_SaveYes2, LCD_SaveNo1, LCD_SaveNo2, LCD_GameSaved1,
LCD_GameSaved2};

int LCD(int state){
	switch(state){
		case LCD_Start:
			reset();
			state = LCD_StartScreen;
			LCD_DisplayString(1, start_screen);
			break;
		
		case LCD_StartScreen:
			if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				state = LCD_NewGame1;
				LCD_DisplayString(1, new_game);
			}
			else state = LCD_StartScreen;
			break;
		
		case LCD_NewGame1:
			if(button_pressed(SELECT1) || button_pressed(LEFT1) ||
				button_pressed(RIGHT1) || button_pressed(SELECT2) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2))
				state = LCD_NewGame1;
			else{
				state = LCD_NewGame2;
				reset();
			}
			break;
		
		case LCD_NewGame2:
			if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				state = LCD_GameScreen1;
				print_game_screen();
			}
			else if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2)){
				state = LCD_LoadGame1;
				LCD_DisplayString(1, load_game);
			}
			else state = LCD_NewGame2;
			break;
		
		case LCD_LoadGame1:
			if(button_pressed(SELECT1) || button_pressed(LEFT1) ||
				button_pressed(RIGHT1) || button_pressed(SELECT2) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2))
				state = LCD_LoadGame1;
			else state = LCD_LoadGame2;
			break;
		
		case LCD_LoadGame2:
			if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2)){
				state = LCD_NewGame1;
				LCD_DisplayString(1, new_game);
			}
			else if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				state = LCD_SavedGame1;
				game_data = (char)(eeprom_read_byte((uint8_t*)46));
				if((game_data & 0x03) < 2 || ((game_data >> 2) & 0x03) == 0x00
				|| ((game_data >> 4) & 0x03) == 0x00){
					LCD_DisplayString(1, no_save);
					data_valid = 0;
				}
				else{
					save_game[9] = (game_data & 0x03) + 48;
					save_game[22] = ((game_data >> 2) & 0x03) + 48;
					save_game[29] = ((game_data >> 4) & 0x03) + 48;
					LCD_DisplayString(1, save_game);
				}
			}
			else state = LCD_LoadGame2;
			break;
		
		case LCD_SavedGame1:
			if(button_pressed(SELECT1) || button_pressed(LEFT1) ||
				button_pressed(RIGHT1) || button_pressed(SELECT2) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2))
				state = LCD_SavedGame1;
			else state = LCD_SavedGame2;
			break;
		
		case LCD_SavedGame2:
			if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				if(data_valid == 0) state = LCD_LoadGame1;
				else{
					setlevel(game_data & 0x03);
					pl1hp = (game_data >> 2) & 0x03;
					pl2hp = (game_data >> 4) & 0x03;
					state = LCD_GameScreen1;
					print_game_screen();
				}
			}
			else if((button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2)) && data_valid){
				state = LCD_GoBack1;
				LCD_DisplayString(1, go_back);
			}
			else state = LCD_SavedGame2;
			break;

		case LCD_GoBack1:
			if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2))
				state = LCD_GoBack1;
			else state = LCD_GoBack2;
			break;
		
		case LCD_GoBack2:
			if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2)){
				state = LCD_SavedGame1;
				LCD_DisplayString(1, save_game);
			}
			else if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				state = LCD_LoadGame1;
				LCD_DisplayString(1, load_game);
			}
			else state = LCD_GoBack2;
			break;
		
		case LCD_GameScreen1:
			if(button_pressed(SELECT1) || button_pressed(SELECT2))
				state = LCD_GameScreen1;
			else {
				state = LCD_GameScreen2;
				game_paused = 0;
			}
			break;
		
		case LCD_GameScreen2:
			if(button_pressed(START1) || button_pressed(START2)){
				game_paused = 1;
				state = LCD_Resume1;
				LCD_DisplayString(1, resume);
			}
			else if(level_won){
				level_won = 0;
				game_paused = 1;
				if(level == 3){
					reset();
					state = LCD_GameWon1;
					LCD_DisplayString(1, game_won);
				}
				else{
					level++;
					setlevel(level);
					game_data = (level & 0x03) | ((pl1hp & 0x03) << 2) |
					((pl2hp & 0x03) << 4);
					state = LCD_SaveYes1;
					LCD_DisplayString(1, save_game_yes);
				}
			}
			else if(game_over){
				state = LCD_GameOver;
				LCD_DisplayString(1, fail_screen);
				reset();
			}
			else state = LCD_GameScreen2;
			break;
		
		case LCD_GameWon1:
			if (button_pressed(SELECT1) || button_pressed(SELECT2))
				state = LCD_GameWon1;
			else state = LCD_GameWon2;
			break;
		
		case LCD_GameWon2:
			if(button_pressed(SELECT1) || button_pressed(SELECT2))
				state = LCD_StartScreen;
			else state = LCD_GameWon2;
			break;
		
		case LCD_GameOver:
			if(button_pressed(SELECT1) || button_pressed(SELECT2))
				state = LCD_StartScreen;
			else state = LCD_GameOver;
			break;
		
		case LCD_SaveYes1:
			if(button_pressed(SELECT1) || button_pressed(LEFT1) ||
				button_pressed(RIGHT1) || button_pressed(SELECT2) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2))
				state = LCD_SaveYes1;
			else state = LCD_SaveYes2;
			break;
		
		case LCD_SaveYes2:
			if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				state = LCD_GameSaved1;
				eeprom_write_byte((uint8_t*)46,(uint8_t)game_data);
				LCD_DisplayString(1, game_saved);
			}
			else if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2)){
				state = LCD_SaveNo1;
				LCD_DisplayString(1, save_game_no);
			}
			else state = LCD_SaveYes2;
			break;
		
		case LCD_SaveNo1:
			if(button_pressed(LEFT1)||button_pressed(RIGHT1) ||
				button_pressed(LEFT2)||button_pressed(RIGHT2))
				state = LCD_SaveNo1;
			else state = LCD_SaveNo2;
			break;
		
		case LCD_SaveNo2:
			if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				state = LCD_GameScreen1;
				print_game_screen();
			}
			else if(button_pressed(LEFT1)||button_pressed(RIGHT1) ||
				button_pressed(LEFT2)||button_pressed(RIGHT2)){
				state = LCD_SaveYes1;
				LCD_DisplayString(1, save_game_yes);
			}
			else state = LCD_SaveNo2;
			break;
		
		case LCD_GameSaved1:
			if(button_pressed(SELECT1) || button_pressed(SELECT2))
				state = LCD_GameSaved1;
			else state = LCD_GameSaved2;
			break;
		
			case LCD_GameSaved2:
			if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				state = LCD_GameScreen1;
				print_game_screen();
			}
			else state = LCD_GameSaved2;
			break;
		
		case LCD_Resume1:
			if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(START1) || button_pressed(LEFT2) ||
				button_pressed(RIGHT2) || button_pressed(START2))
				state = LCD_Resume1;
			else state = LCD_Resume2;
			break;
		
		case LCD_Resume2:
			if(button_pressed(SELECT1) || button_pressed(SELECT2))
				state = LCD_GameScreen1;
			else if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2)){
				state = LCD_Quit1;
				LCD_DisplayString(1, quit);
			}
			else state = LCD_Resume2;
			break;
		
		case LCD_Quit1:
			if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2))
				state = LCD_Quit1;
			else state = LCD_Quit2;
			break;
		
		case LCD_Quit2:
			if(button_pressed(LEFT1) || button_pressed(RIGHT1) ||
				button_pressed(LEFT2) || button_pressed(RIGHT2)){
				state = LCD_Resume1;
				LCD_DisplayString(1, resume);
			}
			else if(button_pressed(SELECT1) || button_pressed(SELECT2)){
				reset();
				state = LCD_NewGame1;
				LCD_DisplayString(1, new_game);
			}
			else state = LCD_Quit2;
			break;
		
		default: state = LCD_StartScreen; break;
	}
	switch(state){
		case LCD_GameScreen2: print_game_screen(); break;
		
		case LCD_Resume1: game_paused = 1; break;
		
		case LCD_Resume2: game_paused = 1; break;
		
		default: break;
	}
	return state;
}