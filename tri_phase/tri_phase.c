/********************************************************************
* tri_phase.c
*
* By: Josh Erickson
* Date: 06/25/2013
*					
* This is the main c file for the tri-phase rehabilitation project.
* All necessary global parameters are defined and initialized.
* The microcontroller setup functions are called.
* The EEPROM is read to load previous state.
* The interrupts are enabled.
* The infinite run loop is defined and carries out the motor and user 
* interface updates.
*
*******************************************************************/

/****AVR Library Includes****/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

/****Project Library Includes****/
#include "tri_phase.h"
#include "config.h"
#include "motor_lut.h"
#include "motor.h"
#include "lcd.h"

/****Global Variables****/
volatile uint8_t  red, green, blue;							// normalized color to intensity
volatile uint8_t  f_intensity, f_red, f_green, f_blue;		// future values from dmx
volatile uint8_t  strobe_duration, strobe_rate;				// current strobe settings				
volatile uint8_t  f_strobe_duration, f_strobe_rate;			// future values from dmx
volatile uint8_t  f_rotation;								// future values from dmx
volatile uint16_t triphase_address;							// current DMX address
volatile uint8_t  user_input;								// current button press
volatile uint8_t  digit1, digit2, digit3, digit4, digit5;	// current LCD output
uint16_t (*MotorUpdateTimerPtr)(uint8_t);					// function pointer for motor profile

/****Fuses***/
//FUSES =
//{
//	LFUSE_DEFAULT,		// .low
//	HFUSE_DEFAULT,		// .high
//	EFUSE_DEFAULT,		// .extended
//};

/********************************************************										
* main
*
* Arguments: void
* Returns: int (GCC conformance)
*
*********************************************************/
int main(void)
{	
	/****Setup Micro****/
	SetupGPIO();
	SetupCounter();	
	SetupUART();
	
	/****Initialize Global Variables****/
	red = 0;
	blue = 0;
	green = 0;
	f_red = 0;
	f_blue = 0;
	f_green = 0;
	
	/****Load Previous Settings from EEPROM****/
	while(!eeprom_is_ready());
	triphase_address = eeprom_read_word(EEPROM_DMX_ADDRESS);
	
	//to be taken out after UI update to choose motor profile
	MotorUpdateTimerPtr = &MotorTimerUpdate1;
	
	sei();							// Enable global interrupts
	
	/****Infinite Running Loop****/
    for(;;)
    {	
		if (TIFR1 & (1 << OCF1A))		// If Timer/Counter1 is ???
		{
			TIFR1 = 1 << OCF1A;			// Clear match flag
			MotorService();				// Update motor position
			UserService(user_input);	// Update LCD and fixture settings
			red = (uint8_t)(((uint16_t)f_red * (uint16_t)f_intensity) / (uint16_t)255);
			blue = (uint8_t)(((uint16_t)f_blue * (uint16_t)f_intensity) / (uint16_t)255);
			green = (uint8_t)(((uint16_t)f_green * (uint16_t)f_intensity) / (uint16_t)255);
				
			if (f_strobe_rate < 10)
			{
				strobe_duration = 255;
			}
			else
			{
				strobe_duration = (uint8_t)(((uint16_t)f_strobe_duration * (uint16_t)(f_strobe_rate-10)) / (uint16_t)255);;
				strobe_rate = f_strobe_rate-10;
			}
		}				
    }
}