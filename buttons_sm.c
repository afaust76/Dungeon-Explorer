unsigned char buttons = 0;

enum Buttons_State{Buttons_Start, Buttons_Check};

int Buttons(int state){
	unsigned char input;
	switch(state){
		default: state = Buttons_Check; break;
	}
	switch(state){
		case Buttons_Check:
			input = ~PINC & 0xF8;
			if(input & 0x80)buttons = 5;
			else if(input & 0x40)buttons = 4;
			else if(input & 0x10)buttons = 2;
			else if(input & 0x20)buttons = 3;
			else if(input & 0x08)buttons = 1;
			else buttons = 0;
			break;
			
		default: break;
	}
	return state;
}