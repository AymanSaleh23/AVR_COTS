/*

 * TIMER_prog.c
 *
 *  Created on: Sep 12, 2021
 *      Author: 20114

 ******************************************************
 ******************************************************
			Make it work Then make it better
 ******************************************************
 ******************************************************
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Err_Type.h"

#include "../PWM/PWM_interface.h"
#include "../ICU/ICU_interface.h"
#include "../ICU/ICU_reg.h"

#include "TIMER_private.h"
#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_reg.h"

static u16 	ScheduleOverFlow 		= 0 ;
static u8 	ScheduleFPreloadCount	= 0 ;

static u8	Continuity	= CONTINUITY_OFF;
static u8 	ScheduleTimer = TIMER_T2;


static u32 Timer0_Freq = 0;
static u32 Timer1_Freq = 0;
static u32 Timer2_Freq = 0;

static u8 Timer2_Prescaler = 0;


//	ISR Timer/Counter 0  OverFlow
static void ( * T0OVFunc )(void) = NULL;

//	ISR Timer/Counter 0  Compare Match
static void ( * T0COMPFunc )(void) = NULL;

//	ISR Timer/Counter 1  OverFlow
static void ( * T1OVFunc )(void) 	= NULL;

//	ISR Timer/Counter 1  Compare Match	B
static void ( * T1BCOMPFunc )(void) = NULL;

//	ISR Timer/Counter 1  Compare Match	A
static void ( * T1ACOMPFunc )(void) = NULL;

//	ISR Timer/Counter 1  Input Capture
static void ( * ICUFunc )(void) 	= NULL;

//	ISR Timer/Counter 2  OverFlow
static void ( * T2OVFunc	) (void)= NULL;
static void ( * ScheduleFunc )(void)= NULL;

//	ISR Timer/Counter 2  Compare Match
static void ( * T2COMPFunc )(void) 	= NULL;

//Initialization of the Pre-build configuration
u8 		TIMER_u8Init			(	void		){
	u8 Local_u8ErrorState = OK;

	return Local_u8ErrorState;

}
//Setting the timer Post-build Configuration;
u8 		TIMER_u8SettingUp		(	const Timer_Type * Copy_TConfiguration		){
	u8 Local_u8ErrorState = OK;
	/*	WGM Setting up */
	TIMER_u8ChangeMode(Copy_TConfiguration->Num,Copy_TConfiguration->Mode);

	/*	COM Setting up */
	TIMER_u8ChangeHWAction(Copy_TConfiguration->OCChannel ,Copy_TConfiguration->OCAction);

	/*	Prescaler Setting up */
	TIMER_u8ChangePrescaler(Copy_TConfiguration->Num , Copy_TConfiguration->CLK);

	if (NULL != Copy_TConfiguration){
		/**********************		Timer	0 	****************************/
		if ( Copy_TConfiguration->Num == TIMER_T0){

			if ( Copy_TConfiguration->OverflowInt == TIMER_INT_DIS){
				CLR_BIT(TIMSK, TIMSK_TOIE0);
			}
			else if (Copy_TConfiguration->OverflowInt == TIMER_INT_EN){
				SET_BIT(TIMSK, TIMSK_TOIE0);
			}
			if ( Copy_TConfiguration->COMPInt== TIMER_INT_DIS){
				CLR_BIT(TIMSK, TIMSK_OCIE0);
			}
			else if (Copy_TConfiguration->COMPInt== TIMER_INT_EN){
				SET_BIT(TIMSK, TIMSK_OCIE0);
			}
		}
		/**********************		Timer	1 	****************************/
		else if ( Copy_TConfiguration->Num == TIMER_T1){

			if ( Copy_TConfiguration->OverflowInt == TIMER_INT_DIS){
				CLR_BIT(TIMSK, TIMSK_TOIE1);
			}
			else if (Copy_TConfiguration->OverflowInt == TIMER_INT_EN){
				SET_BIT(TIMSK, TIMSK_TOIE1);
			}
			if ( Copy_TConfiguration->COMPInt== TIMER_INT_DIS){
				CLR_BIT(TIMSK, TIMSK_OCIE1A);
			}
			else if (Copy_TConfiguration->COMPInt== TIMER_INT_EN){
				SET_BIT(TIMSK, TIMSK_OCIE1A);
			}
		}
		/**********************		Timer	2 	****************************/

		else if ( Copy_TConfiguration->Num == TIMER_T2){

			if ( Copy_TConfiguration->OverflowInt == TIMER_INT_DIS){
				CLR_BIT(TIMSK, TIMSK_TOIE2);
			}
			else if (Copy_TConfiguration->OverflowInt == TIMER_INT_EN){
				SET_BIT(TIMSK, TIMSK_TOIE2);
			}
			if ( Copy_TConfiguration->COMPInt== TIMER_INT_DIS){
				CLR_BIT(TIMSK, TIMSK_OCIE2);
			}
			else if (Copy_TConfiguration->COMPInt== TIMER_INT_EN){
				SET_BIT(TIMSK, TIMSK_OCIE2);
			}
		}

	}
	else {
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}
u8		TIMER_u8ChangeMode		(	u8 Copy_u8TNum , u8 Copy_u8Mode			){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8TNum){

	default :	Local_u8ErrorState = NOK;	break;
	/*	WGM Setting up Timer	0	*/
	case TIMER_T0:{

		TCCR0 &= T0_WGM_MASKING_VALUE;
		switch(Copy_u8Mode){
		default	:	Local_u8ErrorState = NOK;	break;
		case  TIMER_NORMAL_MODE			 	: TCCR0 |= T0_WGM_NORMAL_MODE 			  ;     break;
		case  PWM_PHASE_CORRECR_MODE 		: TCCR0 |= T0_WGM_PWM_PHASE_CORRECT_MODE  ;     break;
		case  TIMER_CTC_MODE			 	: TCCR0 |= T0_WGM_CTC_MODE				  ;     break;
		case  PWM_FAST_MODE		 			: TCCR0 |= T0_WGM_FAST_PWM_MODE 		  ;     break;
		}
	}break;
	/*	WGM Setting up Timer	1	*/
	case TIMER_T1:{

		TCCR1 &= T1_WGM_MASKING_VALUE;
		switch(Copy_u8Mode){
		default	:	Local_u8ErrorState = NOK;	break;
		case  TIMER_NORMAL_MODE			 	: TCCR1 |= T1_WGM_NORMAL;     					break;
		case  PWM_PHASE_CORRECT_8BIT	    : TCCR1 |= T1_WGM_PWM_PHASE_CORRECT_8BIT;   	break;
		case  PWM_PHASE_CORRECT_9BIT	    : TCCR1 |= T1_WGM_PWM_PHASE_CORRECT_9BIT;  	 	break;
		case  PWM_PHASE_CORRECT_10BIT		: TCCR1 |= T1_WGM_PWM_PHASE_CORRECT_10BIT; 	 	break;
		case  TIMER1_CTC_MODE_OCR1A			: TCCR1 |= T1_WGM_CTC_OCR1A;     				break;
		case  PWM_FAST_8BIT					: TCCR1 |= T1_WGM_FAST_PWM_8BIT;     			break;
		case  PWM_FAST_9BIT					: TCCR1 |= T1_WGM_FAST_PWM_9BIT;     			break;
		case  PWM_FAST_10BIT          		: TCCR1 |= T1_WGM_FAST_PWM_10BIT;     			break;
		case  PWM_PHASE_FRQ_CORRECT_ICR1 	: TCCR1 |= T1_WGM_PWM_PHASE_FRQ_CORRECT_ICR1;	break;
		case  PWM_PHASE_FRQ_CORRECT_OCR1A	: TCCR1 |= T1_WGM_PWM_PHASE_FRQ_CORRECT_OCR1A;	break;
		case  PWM_PHASE_CORRECT_ICR1  		: TCCR1 |= T1_WGM_PWM_PHASE_CORRECT_ICR1;   	break;
		case  PWM_PHASE_CORRECT_OCR1A 		: TCCR1 |= T1_WGM_PWM_PHASE_CORRECT_OCR1A;  	break;
		case  TIMER1_CTC_ICR1               : TCCR1 |= T1_WGM_CTC_ICR1;     				break;
		case  PWM_FAST_ICR1           		: TCCR1 |= T1_WGM_FAST_PWM_ICR1;     			break;
		case  PWM_FAST_OCR1A           		: TCCR1 |= T1_WGM_FAST_PWM_OCR1A;     			break;
		}

	}break;
	/*	WGM Setting up Timer	2	*/
	case TIMER_T2:{

		TCCR2 &= T2_WGM_MASKING_VALUE;
		switch(Copy_u8Mode){
		default	:	Local_u8ErrorState = NOK;	break;
		case  TIMER_NORMAL_MODE		: TCCR2 |= T2_WGM_NORMAL_MODE 			  ;     break;
		case  PWM_PHASE_CORRECR_MODE: TCCR2 |= T2_WGM_PWM_PHASE_CORRECT_MODE  ;     break;
		case  TIMER_CTC_MODE		: TCCR2 |= T2_WGM_CTC_MODE				  ;     break;
		case  PWM_FAST_MODE		 	: TCCR2 |= T2_WGM_FAST_PWM_MODE 		  ;     break;
		}
	}break;

	}
	return Local_u8ErrorState;
}
u8		TIMER_u8ChangeHWAction	(	u8 Copy_u8OCNum , u8 Copy_u8Action		){
	u8 Local_u8ErrorState = OK;

	switch (Copy_u8OCNum){

	default :Local_u8ErrorState = NOK; break;

	case HW_OC0 :{
		TCCR0 &= T0_COM_MASKING_VALUE;
		switch (Copy_u8Action){
		default :	Local_u8ErrorState = NOK;	break;
		case OC0_NO_HW_ACTION	:	TCCR0 |= T0_COM0_NO_HW_ACTION;		break;
		case OC0_TOGG	        :   TCCR0 |= T0_COM0_TOGG_OC0;			break;
		case OC0_CLR			:   TCCR0 |= T0_COM0_CLR_OC0;			break;
		case OC0_SET			:   TCCR0 |= T0_COM0_SET_OC0;			break;
		case OC0_CLR_OC0_SET_TOP:   TCCR0 |= T0_COM0_CLR_OC0_SET_TOP;	break;
		case OC0_SET_OC0_CLR_TOP:   TCCR0 |= T0_COM0_SET_OC0_CLR_TOP;	break;
		case OC0_CLR_UP_SET_DOWN:   TCCR0 |= T0_COM0_CLR_UP_SET_DOWN;	break;
		case OC0_SET_UP_CLR_DOWN:   TCCR0 |= T0_COM0_SET_UP_CLR_DOWN;	break;
		}

	} break;
	case HW_OC1A :{
		TCCR1A &= T1_COM1A_MASKING_VALUE;
		switch (Copy_u8Action){
		default :	Local_u8ErrorState = NOK;	break;
		case  OC1A_NO_HW_ACTION			:	TCCR1A |= T1_COM1A_NO_HW_ACTION;	break;
		case  OC1A_TOGG	        		: 	TCCR1A |= T1_COM1A_TOGG_OC1A;		break;
		case  OC1A_CLR		            : 	TCCR1A |= T1_COM1A_CLR_OC1A;		break;
		case  OC1A_SET	                : 	TCCR1A |= T1_COM1A_SET_OC1A;		break;
		case  OC1A_CLR_OC1A_SET_TOP	    : 	TCCR1A |= T1_COM1A_CLR_OC1A_SET_TOP;break;
		case  OC1A_SET_OC1A_CLR_TOP     : 	TCCR1A |= T1_COM1A_SET_OC1A_CLR_TOP;break;
		case  OC1A_CLR_UP_SET_DOWN		: 	TCCR1A |= T1_COM1A_CLR_UP_SET_DOWN;	break;
		case  OC1A_SET_UP_CLR_DOWN		: 	TCCR1A |= T1_COM1A_SET_UP_CLR_DOWN;	break;
		}

	} break;

	case HW_OC1B :{
		TCCR1A &= T1_COM1B_MASKING_VALUE;
		switch (Copy_u8Action){
		default :	Local_u8ErrorState = NOK;	break;
		case  OC1B_NO_HW_ACTION   	: 	TCCR1A |= T1_COM1B_NO_HW_ACTION; 	break;
		case  OC1B_TOGG           	: 	TCCR1A |= T1_COM1B_TOGG_OC1B;		break;
		case  OC1B_CLR            	:	TCCR1A |= T1_COM1B_CLR_OC1B;		break;
		case  OC1B_SET				:	TCCR1A |= T1_COM1B_SET_OC1B;		break;
		case  OC1B_CLR_OC1B_SET_TOP : 	TCCR1A |= T1_COM1B_CLR_OC1A_SET_TOP;break;
		case  OC1B_SET_OC1B_CLR_TOP : 	TCCR1A |= T1_COM1B_SET_OC1A_CLR_TOP;break;
		case  OC1B_CLR_UP_SET_DOWN	:	TCCR1A |= T1_COM1B_CLR_UP_SET_DOWN;	break;
		case  OC1B_SET_UP_CLR_DOWN  :	TCCR1A |= T1_COM1B_SET_UP_CLR_DOWN;	break;

		}

	} break;

	case HW_OC2 :{

		TCCR2 &= T2_COM_MASKING_VALUE;
		switch (Copy_u8Action){

		default :	Local_u8ErrorState = NOK;	break;
		case OC2_NO_HW_ACTION	:	TCCR2 |= T2_COM2_NO_HW_ACTION;		break;
		case OC2_TOGG	        :   TCCR2 |= T2_COM2_TOGG_OC2;			break;
		case OC2_CLR			:   TCCR2 |= T2_COM2_CLR_OC2;			break;
		case OC2_SET			:   TCCR2 |= T2_COM2_SET_OC2;			break;
		case OC2_CLR_OC2_SET_TOP:   TCCR2 |= T2_COM2_CLR_OC2_SET_TOP;	break;
		case OC2_SET_OC2_CLR_TOP:   TCCR2 |= T2_COM2_SET_OC2_CLR_TOP;	break;
		case OC2_CLR_UP_SET_DOWN:   TCCR2 |= T2_COM2_CLR_UP_SET_DOWN;	break;
		case OC2_SET_UP_CLR_DOWN:   TCCR2 |= T2_COM2_SET_UP_CLR_DOWN;	break;
		}

	} break;
	}

	return Local_u8ErrorState;
}
u8		TIMER_u8ChangePrescaler	(	u8 Copy_u8TNum , u8 Copy_u8NewPrescaler		){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8TNum){

	default	:	Local_u8ErrorState = NOK;	break;
	case TIMER_T0	:{
		TCCR0 &= T01_CLK_SLECT_MASKING_VALUE;
		switch (Copy_u8NewPrescaler){
		default	:	Local_u8ErrorState = NOK;	break;
		case  TIMER_OFF		 			 :TCCR0 |= T01_STOP;		 			Timer0_Freq = TIMER_OFF ;			break;
		case  TIMER_PRESCALLER_1		 :TCCR0 |= T01_DIVIDED_BY_1; 			Timer0_Freq = F_CPU/PRESCALER_1	;	break;
		case  TIMER_PRESCALLER_8		 :TCCR0 |= T01_DIVIDED_BY_8; 			Timer0_Freq = F_CPU/PRESCALER_8	;	break;
		case  TIMER_PRESCALLER_64		 :TCCR0 |= T01_DIVIDED_BY_64; 			Timer0_Freq = F_CPU/PRESCALER_64;	break;
		case  TIMER_PRESCALLER_256		 :TCCR0 |= T01_DIVIDED_BY_256; 			Timer0_Freq = F_CPU/PRESCALER_256 ;	break;
		case  TIMER_PRESCALLER_1024		 :TCCR0 |= T01_DIVIDED_BY_1024;			Timer0_Freq = F_CPU/PRESCALER_1024;	break;
		case  TIMER_EXTERNAL_CLK_FALLING :TCCR0 |= T01_EXTRNAL_ON_T01_FALLING; 	Timer0_Freq = EXTERNAL_FALLING;		break;
		case  TIMER_EXTERNAL_CLK_RISING	 :TCCR0 |= T01_EXTRNAL_ON_T01_RISING; 	Timer0_Freq = EXTERNAL_RISING;		break;
		}

	}break;
	case TIMER_T1   :{

		TCCR1B &= T01_CLK_SLECT_MASKING_VALUE;
		switch (Copy_u8NewPrescaler){
		default	:	Local_u8ErrorState = NOK;	break;
		case  TIMER_OFF		 			 :TCCR1B |= T01_STOP;		 			Timer1_Freq = TIMER_OFF ;			break;
		case  TIMER_PRESCALLER_1		 :TCCR1B |= T01_DIVIDED_BY_1; 			Timer1_Freq = F_CPU/PRESCALER_1	;	break;
		case  TIMER_PRESCALLER_8		 :TCCR1B |= T01_DIVIDED_BY_8; 			Timer1_Freq = F_CPU/PRESCALER_8	;	break;
		case  TIMER_PRESCALLER_64		 :TCCR1B |= T01_DIVIDED_BY_64; 			Timer1_Freq = F_CPU/PRESCALER_64;	break;
		case  TIMER_PRESCALLER_256		 :TCCR1B |= T01_DIVIDED_BY_256; 		Timer1_Freq = F_CPU/PRESCALER_256 ;	break;
		case  TIMER_PRESCALLER_1024		 :TCCR1B |= T01_DIVIDED_BY_1024;		Timer1_Freq = F_CPU/PRESCALER_1024;	break;
		case  TIMER_EXTERNAL_CLK_FALLING :TCCR1B |= T01_EXTRNAL_ON_T01_FALLING;	Timer1_Freq = EXTERNAL_FALLING;		break;
		case  TIMER_EXTERNAL_CLK_RISING	 :TCCR1B |= T01_EXTRNAL_ON_T01_RISING; 	Timer1_Freq = EXTERNAL_RISING;		break;
		}

	}
	break;
	case TIMER_T2   : {

		TCCR2 &= T2_CLK_SLECT_MASKING_VALUE;
		switch (Copy_u8NewPrescaler){
		default	:	Local_u8ErrorState = NOK;	break;
		case  TIMER_OFF		 			:TCCR2 |= T2_STOP;		 		Timer2_Freq = TIMER_OFF;	break;
		case  TIMER_PRESCALLER_1	 	:TCCR2 |= T2_DIVIDED_BY_1; 		Timer2_Freq = F_CPU / PRESCALER_1		;	break;
		case  TIMER_PRESCALLER_8	 	:TCCR2 |= T2_DIVIDED_BY_8; 		Timer2_Freq = F_CPU / PRESCALER_8		;	break;
		case  TIMER_PRESCALLER_32		:TCCR2 |= T2_DIVIDED_BY_32; 	Timer2_Freq = F_CPU / PRESCALER_32		;	break;
		case  TIMER_PRESCALLER_64		:TCCR2 |= T2_DIVIDED_BY_64; 	Timer2_Freq = F_CPU / PRESCALER_64		;	break;
		case  TIMER_PRESCALLER_128		:TCCR2 |= T2_DIVIDED_BY_128;	Timer2_Freq = F_CPU / PRESCALER_128		;	break;
		case  TIMER_PRESCALLER_256	 	:TCCR2 |= T2_DIVIDED_BY_256;	Timer2_Freq = F_CPU / PRESCALER_256		;	break;
		case  TIMER_PRESCALLER_1024		:TCCR2 |= T2_DIVIDED_BY_1024;	Timer2_Freq = F_CPU / PRESCALER_1024	; 	break;
		}

	}break;
	}
	return Local_u8ErrorState;

}
//	Schedule (ptrf  , cont, time us)	continuity
u8 		TIMER_u8Schedule		( void ( * ptrf_ScheduleFunc )(void) , u8 Copy_u8Continuity , u8 Copy_u8TimeUS	){

	u8 	Local_u8ErrorState = OK;
	u32 Local_u32OverFlowTimeUS	=	T2_RESOLUTION * ((1/Timer2_Freq)*1000000);
	u16	Local_u8TickTimens 		= 	(1/Timer2_Freq) * 1000000000;

	//Check Null Pointers
	if ( (ptrf_ScheduleFunc != NULL) ){

		//Put Continuity flag as it came from user
		Continuity = Copy_u8Continuity;

		//Get  number of Overflows we need
		ScheduleOverFlow 		= Copy_u8TimeUS/Local_u32OverFlowTimeUS;

		//Get number of of float counts in count format instead of time format
		ScheduleFPreloadCount 	= T2_RESOLUTION - ( Copy_u8TimeUS % Local_u32OverFlowTimeUS );

		//Put the Scheduled Function address
		ScheduleFunc = ptrf_ScheduleFunc;

		//	Put Preload in Count register
		TCNT2 = ScheduleFPreloadCount;

		//	Start Counting by activating Prescaler
		TCCR2 &= T2_CLK_SLECT_MASKING_VALUE;

		TIMER_u8ChangePrescaler(TIMER_T2 ,Timer2_Prescaler );
		//Enable PIE for Overflow Timer2
		SET_BIT(TIMSK , TIMSK_TOIE2);

		//Wait till OverFlow Happen (Go to ISR overflow Timer2)
	}
	//No Address function or Null
	else {
		Local_u8ErrorState = NULL_POINTER;
	}

	return Local_u8ErrorState;
}
void 	TIMER_u8ScheduleDisable	(		void		){

	// Stop Timer2
	TCCR2 	&= T2_CLK_SLECT_MASKING_VALUE;
	TCCR2 	|= T2_STOP;

	// 	Clear Counter Register (TCNT2) for Timer 2
	TCNT2 	= CLR_COUNTER;

	//	Disable PIE
	CLR_BIT(TIMSK , TIMSK_TOIE2);

	// Make Continuity Off
	Continuity = CONTINUITY_OFF;
	//
	ScheduleFunc = NULL;
}
u8		TIMER_u8Disable			(	u8 Copy_u8TNum ){
	u8 Local_u8ErrorState = OK;

	switch (Copy_u8TNum){

	default : Local_u8ErrorState = NOK;break;

	case TIMER_T0:	{
		TIMER_u8ChangePrescaler	(TIMER_T0 , TIMER_OFF);
		TIMER_u8DisableInterrupt(PIE_T0_OV);
		TIMER_u8DisableInterrupt(PIE_T0_COMPARE_MATCH);
	}break;
	case TIMER_T1:	{
		TIMER_u8ChangePrescaler	(TIMER_T1 , TIMER_OFF);
		TIMER_u8DisableInterrupt(PIE_T1_OV);
		TIMER_u8DisableInterrupt(PIE_T1A_COMPARE_MATCH);
		TIMER_u8DisableInterrupt(PIE_T1B_COMPARE_MATCH);
	}break;
	case TIMER_T2:	{
		TIMER_u8ChangePrescaler	(TIMER_T2 , TIMER_OFF);
		TIMER_u8DisableInterrupt(PIE_T2_OV);
		TIMER_u8DisableInterrupt(PIE_T2_COMPARE_MATCH);
	}break;
	}
	return Local_u8ErrorState;
}
u8 		TIMER_u8SetTCNT			( u8 Copy_u8TNum , u16 Copy_u16NewValue	){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8TNum){
	default :	Local_u8ErrorState = NOK;				break;
	case TIMER_T0	: TCNT0 = (u8)	Copy_u16NewValue;	break;
	case TIMER_T1   : TCNT1 = (u16)	Copy_u16NewValue;	break;
	case TIMER_T2   : TCNT2 = (u8)	Copy_u16NewValue;	break;
	}
	return Local_u8ErrorState;
}
u8 		TIMER_u8SetOCR   		( u8 Copy_u8OCRNum , u16 Copy_u16NewValue	){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8OCRNum){

	default :	Local_u8ErrorState = NOK;				break;

	case OCR0_u8_UPDATE		: OCR0 	= (u8)	Copy_u16NewValue;	break;
	case OCR1A_u16_UPDATE	: OCR1A = (u16)	Copy_u16NewValue;	break;
	case OCR1B_u16_UPDATE	: OCR1B = (u16)	Copy_u16NewValue;	break;
	case OCR2_u8_UPDATE		: OCR2 	= (u8)	Copy_u16NewValue;	break;


	}return Local_u8ErrorState;
}
u8 		TIMER_u8SetICR  		( u16 Copy_u16NewValue	){
	u8 Local_u8ErrorState = OK;
	ICR1 = Copy_u16NewValue;
	return Local_u8ErrorState;
}
u8		TIMER_u8Read     		( u8 Copy_u8Reg , u16 * Copy_pu16ReadValue ){
	u8 Local_u8ErrorState = OK;

	switch(Copy_u8Reg){

	default :Local_u8ErrorState = NOK;break;
	case TCCR0_u8_READ   :	*Copy_pu16ReadValue = TCCR0; 	break;
	case TCNT0_u8_READ   :	*Copy_pu16ReadValue = TCNT0; 	break;
	case OCR0_u8_READ    :	*Copy_pu16ReadValue = OCR0;		break;

	case TCCR1A_u8_READ	:	*Copy_pu16ReadValue = TCCR1A; 	break;
	case TCCR1B_u8_READ	:	*Copy_pu16ReadValue = TCCR1B; 	break;
	case OCR1A_u16_READ	:	*Copy_pu16ReadValue = OCR1A;		break;
	case OCR1B_u16_READ	:	*Copy_pu16ReadValue = OCR1B;		break;

	case TCNT1_u16_READ	:	*Copy_pu16ReadValue = TCNT1;  		break;
	case TCCR1_u16_READ	:	*Copy_pu16ReadValue = TCCR1; 		break;
	case ICR1_u16_READ 	:	*Copy_pu16ReadValue = ICR1;			break;

	case TCCR2_u8_READ	:	*Copy_pu16ReadValue = TCCR2; 	break;
	case TCNT2_u8_READ  :	*Copy_pu16ReadValue = TCNT0; 	break;
	case OCR2_u8_READ   :	*Copy_pu16ReadValue = OCR0;		break;

	}
	return Local_u8ErrorState;
}
//Enable Timer Interrupts
u8		TIMER_u8DisableInterrupt(	u8 Copy_u8TimerPIEs){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8TimerPIEs){
	default :	Local_u8ErrorState = NOK;break;
	case PIE_T0_OV				:	CLR_BIT(TIMSK , TIMSK_TOIE0);	break;
	case PIE_T1_OV				:   CLR_BIT(TIMSK , TIMSK_TOIE1);	break;
	case PIE_T2_OV				:   CLR_BIT(TIMSK , TIMSK_TOIE2);	break;
	case PIE_T0_COMPARE_MATCH	:   CLR_BIT(TIMSK , TIMSK_OCIE0);	break;
	case PIE_T1A_COMPARE_MATCH	:   CLR_BIT(TIMSK , TIMSK_OCIE1A);	break;
	case PIE_T1B_COMPARE_MATCH	:   CLR_BIT(TIMSK , TIMSK_OCIE1B);	break;
	case PIE_T2_COMPARE_MATCH	:   CLR_BIT(TIMSK , TIMSK_OCIE2);	break;
	case PIE_INPUT_CAPTURE		:   CLR_BIT(TIMSK , TIMSK_TICIE1);	break;
	}
	return Local_u8ErrorState;
}
//Disable Timer Interrupts
u8		TIMER_u8EnableInterrupt(	u8 Copy_u8TimerPIEs){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8TimerPIEs){
	default :	Local_u8ErrorState = NOK;break;
	case PIE_T0_OV				:	SET_BIT(TIMSK , TIMSK_TOIE0);	break;
	case PIE_T1_OV				:   SET_BIT(TIMSK , TIMSK_TOIE1);	break;
	case PIE_T2_OV				:   SET_BIT(TIMSK , TIMSK_TOIE2);	break;
	case PIE_T0_COMPARE_MATCH	:   SET_BIT(TIMSK , TIMSK_OCIE0);	break;
	case PIE_T1A_COMPARE_MATCH	:   SET_BIT(TIMSK , TIMSK_OCIE1A);	break;
	case PIE_T1B_COMPARE_MATCH	:   SET_BIT(TIMSK , TIMSK_OCIE1B);	break;
	case PIE_T2_COMPARE_MATCH	:   SET_BIT(TIMSK , TIMSK_OCIE2);	break;
	case PIE_INPUT_CAPTURE		:   SET_BIT(TIMSK , TIMSK_TICIE1);	break;
	}
	return Local_u8ErrorState;
}
u8 		TIMER_u8SetISR			( void ( * ptrf_ISRFunc )(void)	, u8 Copy_u8TISR){
	u8 Local_u8ErrorState = OK;
	switch(Copy_u8TISR){
	default:	Local_u8ErrorState = NOK;	break;
	case ISR_T0_OV				:	T0OVFunc 	= ptrf_ISRFunc;	break;
	case ISR_T1_OV				:	T1OVFunc 	= ptrf_ISRFunc; break;
	case ISR_T2_OV				:	T2OVFunc 	= ptrf_ISRFunc; break;
	case ISR_T0_COMPARE_MATCH	:	T0COMPFunc 	= ptrf_ISRFunc;	break;
	case ISR_T1A_COMPARE_MATCH	:	T0COMPFunc 	= ptrf_ISRFunc;	break;
	case ISR_T1B_COMPARE_MATCH	:	T0COMPFunc 	= ptrf_ISRFunc;	break;
	case ISR_T2_COMPARE_MATCH	:	T0COMPFunc 	= ptrf_ISRFunc;	break;
	case ISR_INPUT_CAPTURE		:	ICUFunc 	= ptrf_ISRFunc;	break;
	}
	return Local_u8ErrorState;
}

