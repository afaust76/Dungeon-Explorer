enum LED_State{LED_Start, LED_Update};

int LED(int state){
	switch(state){
		default: state = LED_Update; break;
	}
	switch(state){
		unsigned char out;
		case LED_Update:
		out = 0x00;
		if(game_paused == 0){
			switch(pl1hp){
				case 1: out |= 0x01; break;
				case 2: out |= 0x03; break;
				case 3: out |= 0x07; break;
				default: break;
			}
			switch(pl2hp){
				case 1: out |= 0x80; break;
				case 2: out |= 0xC0; break;
				case 3: out |= 0xE0; break;
				default: break;
			}
			
		}
		PORTB = out;
		break;
		
		default: break;
	}
	return state;
}