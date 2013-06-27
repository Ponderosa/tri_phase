/********************************************************************
* triphase.h
* 
* By: Josh Erickson
* Date: 06/24/2013
*
********************************************************************/

/****Define Guard****/
#ifndef TRIPHASE_TRIPHASE_H_
#define TRIPHASE_TRIPHASE_H_

/****External Variables****/
extern volatile uint8_t  red, green, blue;							// normalized color to intensity
extern volatile uint8_t  f_intensity, f_red, f_green, f_blue;		// future values from dmx
extern volatile uint8_t  strobe_duration, strobe_rate;				// current strobe settings	
extern volatile uint8_t  f_strobe_duration, f_strobe_rate;			// future values from dmx
extern volatile uint8_t  f_rotation;								// future values from dmx
extern volatile uint16_t triphase_address;							// current DMX address
extern volatile uint8_t  user_input;								// current button press
extern volatile uint8_t  digit1, digit2, digit3, digit4, digit5;	// current LCD output
extern uint16_t (*MoterUpdateTimerPtr)(uint8_t);					// function pointer for motor profile

/****Definitions****/
#define		MAX_ADDRESS				512		// MAX DMX address
#define		MIN_ADDRESS				1		// Starting DMX address
#define		CH_INTENSITY_OFFSET 	0x00	// DMX Channel ordering
#define		CH_RED_OFFSET			0x01	//
#define		CH_GREEN_OFFSET			0x02	//
#define		CH_BLUE_OFFSET			0x03	//
#define		CH_ROTATION_OFFSET		0x04	//
#define		CH_STRB_DUR_OFFSET		0x05	//
#define		CH_STRB_FRQ_OFFSET		0x06	//

#define		EEPROM_DMX_ADDRESS		0x00	// 2 Byte DMX Address
#define		EEPROM_MOTOR			0x02	// Motor profile
#define		EEPROM_AUTO				0x03	// Autonomous on/off
#define		EEPROM_BLIND			0x04	// Blind on/off
#define		EEPROM_DISPLAY			0x05	// Display on/off

/****Define Guard****/
#endif /* TRIPHASE_TRIPHASE_H */