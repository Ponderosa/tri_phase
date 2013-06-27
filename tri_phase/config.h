/********************************************************************
* config_io.h
*
* By: Josh Erickson
* Date: 06/24/2013
*
********************************************************************/

/****Define Gaurd****/
#ifndef TRIPHASE_CONFIG_IO_H_
#define TRIPHASE_CONFIG_IO_H_

/****Function Protoypes****/
void SetupGPIO(void);
void SetupCounter(void);
void SetupUART(void);

/****Definitions***********/
#define FUSE_MEMORY_SIZE	3			// 3 bytes
#define F_CPU				8000000UL	// 16 MHz

#define LED1_R				0b00010000	// RGB LED Masks for Port B
#define LED1_G				0b01000000	//
#define LED1_B				0b10000000	//

#define USART_RX_COMP		0b10000000
#define FRAME_ERROR			0b00010000
#define DATA_OVERRUN		0b00001000

#define J2_1				0b00100000
#define J2_2				0b00010000
#define J2_3				0b00001000
#define J2_4				0b00000100
#define J2_5				0b01000000
#define J2_6				0b10000000

/****Define Guard****/
#endif /* TRIPHASE_CONFIG_IO_H_ */