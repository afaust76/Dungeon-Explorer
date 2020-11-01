#ifndef _LCD_
#define _LCD_

/* The following code was provided by the University of California, Riverside */

#define SET_BIT(p,i) ((p) |= (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) & (1 << (i)))

#define DATA_BUS PORTD		// port connected to pins 7-14 of LCD display
#define CONTROL_BUS PORTC	// port connected to pins 4 and 6 of LCD disp.
#define RS 1			// pin number of uC connected to pin 4 of LCD disp.
#define E 0			// pin number of uC connected to pin 6 of LCD disp.

void LCD_init();
void LCD_ClearScreen(void);
void LCD_WriteCommand (unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_Cursor (unsigned char column);
void LCD_DisplayString(unsigned char column ,const unsigned char *string);
void delay_ms(int miliSec);

/*----------------------------------------------------------------------------*/

void custom_chars();

#endif