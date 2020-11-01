unsigned char key;

/* The following code was provided by the University of California, Riverside */

unsigned char GetBit(unsigned char port, unsigned char number){
    return (port&(0x01 << number));
}

/*----------------------------------------------------------------------------*/

enum Keypad_State{Keypad_Start, Keypad_Check};

int Keypad(int state){
    switch(state){ 
        default: state = Keypad_Check; break;
    }
    switch(state){
        case Keypad_Check:
            key = 0x00;
            
/* The following code was provided by the University of California, Riverside */
            
            PORTA = 0xEF;
            asm("nop");
            if (GetBit(PINA,0)==0) { key = '1'; break; } //1
            if (GetBit(PINA,1)==0) { key = '4'; break; } //4
            if (GetBit(PINA,2)==0) { key = '7'; break; } //7
            if (GetBit(PINA,3)==0) { key = '*'; break; } //*
            
            PORTA = 0xDF;
            asm("nop");
            if (GetBit(PINA,0)==0) { key = '2'; break; } //2
            if (GetBit(PINA,1)==0) { key = '5'; break; } //5
            if (GetBit(PINA,2)==0) { key = '8'; break; } //8
            if (GetBit(PINA,3)==0) { key = '0'; break; } //0
            
            PORTA = 0xBF;
            asm("nop");
            if (GetBit(PINA,0)==0) { key = '3'; break; } //3
            if (GetBit(PINA,1)==0) { key = '6'; break; } //6
            if (GetBit(PINA,2)==0) { key = '9'; break; } //9
            if (GetBit(PINA,3)==0) { key = '#'; break; } //#
            
            PORTA = 0x7F;
            asm("nop");
            if (GetBit(PINA,0)==0) { key = 'A'; break; } //A
            if (GetBit(PINA,1)==0) { key = 'B'; break; } //B
            if (GetBit(PINA,2)==0) { key = 'C'; break; } //C
            if (GetBit(PINA,3)==0) { key = 'D'; break; } //D
            
/*----------------------------------------------------------------------------*/
            
            break;
			
        default: break;
    }
    return state;
}