/********************************************************************
* lcd.h
*
* By: Josh Erickson
* Date: 06/24/2013
*
********************************************************************/

/****Define Guard****/
#ifndef TRIPHASE_LCD_H_
#define TRIPHASE_LCD_H_

/****Funciton Prototypes****/
void UserService(uint8_t user_button);
uint8_t AddressDigitLookup(uint8_t num_dig);

/****Definitions****/
#define LCD_BLANK	0b00000000			// blank lcd
#define LCD_0		0b00111111			// 0, same reversed
#define LCD_1		0b00000110			// 1, same reversed
#define LCD_2		0b01011011			// 2, same reversed
#define LCD_3		0b01001111			// 3, E reversed
#define LCD_4		0b01100110			// 4, h reversed
#define LCD_5		0b01101101			// 5 & S, same reversed
#define LCD_6		0b01111101			// 6, 9 reversed
#define LCD_7		0b00000111			// 7, L reversed
#define LCD_8		0b01111111			// 8, same reversed
#define LCD_9		0b01100111			// 9, 6 reversed
#define LCD_A		0b01110111			// A
#define LCD_d		0b01011110			// d, P reversed
#define LCD_r		0b01010000			// r
#define LCD_L		0b00111000			// L, 7 reversed
#define LCD_U		0b00111110			// U, M reversed
#define LCD_n		0b01010100			// n
#define LCD_Y		0b01101110			// Y
#define LCD_E		0b01111001			// E, 3 reversed
#define LCD_o		0b01011100			// o
#define LCD_F		0b01110001			// F
#define LCD_P		0b01110011			// P, d reversed
#define LCD_H		0b01110100			// h, 4 reversed
#define LCD_u		0b00011100			// u
#define LCD_M		0b00110111			// M, U reversed

#define LCDR_A		0b01111110			// A reversed
#define LCDR_r		0b01000010			// r reversed
#define LCDR_n		0b01100010			// n reversed
#define LCDR_Y		0b01110101			// Y reversed
#define LCDR_o		0b01100011			// o reversed
#define LCDR_F		0b01001110			// F reversed
#define LCDR_u		0b00100011			// u reversed

#define BLANK			0x00			// LCD State
#define ADDRESS			0x01			//
#define ADDRESS_EDIT	0x02			//
#define BLANK_ADDRESS	0X03			//
#define MOTOR			0x04			//
#define AUTO			0x05			//
#define BLIND			0x06			//
#define DISPLAY			0x07			//
#define HOURS			0x08			//
#define FIRMWARE		0x09			//

#define MENU		0b00100000			// LCD Button Masks
#define ENTER		0b00010000			//
#define UP			0b00001000			//
#define DOWN		0b00000100			//

/****Define Guard****/
#endif /* TRIPHASE_LCD_H_ */
