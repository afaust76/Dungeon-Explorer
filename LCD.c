#include "LCD.h"

/* The following code was provided by the University of California, Riverside */

void LCD_ClearScreen(void) {
	LCD_WriteCommand(0x01);
}

void LCD_init(void) {
	//wait for 100 ms.
	delay_ms(100);
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x0f);
	LCD_WriteCommand(0x01);
	delay_ms(10);
}

void LCD_WriteCommand (unsigned char Command) {
	CLR_BIT(CONTROL_BUS,RS);
	DATA_BUS = Command;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(2); // ClearScreen requires 1.52ms to execute
}

void LCD_WriteData(unsigned char Data) {
	SET_BIT(CONTROL_BUS,RS);
	DATA_BUS = Data;
	SET_BIT(CONTROL_BUS,E);
	asm("nop");
	CLR_BIT(CONTROL_BUS,E);
	delay_ms(1);
}

void LCD_DisplayString( unsigned char column, const unsigned char* string) {
	LCD_ClearScreen();
	unsigned char c = column;
	while(*string) {
		LCD_Cursor(c++);
		LCD_WriteData(*string++);
	}
}

void LCD_Cursor(unsigned char column) {
	if ( column < 17 ) { // 16x1 LCD: column < 9
		// 16x2 LCD: column < 17
		LCD_WriteCommand(0x80 + column - 1);
		} else {
		LCD_WriteCommand(0xB8 + column - 9);	// 16x1 LCD: column - 1
		// 16x2 LCD: column - 9
	}
}

void delay_ms(int miliSec) //for 8 Mhz crystal
{
	int i,j;
	for(i=0;i<miliSec;i++)
	for(j=0;j<775;j++)
	{
		asm("nop");
	}
}

/*----------------------------------------------------------------------------*/

void custom_chars(){
	//Character walking forward 0
	//Character attacking forward 1
	//Character walking backward 2
	//Character attacking backwards 3
	//Enemy walking 4
	//Enemy attacking 5
	//Door 6
	//Spike 7
	
	LCD_WriteCommand(0x40);
	delay_ms(10);
	
	//Character walking forward 0
	LCD_WriteData(0x04);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x05);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x14);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x0A);
	
	//Character attacking forward 1
	LCD_WriteData(0x04);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0F);
	LCD_WriteData(0x14);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x0A);
	
	//Character walking backward 2
	LCD_WriteData(0x04);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x14);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x05);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x0A);
	
	//Character attacking backwards 3
	LCD_WriteData(0x04);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x04);
	LCD_WriteData(0x1E);
	LCD_WriteData(0x05);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x0A);
	
	//Enemy walking 4
	LCD_WriteData(0x00);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x15);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x0A);
	
	//Enemy attacking 5
	LCD_WriteData(0x00);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x15);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x04);
	LCD_WriteData(0x0A);
	LCD_WriteData(0x0A);
	
	//Door 6
	LCD_WriteData(0x04);
	LCD_WriteData(0x0E);
	LCD_WriteData(0x1F);
	LCD_WriteData(0x1F);
	LCD_WriteData(0x1F);
	LCD_WriteData(0x1F);
	LCD_WriteData(0x1F);
	LCD_WriteData(0x1F);
	
	//Spike 7
	LCD_WriteData(0x0E);
	LCD_WriteData(0x04);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
	LCD_WriteData(0x00);
}