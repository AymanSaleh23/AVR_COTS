/*
 * SERVO_prog.c
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Err_Type.h"
#include "../../LIB/MATH_FUNC.h"

#include "../../MCAL/PWM/PWM_interface.h"

#include "SERVO_private.h"
#include "SERVO_config.h"
#include "SERVO_interface.h"

static u8 ServoChannel = 0;

u8 SERVO_voidInit				(	u8 Copy_u8Channel	){
	u8 Local_u8ErrorState = OK;

	if ( (PWM_OC1A == Copy_u8Channel ) || (PWM_OC1B == Copy_u8Channel) ){
		PWM_u8Enable		(Copy_u8Channel , PWM_NON_INVERTED , PWM_FAST_ICR1);
		PWM_u8SetPeriodus	(SERVO_PERIOD_US,DUTY_100, DUTY_0);
		PWM_u8SetMappedRanges(Copy_u8Channel ,128 ,0);
		SERVO_voidSetPositionDegree(0);
		PWM_u8SetPrescaler	(Copy_u8Channel , PWM_PRESCALLER_8);
		ServoChannel = Copy_u8Channel;
	}
	else {
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
void	SERVO_voidSetPositionDegree	(	u8 Copy_u8Degree	){
	PWM_u8SetDuty		(Copy_u8Degree ,ServoChannel);
}