//	ISR Timer/Counter 0  OverFlow
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void){
	if (T0OVFunc != NULL){
		T0OVFunc();
	}
}

//	ISR Timer/Counter 0  Compare Match
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void){

	if (T0COMPFunc != NULL){
		T0COMPFunc();
	}

}

//	ISR Timer/Counter 1  OverFlow
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void){

	if (T1OVFunc != NULL){
		T1OVFunc();
	}

}


//	ISR Timer/Counter 1  Compare Match	B
void __vector_8 (void) __attribute__((signal));
void __vector_8 (void){

	if (T1BCOMPFunc != NULL){
		T1BCOMPFunc();
	}

}


//	ISR Timer/Counter 1  Compare Match	A
void __vector_7 (void) __attribute__((signal));
void __vector_7 (void){

	if (T1ACOMPFunc != NULL){
		T1ACOMPFunc();
	}

}

//	ISR Timer/Counter 2  OverFlow
void __vector_5 (void) __attribute__((signal));
void __vector_5 (void){
	if (ScheduleFunc != NULL){
		ScheduleFunc();
		if (Continuity == CONTINUITY_OFF){
			TIMER_u8Disable(ScheduleTimer);
		}
	}
	else if (ScheduleFunc == NULL){
		if (T2OVFunc != NULL ){
			T2OVFunc();
		}
	}

}

//	ISR Timer/Counter 2  Compare Match
void __vector_4 (void) __attribute__((signal));
void __vector_4 (void){
	if (T2COMPFunc != NULL){
		T2COMPFunc();
	}
}

