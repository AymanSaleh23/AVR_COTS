/*
 * PWM_prog.c
 *
 *  Created on: Sep 21, 2021
 *      Author: 20114
 */


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Err_Type.h"
#include "../../LIB/MATH_FUNC.h"

#include "../TIMER/TIMER_interface.h"
#include "../TIMER/TIMER_private.h"

#include "../ICU/ICU_reg.h"

#include "../PWM/PWM_private.h"
#include "../PWM/PWM_interface.h"
#include "../PWM/PWM_config.h"
#include "../PWM/PWM_reg.h"

static u16 OC1A_MinDuty	= 0;
static u16 OC1A_MaxDuty	= 65534;

static u16 OC1B_MinDuty	= 0;
static u16 OC1B_MaxDuty	= 65534;

static u16 OC0_MinDuty	= 0;
static u16 OC0_MaxDuty	= 255;

static u16 OC2_MinDuty	= 0;
static u16 OC2_MaxDuty	= 255;

static u16 OC1A_MinMapp	= 0;
static u16 OC1A_MaxMapp = 0;

static u16 OC1B_MinMapp = 0;
static u16 OC1B_MaxMapp = 0;

static u16  OC0_MinMapp = 0;
static u16  OC0_MaxMapp = 0;

static u16  OC2_MinMapp = 0;
static u16  OC2_MaxMapp = 0;


