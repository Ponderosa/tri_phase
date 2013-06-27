/********************************************************************
* motor.c
*
* By: Josh Erickson
* Date: 06/24/2013
*
* This file 
********************************************************************/

/****AVR Library Includes****/
#include <avr/io.h>
#include <avr/interrupt.h>

/****Project Library Includes****/
#include "tri_phase.h"
#include "motor_lut.h"

/**********************************************************
* MotorService
*
* Arguments:
* Returns:
* 
**********************************************************/			
void MotorService(void)
{
	/****Static Variables****/
	static uint16_t vref_counter = 0;
	static uint8_t rotation = 0;
			
	/****Step Through Phase Pattern****/
	if (vref_counter <= (PWM_UNIQUE - 2))
	{
		PORTD |= 1<<PD5;	// Phase 1 = 1
		PORTD |= 1<<PD4;	// Phase 2 = 1
	}		
	else if ((vref_counter >= (PWM_UNIQUE - 1)) && (vref_counter <= ((PWM_UNIQUE - 1) * 2 - 1)))
	{
		PORTD &= ~(1<<PD5);	// Phase 1 = 0
		PORTD |= 1<<PD4;	// Phase 2 = 1
	}
	else if ((vref_counter >= ((PWM_UNIQUE - 1) * 2)) && (vref_counter <= ((PWM_UNIQUE - 1) * 3 - 1)))
	{
		PORTD &= ~(1<<PD5);	// Phase 1 = 0
		PORTD &= ~(1<<PD4); // Phase 2 = 0
	}
	else // ((vref_counter >= 66) && (vref_counter <= 87))
	{
		PORTD |= 1<<PD5;	// Phase 1 = 1
		PORTD &= ~(1<<PD4); // Phase 2 = 0
	}
	
	/****Set Rotation Speed****/
	rotation = f_rotation;	// copy to safe variable

	if ((rotation > 9) && (rotation < 121))			// clockwise rotation fast-slow
	{
		vref_counter++;
		if (vref_counter >= ((PWM_UNIQUE - 1) * 4))
		{
			vref_counter = 0;
		}
		rotation -= 10;
		OCR1AH = (uint8_t) (MotorTimerUpdate1(rotation) >> 8);
		OCR1AL = (uint8_t) (MotorTimerUpdate1(rotation));
	}
	else if ((rotation > 134) && (rotation < 246))	// counter clockwise rotation
	{
		vref_counter--;
		if (vref_counter >= ((PWM_UNIQUE - 1) * 4))
		{
			vref_counter = (PWM_UNIQUE - 1) * 4 - 1;
		}
		rotation = (uint8_t) ((((int8_t) (rotation - 135)) * -1) + 110);
		OCR1AH = (uint8_t) (MotorTimerUpdate1(rotation) >> 8);
		OCR1AL = (uint8_t) (MotorTimerUpdate1(rotation));
	}
	
	/****Set Motor Postion****/
	OCR2A  = MotorPWMDuty((vref_counter + (PWM_UNIQUE - 1)) % ((PWM_UNIQUE - 1) * 2));	// vref 1 is at top of sin2
	OCR2B  = MotorPWMDuty(vref_counter % ((PWM_UNIQUE - 1) * 2));	// vref 2 is at bottom of sin2
}		