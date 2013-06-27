/********************************************************************
* lcd.c
*
* By: Josh Erickson
* Date: 06/24/2013
*
* This file 
********************************************************************/

/****AVR Library Includes****/
#include <avr/io.h>
#include <avr/eeprom.h>

/****Project Library Includes****/
#include "lcd.h"
#include "tri_phase.h"

/**********************************************************
* UserService
*
* Arguments:
* Returns:
*
* 
**********************************************************/
void UserService(uint8_t user_button)
{
	/****Static Variables****/
	static uint8_t  top_state = BLANK;
	static uint8_t  previous_user_button;
	static uint16_t temp_address;
	static uint8_t blink_temp;
	
	/****Variables****/
	uint16_t scratch_address;
	
	if (!user_button)
	{
		//countdown to blank
	}
	
	if (previous_user_button == user_button)
	{
		previous_user_button = user_button;
		user_button = 0;
	}
	else
	{
		previous_user_button = user_button;
	}

	switch (top_state)
	{
		case BLANK:		//LCD is OFF
			digit1 = LCD_BLANK;
			digit2 = LCD_BLANK;
			digit3 = LCD_BLANK;
			digit4 = LCD_BLANK;
		
			if (user_button)
			{
				top_state = ADDRESS;
			}
			break;
		case ADDRESS:	//Fixture DMX Address
			digit1 = LCD_A;
			digit2 = LCD_d;
			digit3 = LCD_d;
			digit4 = LCD_r;
			
			switch (user_button)
			{
				case MENU:
					top_state = BLANK;
					break;
				case ENTER:
					temp_address = triphase_address;
					top_state = ADDRESS_EDIT;
					break;
				case UP:
					top_state = FIRMWARE;
					break;
				case DOWN:
					top_state = MOTOR;
					break;
				default:
					break;	
			}
			break; 
		case ADDRESS_EDIT:
			digit4 = AddressDigitLookup(temp_address % 10);
			scratch_address = temp_address / 10;
			digit3 = AddressDigitLookup(scratch_address % 10);
			scratch_address = scratch_address / 10;
			digit2 = AddressDigitLookup(scratch_address % 10);
			digit1 = LCD_BLANK;
			
			switch (user_button)
			{
				case MENU:
					top_state = ADDRESS;
					break;
				case ENTER:
					triphase_address = temp_address;
					if (eeprom_is_ready())
					{
						eeprom_write_word(EEPROM_DMX_ADDRESS, triphase_address);
					}
					top_state = BLANK_ADDRESS;
					break;
				case UP:
					if (MAX_ADDRESS > temp_address)
					{
						temp_address++;
					}					
					else 
					{
						temp_address = MIN_ADDRESS;
					}
					break;
				case DOWN:
					if (MIN_ADDRESS < temp_address)
					{
						temp_address--;
					}
					else
					{
						temp_address = MAX_ADDRESS;
					}
					break;
				default:
					break;
			}			
			break;
		case BLANK_ADDRESS:
			blink_temp++;
			if (blink_temp == 5)
			{
				blink_temp = 0;
				top_state = ADDRESS_EDIT;
			}
			break;
		//case BLINK:
			//break; 
		case MOTOR:
			digit1 = LCD_M;
			digit2 = LCD_P;
			digit3 = LCD_BLANK;
			digit4 = LCD_BLANK;
			
			switch (user_button)
			{
				case MENU:
					top_state = BLANK;
					break;
				case ENTER:
					//top_state = MOTOR_EDIT;
					break;
				case UP:
					top_state = ADDRESS;
					break;
				case DOWN:
					top_state = AUTO;
					break;
				default:
					break;	
			}
			break;
		case AUTO:
			digit1 = LCD_P;
			digit2 = LCD_E;
			digit3 = LCD_r;
			digit4 = LCD_F;
		
			switch (user_button)
			{
				case MENU:
					top_state = BLANK;
					break;
				case ENTER:
					//top_state = AUTO_EDIT;
					break;
				case UP:
					top_state = MOTOR;
					break;
				case DOWN:
					top_state = BLIND;
					break;
				default:
					break;	
			}
			break;
		case BLIND:
			digit1 = LCD_6;
			digit2 = LCD_L;
			digit3 = LCD_n;
			digit4 = LCD_d;
		
			switch (user_button)
			{
				case MENU:
					top_state = BLANK;
					break;
				case ENTER:
					//top_state = BLIND_EDIT;
					break;
				case UP:
					top_state = AUTO;
					break;
				case DOWN:
					top_state = DISPLAY;
					break;
				default:
					break;	
			} 
			break;
		case DISPLAY:
			digit1 = LCD_d;
			digit2 = LCD_1;
			digit3 = LCD_5;
			digit4 = LCD_P;
		
			switch (user_button)
			{
				case MENU:
					top_state = BLANK;
					break;
				case ENTER:
					//top_state = DISPLAY_EDIT;
					break;
				case UP:
					top_state = BLIND;
					break;
				case DOWN:
					top_state = HOURS;
					break;
				default:
					break;	
			}
			break;
		case HOURS:
			digit1 = LCD_F;
			digit2 = LCD_H;
			digit3 = LCD_r;
			digit4 = LCD_5;
		
			switch (user_button)
			{
				case MENU:
					top_state = BLANK;
					break;
				case ENTER:
					//top_state = HOURS_SHOW;
					break;
				case UP:
					top_state = DISPLAY;
					break;
				case DOWN:
					top_state = FIRMWARE;
					break;
				default:
					break;	
			}
			break;
		case FIRMWARE:
			digit1 = LCD_U;
			digit2 = LCD_E;
			digit3 = LCD_r;
			digit4 = LCD_BLANK;
		
			switch (user_button)
			{
				case MENU:
					top_state = BLANK;
					break;
				case ENTER:
					//top_state = FIRMWARE_SHOW;
					break;
				case UP:
					top_state = HOURS;
					break;
				case DOWN:
					top_state = ADDRESS;
					break;
				default:
					break;	
			}
			break;
		default:
			top_state = BLANK;
			break;
	}
}

/********************************************************
* AddressDigitLookup
*********************************************************/
uint8_t AddressDigitLookup(uint8_t num_dig)
{
	/****Variables****/
	uint8_t temp;
	
	static const uint8_t lookup[10] =
	{
		LCD_0,
		LCD_1,
		LCD_2,
		LCD_3,
		LCD_4,
		LCD_5,
		LCD_6,
		LCD_7,
		LCD_8,
		LCD_9
	};
	temp = lookup[num_dig];
	return temp;
}
