unsigned char pl1dir;
unsigned char p1count;

enum Player1_State{Player1_Start, Player1_Play, Player1_Attack};

int Player1(int state){
	switch(state){ 
		case Player1_Play:
			if(button_pressed(ATTACK1) && game_paused == 0x00){
				state = Player1_Attack;
				if(pl1dir == FORWARD){
					current_level[pl1pos] = '1';
					if(en1pos == pl1pos + 1){
						current_level[en1pos] = ' ';
						en1pos = 0;
					}
				}
				else{
					current_level[pl1pos] = '3';
					if(en2pos == pl1pos - 1){
						current_level[pl1pos - 1] = ' ';
					}
				}
			}
			break;
		
		case Player1_Attack:
			if(button_pressed(ATTACK1) == 0x00 && game_paused == 0x00){
				state = Player1_Play;
				if(pl1dir == FORWARD) current_level[pl1pos] = '0';
				else current_level[pl1pos] = '2';
			}
			break;
		
		default: state = Player1_Play; break;
	}
	switch(state){ 
		case Player1_Play:
			if(game_paused == 0x00){ 
				if(button_pressed(START1) || button_pressed(START2)) 
					game_paused = 0x01;
				else{
					if(button_pressed(SELECT1) && pl1dir == FORWARD && 
						current_level[pl1pos + 1] == '6'){
						level_won = 0x01;
						game_paused = 0x01;
					}
					else if(button_pressed(LEFT1)){
						if(p1count == 0 || p1count == 3){
							p1count = 0;
							current_level[pl1pos] = '2';
							pl1dir = BACKWARD;
							if(current_level[pl1pos - 1] == ' '){
								current_level[pl1pos - 1] = '2';
								current_level[pl1pos] = ' ';
								pl1pos--;
							}
						}
						p1count++;
					}
					else if(button_pressed(RIGHT1)){
						if(p1count == 0 || p1count == 3){
							p1count = 0;
							current_level[pl1pos] = '0';
							pl1dir = FORWARD;
							if(current_level[pl1pos + 1] == ' '){
								current_level[pl1pos + 1] = '0';
								current_level[pl1pos] = ' ';
								pl1pos++;
							}
						}
						p1count++;
					}
					else p1count = 0;
				}
			}
			break;
		
		case Player1_Attack: if(button_pressed(START1)) game_paused = 0x01; 
			break;
		
		default: break;
	}
	return state;
}