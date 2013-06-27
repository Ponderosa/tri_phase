/********************************************************************
 * config.c
 *
 * By: Josh Erickson
 * Date: 06/24/2013
 *
 * This file
 *******************************************************************/
 
/****AVR Library Includes****/
#include <avr/io.h>

/****Project Library Includes****/
#include "config.h"
#include "motor_lut.h"

/**********************************************************
* SetupGPIO
*
* Arguments: void
* Reuturns: void
*
* 
**********************************************************/
void SetupGPIO(void)
{
	/****Variables****/
	uint8_t temp_mcucr;
	
	/****Port A****/
	// PA0 - J2_7  (output)
	// PA1 - J2_8  (output)
	// PA2 - J2_9  (output)
	// PA3 - J2_10 (output)
	// PA4 - J2_11 (output)
	// PA5 - J2_12 (output)
	// PA6 - J2_13 (output)
	// PA7 - J2_14 (output)
	PORTA = 0x00;
	DDRA  = 0xFF;
	
	/****Port B****/
	// PB0 - CA8_3   (tri-state) Remote control
	// PB1 - CA8_2   (tri-state) Remote control
	// PB2 - CA8_1   (tri-state) Remote control
	// PB3 - LAMP1_2 (tri-state) no connect
	// PB4 - LED1_R  (output)
	// PB5 - unused  (tri-state)
	// PB6 - LED2_G	 (output)
	// PB7 - LED3_B  (output)
	PORTB = 0x00;
	DDRB  = 0xD0;
	
	/****Port C****/
	// PC0 - DMX_DIR (output)
	// PC1 - unused  (tri-state)
	// PC2 - J2_4	 (output) down
	// PC3 - J2_3	 (output) up
	// PC4 - J2_2	 (output) enter
	// PC5 - J2_1	 (output) menu
	// PC6 - J2_5	 (output)
	// PC7 - J2_6	 (input pull-up)
	PORTC = 0x80;
	DDRC  = 0x7D;
	
	/****Port D****/
	// PD0 - DMX_IN_TRI  (input)
	// PD1 - DMX_OUT_TRI (output)
	// PD2 - MIC		 (input)
	// PD3 - unused		 (tristate)
	// PD4 - PHASE2		 (output)
	// PD5 - PHASE1		 (output)
	// PD6 - VREF2		 (output)
	// PD7 - VREF1		 (output)
	PORTD = 0x30; //why is this?
	DDRD  = 0xF2;
	
	// Disable JTAG for Port C
	temp_mcucr = MCUCR | (1 << JTD);
	MCUCR = temp_mcucr;		// write twice needed for protection
	MCUCR = temp_mcucr;
}

/********************************************************
* SetupCounter
*********************************************************/
void SetupCounter(void)
{
	// Setup LED service timer (counter 0)
	TCCR0A = 0x02;	// CTC WGM1 = 1
	TCCR0B = 0x02;	// clkio/8 CS01 = 1
	OCR0A  = 0x19;	// service every 400 cycles (50uS)
	TIMSK0 = 0x02;  // interrupt on OC match A
	
	// Setup motor pwm timer (counter 2)
	TCCR2A = 0xA3;	// COM2A1 = 1, COM2B1 = 1, WGM1 = 1, WGM0 = 1
	TCCR2B = 0x01;	// clkio/1 CS20 = 1;
	OCR2A  = 0xFF;  // vref 1 is at top of sin2
	OCR2B  = 0x00;	// vref 2 is at bottom of sin2
	
	// Setup motor service timer (counter 1)
	TCCR1A = 0x00;	// 
	TCCR1B = 0x0A;	// CTC WGM2 = 1; clkio/8 CS11 = 1;
	OCR1AH = (uint8_t) (MotorTimerUpdate(MOTOR_TIMER_UPDATE_MAX - 1) >> 8);
	OCR1AL = (uint8_t) (MotorTimerUpdate(MOTOR_TIMER_UPDATE_MAX - 1));
	OCR1BH = 0x46;
	OCR1BL = 0x50; // 9ms
}

/********************************************************
* SetupUART
*********************************************************/
void SetupUART(void)
{
	// Setup USART0 to rx dmx
	UCSR0B = 0x90;	// RX Interrrupt Bit7, RX Enable Bit4
	UCSR0C = 0x0E;	// 2 stop bits Bit3, 8bit char Bit2 Bit1
	UBRR0L = 0x03;  // set baud to 250k for 16mhz clock
}