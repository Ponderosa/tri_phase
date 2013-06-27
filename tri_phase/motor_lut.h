/********************************************************************
* lut.h
*
* By: Josh Erickson
* Date: 06/24/2013
*
********************************************************************/

/****Define Guards****/
#ifndef TRIPHASE_LUT_H_
#define TRIPHASE_LUT_H_

/****Function Protoypes****/
uint16_t MotorTimerUpdate1(uint8_t);
uint16_t MotorTimerUpdate2(uint8_t);
uint8_t MotorPWMDuty(uint8_t);

/****Defininitions****/
#define PWM_UNIQUE				93
#define MOTOR_TIMER_UPDATE_MAX	111
#define MOTOR_PWM_DUTY_MAX		(PWM_UNIQUE * 2) - 1

/****Define Guard****/
#endif /* TRIPHASE_LUT_H_ */

