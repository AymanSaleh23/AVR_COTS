/*
 * PWM_interface.h
 *
 *  Created on: Sep 21, 2021
 *      Author: 20114
 */

#ifndef MCAL_PWM_PWM_INTERFACE_H_
#define MCAL_PWM_PWM_INTERFACE_H_

#define PWM_INVERTED		1
#define PWM_NON_INVERTED	2

#define PWM_OC0		1
#define PWM_OC1A	2
#define PWM_OC1B	3
#define PWM_OC2		4

#define PWM_PHASE_CORRECR_MODE		1
#define PWM_FAST_MODE				3

#define PWM_PHASE_CORRECT_8BIT		1
#define PWM_PHASE_CORRECT_9BIT		2
#define PWM_PHASE_CORRECT_10BIT		3
#define PWM_FAST_8BIT				5
#define PWM_FAST_9BIT				6
#define PWM_FAST_10BIT       		7
#define PWM_PHASE_FRQ_CORRECT_ICR1  8
#define PWM_PHASE_FRQ_CORRECT_OCR1A 9
#define PWM_PHASE_CORRECT_ICR1		10
#define PWM_PHASE_CORRECT_OCR1A		11
#define PWM_FAST_ICR1     			14
#define PWM_FAST_OCR1A     			15

#define	OC0_NO_HW_ACTION		1

#define OC0_CLR_OC0_SET_TOP 	5
#define OC0_SET_OC0_CLR_TOP   	6
#define OC0_CLR_UP_SET_DOWN 	7
#define OC0_SET_UP_CLR_DOWN    	8

#define OC1A_NO_HW_ACTION		1
#define OC1B_NO_HW_ACTION       5

#define OC1A_CLR_OC1A_SET_TOP	9
#define OC1A_SET_OC1A_CLR_TOP   10
#define OC1A_CLR_UP_SET_DOWN	11
#define OC1A_SET_UP_CLR_DOWN	12

#define OC1B_CLR_OC1B_SET_TOP 	13
#define OC1B_SET_OC1B_CLR_TOP  	14
#define OC1B_CLR_UP_SET_DOWN	15
#define OC1B_SET_UP_CLR_DOWN   	16


#define OC2_NO_HW_ACTION		1

#define OC2_CLR_OC2_SET_TOP     5
#define OC2_SET_OC2_CLR_TOP     6
#define OC2_CLR_UP_SET_DOWN     7
#define OC2_SET_UP_CLR_DOWN     8

#define PWM_PRESCALLER_1		1
#define PWM_PRESCALLER_8		2
#define PWM_PRESCALLER_64		4
#define PWM_PRESCALLER_256		6
#define PWM_PRESCALLER_1024		7

u8 PWM_u8Init			(	void	);
u8 PWM_u8Enable			(	u8	Copy_u8OCPin	, u8 Copy_u8OCMode , u8 Copy_u8PWMPhase );
u8 PWM_u8Disable		(	u16 Copy_u8OCPin	);
u8 PWM_u8SetDuty		(	u16 Copy_u8ValueInRange	,	u8 Copy_u8OCPin	);
u8 PWM_u8SetPeriodus	(	u16 Copy_u16Periodus	, u16 Copy_u16MaxDutyus	, u16 Copy_u16MinDutyus);
u8 PWM_u8SetPrescaler	(	u8 	Copy_u8PWMchannel 	, u8 Copy_u8Prescaler	);
u8 PWM_u8SetMappedRanges(	u8 	Copy_u8PWMchannel 	, u16 Copy_u16Max , u16 Copy_u16Min);
#endif /* MCAL_PWM_PWM_INTERFACE_H_ */