u8 PWM_u8Init	(void){
	u8 Local_u8ErrorState = OK;


#if		OC0_MODE == FAST_PWM
	TIMER_u8ChangeMode(TIMER_T0 ,PWM_FAST_MODE);
	PWM_u8Enable(PWM_OC0,PWM_NON_INVERTED,PWM_FAST_MODE);
#elif 	OC0_MODE == PHASE_CORRECT_PWM
	TIMER_u8ChangeMode(TIMER_T0 ,PWM_PHASE_CORRECR_MODE);
#endif

#if		OC2_MODE ==	FAST_PWM
	TIMER_u8ChangeMode(TIMER_T2 ,PWM_FAST_MODE);
	PWM_u8Enable(PWM_OC2,PWM_NON_INVERTED,PWM_FAST_MODE);

#elif 	OC2_MODE == PHASE_CORRECT_PWM
	TIMER_u8ChangeMode(TIMER_T2 ,PWM_PHASE_CORRECR_MODE);
#endif

#if		OC1A_MODE == FAST_PWM
#elif	OC1A_MODE == PWM_PHASE_CORRECT_8BIT
#elif	OC1A_MODE == PWM_PHASE_CORRECT_9BIT
#elif	OC1A_MODE == PWM_PHASE_CORRECT_10BIT
#elif	OC1A_MODE == PWM_FAST_8BIT
#elif	OC1A_MODE == PWM_FAST_9BIT
#elif	OC1A_MODE == PWM_FAST_10BIT
#elif	OC1A_MODE == PWM_PHASE_FRQ_CORRECT_ICR1
#elif	OC1A_MODE == PWM_PHASE_FRQ_CORRECT_OCR1A
#elif	OC1A_MODE == PWM_PHASE_CORRECT_ICR1
	TIMER_u8ChangeMode(TIMER_T1 ,PWM_FAST_ICR1);
	PWM_u8Enable(PWM_OC1A,PWM_NON_INVERTED,PWM_PHASE_CORRECT_8BIT);
#elif	OC1A_MODE == PWM_PHASE_CORRECT_OCR1A
#elif	OC1A_MODE == PWM_FAST_ICR1
#elif	OC1A_MODE == PWM_FAST_OCR1A
#endif

#if		OC1B_MODE == FAST_PWM
#elif	OC1B_MODE == PWM_PHASE_CORRECT_8BIT
#elif	OC1B_MODE == PWM_PHASE_CORRECT_9BIT
#elif	OC1B_MODE == PWM_PHASE_CORRECT_10BIT
#elif	OC1B_MODE == PWM_FAST_8BIT
#elif	OC1B_MODE == PWM_FAST_9BIT
#elif	OC1B_MODE == PWM_FAST_10BIT
#elif	OC1B_MODE == PWM_PHASE_FRQ_CORRECT_ICR1
#elif	OC1B_MODE == PWM_PHASE_FRQ_CORRECT_OCR1A
#elif	OC1B_MODE == PWM_PHASE_CORRECT_ICR1
	TIMER_u8ChangeMode(TIMER_T1 ,PWM_FAST_ICR1);
	PWM_u8Enable(PWM_OC1B,PWM_NON_INVERTED,PWM_PHASE_CORRECT_8BIT);
#elif	OC1B_MODE == PWM_PHASE_CORRECT_OCR1A
#elif	OC1B_MODE == PWM_FAST_ICR1
#elif	OC1B_MODE == PWM_FAST_OCR1A
#endif

#if 	OC0_STATE == ENABLE
	TIMER_u8ChangePrescaler(TIMER_T0, TIMER_PRESCALLER_8);
#elif 	OC0_STATE == DISABLE
#endif

#if 	OC1A_STATE == ENABLE
	TIMER_u8ChangePrescaler(TIMER_T0, TIMER_PRESCALLER_8);
#elif 	OC1A_STATE == DISABLE
#endif

#if 	OC1B_STATE == ENABLE
#elif 	OC1B_STATE == DISABLE
#endif

#if 	OC2_STATE == ENABLE
	TIMER_u8ChangePrescaler(TIMER_T0, TIMER_PRESCALLER_8);
#elif 	OC2_STATE == DISABLE
#endif

	return Local_u8ErrorState;
}
u8 PWM_u8Enable	(	u8	Copy_u8OCPin	, u8 Copy_u8OCMode , u8 Copy_u8PWMPhase ){
	u8 Local_u8ErrorState = OK;

	if (Copy_u8OCMode == PWM_INVERTED){

		switch (Copy_u8OCPin){

		default : Local_u8ErrorState = NOK;	break;

		case PWM_OC0	:	{
			switch (Copy_u8PWMPhase){
			default : Local_u8ErrorState = NOK;		break;

			case PWM_PHASE_CORRECR_MODE	: {
				TIMER_u8ChangeMode(TIMER_T0,PWM_PHASE_CORRECR_MODE);
				TIMER_u8ChangeHWAction(HW_OC0 ,OC0_SET_UP_CLR_DOWN );
			}break;

			case PWM_FAST_MODE			: {
				TIMER_u8ChangeMode(TIMER_T0,PWM_FAST_MODE			);
				TIMER_u8ChangeHWAction(HW_OC0 ,OC0_SET_OC0_CLR_TOP );
			}break;

			}
		}break;
		case PWM_OC1A	:  	{
			switch (Copy_u8PWMPhase){

			default	: Local_u8ErrorState = NOK;		break;
			case  PWM_PHASE_CORRECT_8BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_8BIT	);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_UP_CLR_DOWN );

			}break;
			case  PWM_PHASE_CORRECT_9BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_9BIT	);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_UP_CLR_DOWN );

			}break;
			case  PWM_PHASE_CORRECT_10BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_10BIT	);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_UP_CLR_DOWN );

			}break;
			case  PWM_FAST_8BIT				    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_8BIT				);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_OC1A_CLR_TOP );

			}break;
			case  PWM_FAST_9BIT				    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_9BIT				);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_OC1A_CLR_TOP );
			}break;
			case  PWM_FAST_10BIT       		    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_10BIT       		);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_OC1A_CLR_TOP );
			}break;
			case  PWM_PHASE_FRQ_CORRECT_ICR1    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_FRQ_CORRECT_ICR1 );
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_OC1A_CLR_TOP );

			}break;
			case  PWM_PHASE_FRQ_CORRECT_OCR1A   :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_FRQ_CORRECT_OCR1A);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_OC1A_CLR_TOP );

			}break;
			case  PWM_FAST_ICR1        :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_ICR1     );
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_OC1A_CLR_TOP );

			}break;
			case  PWM_FAST_OCR1A		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_OCR1A	);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_SET_OC1A_CLR_TOP );

			}break;
			}
		}break;

		case PWM_OC1B	:  	{
			switch (Copy_u8PWMPhase){

			default	: Local_u8ErrorState = NOK;		break;
			case  PWM_PHASE_CORRECT_8BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_8BIT	);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_UP_CLR_DOWN );

			}break;
			case  PWM_PHASE_CORRECT_9BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_9BIT	);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_UP_CLR_DOWN );

			}break;
			case  PWM_PHASE_CORRECT_10BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_10BIT	);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_UP_CLR_DOWN );

			}break;
			case  PWM_FAST_8BIT				    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_8BIT				);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_OC1B_CLR_TOP );

			}break;
			case  PWM_FAST_9BIT				    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_9BIT				);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_OC1B_CLR_TOP );
			}break;
			case  PWM_FAST_10BIT       		    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_10BIT       		);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_OC1B_CLR_TOP );
			}break;
			case  PWM_PHASE_FRQ_CORRECT_ICR1    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_FRQ_CORRECT_ICR1 );
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_OC1B_CLR_TOP );

			}break;
			case  PWM_PHASE_FRQ_CORRECT_OCR1A   :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_FRQ_CORRECT_OCR1A);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_OC1B_CLR_TOP );

			}break;
			case  PWM_FAST_ICR1        :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_ICR1     );
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_OC1B_CLR_TOP );

			}break;
			case  PWM_FAST_OCR1A		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_OCR1A	);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_SET_OC1B_CLR_TOP );

			}break;
			}
		}break;
		case PWM_OC2	:   {
			switch (Copy_u8PWMPhase){
			default : Local_u8ErrorState = NOK;		break;

			case PWM_PHASE_CORRECR_MODE	: {
				TIMER_u8ChangeMode(TIMER_T2,PWM_PHASE_CORRECR_MODE);
				TIMER_u8ChangeHWAction(HW_OC2 ,OC2_SET_UP_CLR_DOWN );
			}break;

			case PWM_FAST_MODE			: {
				TIMER_u8ChangeMode(TIMER_T2,PWM_FAST_MODE			);
				TIMER_u8ChangeHWAction(HW_OC2 ,OC2_SET_OC2_CLR_TOP );
			}break;

			}
		}break;
		}
	}

	else if (Copy_u8OCMode == PWM_NON_INVERTED){

		switch (Copy_u8OCPin){

		default : Local_u8ErrorState = NOK;	break;

		case PWM_OC0	:	{
			switch (Copy_u8PWMPhase){
			default : Local_u8ErrorState = NOK;		break;

			case PWM_PHASE_CORRECR_MODE	: {
				TIMER_u8ChangeMode(TIMER_T0,PWM_PHASE_CORRECR_MODE);
				TIMER_u8ChangeHWAction(HW_OC0 ,OC0_CLR_UP_SET_DOWN );
			}break;

			case PWM_FAST_MODE			: {
				TIMER_u8ChangeMode(TIMER_T0,PWM_FAST_MODE			);
				TIMER_u8ChangeHWAction(HW_OC0 ,OC0_CLR_OC0_SET_TOP );
			}break;

			}
		}break;
		case PWM_OC1A	:  	{
			switch (Copy_u8PWMPhase){

			default	: Local_u8ErrorState = NOK;		break;
			case  PWM_PHASE_CORRECT_8BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_8BIT	);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_UP_SET_DOWN );

			}break;
			case  PWM_PHASE_CORRECT_9BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_9BIT	);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_UP_SET_DOWN );

			}break;
			case  PWM_PHASE_CORRECT_10BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_10BIT	);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_UP_SET_DOWN );

			}break;
			case  PWM_FAST_8BIT				    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_8BIT				);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_OC1A_SET_TOP );

			}break;
			case  PWM_FAST_9BIT				    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_9BIT				);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_OC1A_SET_TOP );
			}break;
			case  PWM_FAST_10BIT       		    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_10BIT       		);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_OC1A_SET_TOP );
			}break;
			case  PWM_PHASE_FRQ_CORRECT_ICR1    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_FRQ_CORRECT_ICR1 );
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_OC1A_SET_TOP );

			}break;
			case  PWM_PHASE_FRQ_CORRECT_OCR1A   :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_FRQ_CORRECT_OCR1A);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_OC1A_SET_TOP );

			}break;
			case  PWM_FAST_ICR1        :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_ICR1     );
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_OC1A_SET_TOP );

			}break;
			case  PWM_FAST_OCR1A		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_OCR1A	);
				TIMER_u8ChangeHWAction(HW_OC1A ,OC1A_CLR_OC1A_SET_TOP );

			}break;
			}
		}break;

		case PWM_OC1B	:  	{
			switch (Copy_u8PWMPhase){

			default	: Local_u8ErrorState = NOK;		break;
			case  PWM_PHASE_CORRECT_8BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_8BIT	);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_UP_SET_DOWN );

			}break;
			case  PWM_PHASE_CORRECT_9BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_9BIT	);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_OC1B_SET_TOP );

			}break;
			case  PWM_PHASE_CORRECT_10BIT		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_CORRECT_10BIT	);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_UP_SET_DOWN );

			}break;
			case  PWM_FAST_8BIT				    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_8BIT				);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_OC1B_SET_TOP );

			}break;
			case  PWM_FAST_9BIT				    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_9BIT				);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_OC1B_SET_TOP );
			}break;
			case  PWM_FAST_10BIT       		    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_10BIT       		);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_OC1B_SET_TOP );
			}break;
			case  PWM_PHASE_FRQ_CORRECT_ICR1    :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_FRQ_CORRECT_ICR1 );
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_OC1B_SET_TOP );

			}break;
			case  PWM_PHASE_FRQ_CORRECT_OCR1A   :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_PHASE_FRQ_CORRECT_OCR1A);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_OC1B_SET_TOP );

			}break;
			case  PWM_FAST_ICR1        :{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_ICR1     );
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_OC1B_SET_TOP );

			}break;
			case  PWM_FAST_OCR1A		:{
				TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_OCR1A	);
				TIMER_u8ChangeHWAction(HW_OC1B ,OC1B_CLR_OC1B_SET_TOP );

			}break;
			}
		}break;
		case PWM_OC2	:   {
			switch (Copy_u8PWMPhase){
			default : Local_u8ErrorState = NOK;		break;

			case PWM_PHASE_CORRECR_MODE	: {
				TIMER_u8ChangeMode(TIMER_T2,PWM_PHASE_CORRECR_MODE);
				TIMER_u8ChangeHWAction(HW_OC2 ,OC2_CLR_UP_SET_DOWN );
			}break;

			case PWM_FAST_MODE			: {
				TIMER_u8ChangeMode(TIMER_T2,PWM_FAST_MODE			);
				TIMER_u8ChangeHWAction(HW_OC2 ,OC2_CLR_OC2_SET_TOP );
			}break;

			}
		}break;
		}
	}
	return Local_u8ErrorState;
}
u8 PWM_u8Disable(	u16 Copy_u8OCPin		){
	u8 Local_u8ErrorStete = OK;

	switch(Copy_u8OCPin){

	default : Local_u8ErrorStete = NOK; break;
	case PWM_OC0	:	TIMER_u8ChangeHWAction(HW_OC0 ,OC0_NO_HW_ACTION 	);	break;
	case PWM_OC1A	:	TIMER_u8ChangeHWAction(HW_OC1A,OC1A_NO_HW_ACTION 	);	break;
	case PWM_OC1B	:	TIMER_u8ChangeHWAction(HW_OC1B,OC1B_NO_HW_ACTION 	);	break;
	case PWM_OC2	:	TIMER_u8ChangeHWAction(HW_OC2 ,OC0_NO_HW_ACTION 	);	break;
	}
	return Local_u8ErrorStete;
}
u8 PWM_u8SetPeriodus(	u16 Copy_u16Periodus	, u16 Copy_u16MaxDutyus	, u16 Copy_u16MinDutyus){
	u8 Local_u8ErrorStete = OK;

	u16 Local_Period = (F_CPU/8000000) * Copy_u16Periodus;

	OC1A_MinDuty = Copy_u16MinDutyus;
	OC1B_MinDuty = Copy_u16MinDutyus;
	OC1A_MaxDuty = Copy_u16MaxDutyus;
	OC1B_MaxDuty = Copy_u16MaxDutyus;

	TIMER_u8SetICR(Local_Period);

	TIMER_u8ChangeMode(TIMER_T1,PWM_FAST_ICR1);
	return Local_u8ErrorStete;
}
u8 PWM_u8SetMappedRanges(u8 Copy_u8PWMchannel , u16 Copy_u16Max , u16 Copy_u16Min){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8PWMchannel){
	case PWM_OC0	:	OC0_MaxMapp  = Copy_u16Max ;OC0_MinMapp  = Copy_u16Min;	break;
	case PWM_OC1A	:	OC1A_MaxMapp = Copy_u16Max ;OC1A_MinMapp = Copy_u16Min;	break;
	case PWM_OC1B	:	OC1B_MaxMapp = Copy_u16Max ;OC1B_MinMapp = Copy_u16Min;	break;
	case PWM_OC2	:	OC2_MaxMapp  = Copy_u16Max ;OC2_MinMapp  = Copy_u16Min;	break;
	}
	return Local_u8ErrorState;
}
u8 PWM_u8SetDuty(	u16 	Copy_u16ValueInRange	,	u8 Copy_u8OCPin	){
	u8 Local_u8ErrorStete = OK;
	switch (Copy_u8OCPin){
	default : Local_u8ErrorStete = NOK;	break;
	case PWM_OC0	:OCR0 	= MAPPING(OC0_MaxMapp , OC0_MinMapp , OC0_MaxDuty   ,  OC0_MinDuty   , Copy_u16ValueInRange%(OC0_MaxMapp+1 ));	break;
	case PWM_OC2	:OCR2 	= MAPPING(OC2_MaxMapp , OC2_MinMapp , OC2_MaxDuty   ,  OC2_MinDuty   , Copy_u16ValueInRange%(OC2_MaxMapp+1 ));	break;
	case PWM_OC1A	:OCR1A 	= MAPPING(OC1A_MaxMapp, OC1A_MinMapp, OC1A_MaxDuty  ,  OC1A_MinDuty  , Copy_u16ValueInRange%(OC1A_MaxMapp+1));	break;
	case PWM_OC1B	:OCR1B 	= MAPPING(OC1B_MaxMapp, OC1B_MinMapp, OC1B_MaxDuty  ,  OC1B_MinDuty  , Copy_u16ValueInRange%(OC1B_MaxMapp+1));	break;

	}

	return Local_u8ErrorStete ;
}
u8 PWM_u8SetPrescaler(	u8 Copy_u8PWMchannel , u8 Copy_u8Prescaler	){
	u8 Local_u8ErrorState = OK;
	if (Copy_u8PWMchannel == PWM_OC2){
		switch (Copy_u8Prescaler){
		default : Local_u8ErrorState = NOK;break;
		case TIMER_PRESCALLER_32:{
			switch (Copy_u8PWMchannel){

			case PWM_OC2	:	TIMER_u8ChangePrescaler(TIMER_T2, TIMER_PRESCALLER_1024);break;
			}
		}break;
		case TIMER_PRESCALLER_128:{
			switch (Copy_u8PWMchannel){

			case PWM_OC2	:	TIMER_u8ChangePrescaler(TIMER_T2, TIMER_PRESCALLER_1024);break;
			}
		}break;
		}
	}
	switch (Copy_u8Prescaler){

	default :	Local_u8ErrorState = NOK; break;

	case PWM_PRESCALLER_1	:{
		switch (Copy_u8PWMchannel){
		case PWM_OC0	:	TIMER_u8ChangePrescaler(TIMER_T0, TIMER_PRESCALLER_1);break;
		case PWM_OC1A	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_1);break;
		case PWM_OC1B	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_1);break;
		case PWM_OC2	:	TIMER_u8ChangePrescaler(TIMER_T2, TIMER_PRESCALLER_1);break;
		}
	}break;
	case PWM_PRESCALLER_8	:{
		switch (Copy_u8PWMchannel){
		case PWM_OC0	:	TIMER_u8ChangePrescaler(TIMER_T0, TIMER_PRESCALLER_8);break;
		case PWM_OC1A	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_8);break;
		case PWM_OC1B	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_8);break;
		case PWM_OC2	:	TIMER_u8ChangePrescaler(TIMER_T2, TIMER_PRESCALLER_8);break;
		}
	}break;
	case PWM_PRESCALLER_64	:{
		switch (Copy_u8PWMchannel){
		case PWM_OC0	:	TIMER_u8ChangePrescaler(TIMER_T0, TIMER_PRESCALLER_64);break;
		case PWM_OC1A	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_64);break;
		case PWM_OC1B	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_64);break;
		case PWM_OC2	:	TIMER_u8ChangePrescaler(TIMER_T2, TIMER_PRESCALLER_64);break;
		}
	}break;
	case PWM_PRESCALLER_256	:{
		switch (Copy_u8PWMchannel){
		case PWM_OC0	:	TIMER_u8ChangePrescaler(TIMER_T0, TIMER_PRESCALLER_256);break;
		case PWM_OC1A	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_256);break;
		case PWM_OC1B	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_256);break;
		case PWM_OC2	:	TIMER_u8ChangePrescaler(TIMER_T2, TIMER_PRESCALLER_256);break;
		}
	}break;
	case PWM_PRESCALLER_1024:{
		switch (Copy_u8PWMchannel){
		case PWM_OC0	:	TIMER_u8ChangePrescaler(TIMER_T0, TIMER_PRESCALLER_1024);break;
		case PWM_OC1A	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_1024);break;
		case PWM_OC1B	:	TIMER_u8ChangePrescaler(TIMER_T1, TIMER_PRESCALLER_1024);break;
		case PWM_OC2	:	TIMER_u8ChangePrescaler(TIMER_T2, TIMER_PRESCALLER_1024);break;
		}
	}break;
	}


	return Local_u8ErrorState;
}
