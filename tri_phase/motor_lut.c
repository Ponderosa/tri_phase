/********************************************************************
* lut.c 
*
* By: Josh Erickson
* Date: 06/24/2013
*
* This file contains look up tables for the motor update function.
********************************************************************/

/****AVR Library Includes****/
#include <avr/io.h>
#include <avr/interrupt.h>

/****Project Library Includes****/
#include "motor_lut.h"

/**********************************************************
* MotorPWMDuty
* 
* Arguments: uint8_t sin_loc
* Returns: uint8_t 
**********************************************************/

uint8_t MotorPWMDuty(uint8_t sin_loc)
{
	/****Look Up Table****/
	static const uint8_t lookup[MOTOR_PWM_DUTY_MAX] =
	{
		0,
		4,
		8,
		12,
		17,
		21,
		25,
		30,
		34,
		38,
		42,
		47,
		51,
		55,
		59,
		63,
		68,
		72,
		76,
		80,
		84,
		88,
		92,
		96,
		100,
		104,
		108,
		112,
		116,
		119,
		123,
		127,
		131,
		134,
		138,
		142,
		145,
		149,
		152,
		156,
		159,
		162,
		166,
		169,
		172,
		175,
		178,
		181,
		184,
		187,
		190,
		193,
		196,
		198,
		201,
		204,
		206,
		209,
		211,
		214,
		216,
		218,
		220,
		222,
		225,
		227,
		228,
		230,
		232,
		234,
		235,
		237,
		239,
		240,
		241,
		243,
		244,
		245,
		246,
		247,
		248,
		249,
		250,
		251,
		252,
		252,
		253,
		253,
		254,
		254,
		254,
		255,
		255,
		255,
		254,
		254,
		254,
		253,
		253,
		252,
		252,
		251,
		250,
		249,
		248,
		247,
		246,
		245,
		244,
		243,
		241,
		240,
		239,
		237,
		235,
		234,
		232,
		230,
		228,
		227,
		225,
		222,
		220,
		218,
		216,
		214,
		211,
		209,
		206,
		204,
		201,
		198,
		196,
		193,
		190,
		187,
		184,
		181,
		178,
		175,
		172,
		169,
		166,
		162,
		159,
		156,
		152,
		149,
		145,
		142,
		138,
		134,
		131,
		127,
		123,
		119,
		116,
		112,
		108,
		104,
		100,
		96,
		92,
		88,
		84,
		80,
		76,
		72,
		68,
		63,
		59,
		55,
		51,
		47,
		42,
		38,
		34,
		30,
		25,
		21,
		17,
		12,
		8,
		4,
		0
	};
	
	sin_loc = lookup[sin_loc];
	return sin_loc;
}

/**********************************************************
* MotorTimerUpdate
*
* Arguments:
* Returns:
* 
**********************************************************/

uint16_t MotorTimerUpdate1(uint8_t speed) 
{
	/****Variables****/
	uint16_t temp;
	
	/****Look Up Table****/
	static const unsigned int lookup[MOTOR_TIMER_UPDATE_MAX] =
	{
		333,
		860,
		1387,
		1914,
		2441,
		2968,
		3495,
		4022,
		4549,
		5076,
		5603,
		6130,
		6657,
		7184,
		7711,
		8238,
		8765,
		9292,
		9819,
		10346,
		10873,
		11400,
		11927,
		12454,
		12981,
		13508,
		14035,
		14562,
		15089,
		15616,
		16143,
		16670,
		17197,
		17724,
		18251,
		18778,
		19305,
		19832,
		20359,
		20886,
		21413,
		21940,
		22467,
		22994,
		23521,
		24048,
		24575,
		25102,
		25629,
		26156,
		26683,
		27210,
		27738,
		28265,
		28792,
		29319,
		29846,
		30373,
		30900,
		31427,
		31954,
		32481,
		33008,
		33535,
		34062,
		34589,
		35116,
		35643,
		36170,
		36697,
		37224,
		37751,
		38278,
		38805,
		39332,
		39859,
		40386,
		40913,
		41440,
		41967,
		42494,
		43021,
		43548,
		44075,
		44602,
		45129,
		45656,
		46183,
		46710,
		47237,
		47764,
		48291,
		48818,
		49345,
		49872,
		50399,
		50926,
		51453,
		51980,
		52507,
		53034,
		53561,
		54088,
		54615,
		55142,
		55669,
		56196,
		56723,
		57250,
		57777,
		58304
	};
	
	temp = lookup[speed];
	return temp;
}

/**********************************************************
* MotorTimerUpdate2
*
* Arguments:
* Returns:
*
**********************************************************/

uint16_t MotorTimerUpdate2(uint8_t speed)
{
	/****Variables****/
	uint16_t temp;
	
	/****Look Up Table****/
	static const unsigned int lookup[MOTOR_TIMER_UPDATE_MAX] =
	{
		81,
		2141,
		3346,
		4202,
		4865,
		5407,
		5865,
		6262,
		6612,
		6925,
		7209,
		7467,
		7705,
		7926,
		8131,
		8323,
		8503,
		8673,
		8833,
		8986,
		9131,
		9269,
		9401,
		9528,
		9649,
		9766,
		9878,
		9986,
		10090,
		10191,
		10289,
		10383,
		10475,
		10563,
		10649,
		10733,
		10815,
		10894,
		10971,
		11046,
		11120,
		11191,
		11261,
		11330,
		11397,
		11462,
		11526,
		11588,
		11650,
		11710,
		11769,
		11826,
		11883,
		11939,
		11993,
		12047,
		12099,
		12151,
		12202,
		12252,
		12301,
		12349,
		12397,
		12444,
		12490,
		12535,
		12580,
		12624,
		12667,
		12710,
		12752,
		12794,
		12835,
		12875,
		12915,
		12954,
		12993,
		13032,
		13070,
		13107,
		13144,
		13180,
		13216,
		13252,
		13287,
		13322,
		13356,
		13390,
		13424,
		13457,
		13490,
		13522,
		13555,
		13586,
		13618,
		13649,
		13680,
		13710,
		13740,
		13770,
		13800,
		13829,
		13858,
		13887,
		13915,
		13943,
		13971,
		13999,
		14026,
		14054,
		14080
	};
	
	temp = lookup[speed];
	return temp;
}