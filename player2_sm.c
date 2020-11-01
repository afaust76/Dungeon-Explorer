unsigned char pl2dir;
unsigned char p2count;

enum Player2_State{Player2_Start, Player2_Play, Player2_Attack};

int Player2(int state){
	switch(state){
		case Player2_Play:
			if(button_pressed(ATTACK2) && game_paused == 0x00){
				state = Player2_Attack;
				if(pl2dir == FORWARD){
					current_level[pl2pos] = '1';
					if(en1pos == pl2pos + 1){
						current_level[pl2pos + 1] = ' ';
					}
				}
				else{
					current_level[pl2pos] = '3';
					if(en2pos == pl2pos - 1){
						current_level[en2pos] = ' ';
						en2pos = 0;
					}
				}
			}
			break;
		
		case Player2_Attack:
			if(button_pressed(ATTACK2) == 0x00 && game_paused == 0x00){
				state = Player2_Play;
				if(pl2dir == FORWARD) current_level[pl2pos] = '0';
				else current_level[pl2pos] = '2';
			}
			break;
		
		default: state = Player2_Play; break;
	}
	switch(state){
		case Player2_Play:
			if(game_paused == 0x00){
				if(button_pressed(START2)) game_paused = 0x01;
				else{
					if(button_pressed(SELECT2) && pl2dir == FORWARD && current_level[pl2pos + 1] == '6'){
						level_won = 0x01;
						game_paused = 0x01;
					}
					else if(button_pressed(LEFT2)){
						if(p2count == 0 || p2count == 3){
							p2count = 0;
							current_level[pl2pos] = '2';
							pl2dir = BACKWARD;
							if(current_level[pl2pos - 1] == ' '){
								current_level[pl2pos - 1] = '2';
								current_level[pl2pos] = ' ';
								pl2pos--;
							}
						}
						p2count++;
					}
					else if(button_pressed(RIGHT2)){
						if(p2count == 0 || p2count == 3){
							p2count = 0;
							current_level[pl2pos] = '0';
							pl2dir = FORWARD;
							if(current_level[pl2pos + 1] == ' '){
								current_level[pl2pos + 1] = '0';
								current_level[pl2pos] = ' ';
								pl2pos++;
							}
						}
						p2count++;
					}
					else p2count = 0;
				}
			}
			break;
		
		case Player2_Attack: if(button_pressed(START2)) game_paused = 0x01;
			break;
		
		default: break;
	}
	return state;
}