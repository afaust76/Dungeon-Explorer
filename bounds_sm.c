enum Bounds_State{Bounds_Start, Bounds_Update};

int Bounds(int state){
	switch(state){
		default: state = Bounds_Update; break;
	}
	switch(state){
		case Bounds_Update:
			if(((pl2pos - (left_bound + lvl_length)) > 8) && 
				current_level[left_bound+15] != '|') left_bound++;
			else if(((pl1pos - (left_bound + lvl_length)) < 8) && 
				current_level[left_bound] != '|') left_bound--;
			break;
		
		default: break;
	}
	return state;
}