enum Enemy_State{Enemy_Start, Enemy_Update};

int Enemy(int state){
	switch(state){
		default: state = Enemy_Update; break;
	}
	switch(state){
		case Enemy_Update:
			if(game_paused == 0){
				if(en1pos == 0 && left_bound + 15 < lvl_length - 4){
					en1pos = (2*lvl_length)-4;
					current_level[en1pos] = '4';
				}
				else if(current_level[en1pos] == '5')
					current_level[en1pos] = '4';
				else if(en1pos == pl1pos + 1){
					current_level[en1pos] = '5';
					pl1hp--;
				}
				else if (en1pos != 0 && current_level[en1pos - 1] == ' '){
					current_level[en1pos-1] = '4';
					current_level[en1pos] = ' ';
					en1pos--;
				}
				else{};
			
				if(en2pos == 0 && left_bound > 1){
					en2pos = lvl_length + 1;
					current_level[en2pos] = '4';

				}
				else if(current_level[en2pos] == '5')
					current_level[en2pos] = '4';
				else if(en2pos == pl2pos - 1){
					current_level[en2pos] = '5';
					pl2hp--;
				}
				else if(en2pos != 0 && current_level[en2pos + 1] == ' '){
					current_level[en2pos+1] = '4';
					current_level[en2pos] = ' ';
					en2pos++;
				}
				else{}
			
				if(pl1hp == 0 || pl2hp == 0) {
					game_over = 1;
					game_paused = 1;
				}
			}
			break;
		
		default: break;
	}
	return state;
}