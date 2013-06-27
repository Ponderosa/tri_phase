/********************************************************************
* interrupt.c
*
* By: Josh Erickson
* Date: 06/24/2013
*
* This file is used to define all interrupts.
* The Timer0 interrupt handles updates to the LED and User Interface.
* The USART0 RX interface handles updates from the incoming DMX data.
********************************************************************/

/****AVR Library Includes****/
#include <avr/interrupt.h>

/****Project Library Includes****/
#include "tri_phase.h"
#include "config.h"
#include "lcd.h"
#include "interrupt.h"

/**********************************************************
* ISR TIMER0_COMPA_vect
*
* This intterrupt handles updates to the RGB LED and the 
* User Interface. The RGB LED's are driven in a bit-banging 
* fashion. While the User Interface uses a 5 step multiplexed
* button read and LCD write.
**********************************************************/
ISR(TIMER0_COMPA_vect)
{
	/****Static Variables****/
	static uint8_t dutyc_location;	// Duty Cycle Count
	static uint8_t dutyc_count;		
	static uint8_t ui_mode;			// 
	static uint8_t refresh_count;
	static uint8_t button_press;
	
	/****RGB LED Update****/
	if(0 == dutyc_location)			// Duty Cycle Reset (wrap around)
	{		
		if (strobe_duration >= dutyc_count)
		{
			if (red)					// Prevent ghosting
			{
				PORTB |= LED1_R;		// Turn on Red
			}
			if (green)					// Prevent ghosting
			{
				PORTB |= LED1_G;		// Turn on Green
			}
			if (blue)					// Prevent ghosting
			{
				PORTB |= LED1_B;		// Turn on Blue
			}
		}
		
		dutyc_count++;				// Every 10.24ms
		
		if (strobe_rate < dutyc_count)
		{
			dutyc_count = 0;
		}

	}
	
	if(dutyc_location == red)		
	{
		PORTB &= ~LED1_R;			// Turn off Red
	}		
	if(dutyc_location == green)
	{
		PORTB &= ~LED1_G;			// Turn off Green
	}		
	if(dutyc_location == blue)
	{
		PORTB &= ~LED1_B;			// Turn off Blue
	}
	
	dutyc_location++;				// Will continually wrap around
	
	//if(255 == dutyc_location)
	//{
	//	dutyc_location = 0;
	//}
	
	/****User Interface Update****/
	if (UI_REFRESH_RATE < refresh_count)
	{
		refresh_count = 0;
		
		switch (ui_mode) 			// Circular state machine
		{
			case 1:
				user_input = button_press;	// store accumulated user input
				button_press = 0;			// clear accumulated user input
				PORTA = digit1;				// write first LCD digit
				PORTC |= J2_1 | J2_5;		// enable first digit and button pullup
				ui_mode = 2;
				break;
			case 2:
				if (~PINC & J2_6)			// grab button state from case 1
				{
					button_press |= MENU;	// accumulate Menu
				}
				PORTC &= ~J2_1;				// disable first digit
				PORTA = digit2;				// write second LCD digit
				PORTC |= J2_2;				// enable second digit
				ui_mode = 3;
				break;
			case 3:
				if (~PINC & J2_6)			// grab button state from case 2
				{
					button_press |= ENTER;	// accumulate Enter
				}
				PORTC &= ~J2_2;				// disable second digit
				PORTA = digit3;				// write third digit
				PORTC |= J2_3;				// enable third digit
				ui_mode = 4;
				break;
			case 4:
				if (~PINC & J2_6)			// grab button state from case 3
				{
					button_press |= UP;		// accumulate Up
				}
				PORTC &= ~J2_3;				// disable third digit
				PORTA = digit4;				// write forth digit
				PORTC |= J2_4;				// enable forth digit
				ui_mode = 5;
				break;
			case 5:
				if (~PINC & J2_6)			// grab button state from case 4
				{
					button_press |= DOWN;	// accumulate Down
				}
				PORTC &= ~J2_4 & ~J2_5; 	// disable forth digit 
				PORTA = digit5;				// write digit5 (indicator leds)
				ui_mode = 1;
				break;
			default:
				ui_mode = 1;
				break;
		}
	}
	refresh_count++;		
}	

/********************************************************
* ISR USART0_RX_vect
*
* This interrupt handles the incoming DMX data. The DMX 
* stream is decoded by exploiting the hardware frame error
* to recognize the Break. The first received byte should be 
* 0x00 to indicate DMX. After that each serial byte 
* received increments the counter until the device address.
* Then the channels are recorded.
*********************************************************/
ISR(USART0_RX_vect)
{
	/****Static Variables****/
	static uint16_t current_channel;	// Current DMX channel being received
	static uint8_t  dmx_mode;			// DMX valid state
	
	/****Variables****/
	uint8_t status = UCSR0A;			// Snapshot of USART status register
	uint8_t data   = UDR0;				// Snapshot of USART data
	
	/****DMX Update****/
	if(FRAME_ERROR & status)			// DMX Protocol Break
	{
		current_channel = 0;			// Reset channel counter
		dmx_mode = 0;					// Set DMX not valid
	}
	
	if(dmx_mode) 						// DMX valid 
	{
		if((triphase_address + CH_INTENSITY_OFFSET) == current_channel)
		{
			f_intensity = data;
		}
		else if((triphase_address + CH_RED_OFFSET) == current_channel)
		{
			f_red = data;
		}		
		else if((triphase_address + CH_GREEN_OFFSET) == current_channel)
		{
			f_green = data;
		}		
		else if((triphase_address + CH_BLUE_OFFSET) == current_channel)
		{
			f_blue = data;
		}		
		else if((triphase_address + CH_ROTATION_OFFSET) == current_channel)
		{
			f_rotation = data;
		}
		else if((triphase_address + CH_STRB_DUR_OFFSET) == current_channel)
		{
			f_strobe_duration = data;
		}		
		else if((triphase_address + CH_STRB_FRQ_OFFSET) == current_channel)
		{
			f_strobe_rate = data;
		}
		
		current_channel++;
	}
	else if((0x00 == current_channel) && (0x00 == data))
	{
		dmx_mode = 1;			// Set DMX valid
	}		
}