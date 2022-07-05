/*
 * ICU_prog.c
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Err_Type.h"
#include "../../LIB/MATH_FUNC.h"

#include "../TIMER/TIMER_interface.h"
#include "ICU_private.h"
#include "ICU_config.h"
#include "ICU_interface.h"
#include "ICU_reg.h"

static u8  Edge 	= 0;
static ICU_Data * ICUData = {0};
static u8 Polarity = NON_INVERTED;
static u8 ISRAction = ICU_NORMAL_MODE;

static void (* NotificationICU)(void) = NULL;

void ICU_u8Init		( 	void	){

#if ICU_STATE == ENABLE
	SET_BIT(TIMSK ,TIMSK_TICIE1);
#if ICU_MODE == NORMAL_MODE
	ISRAction = ICU_NORMAL_MODE;
#elif ICU_MODE == ICU_EDGE_MODE
	ISRAction = ICU_EDGE_MODE;
#else
#error	"Invalid ICU_MODE Configuration"
#endif

#elif ICU_STATE == DISABLE
	CLR_BIT(TIMSK ,TIMSK_TICIE1);
#else
#error	"Invalid ICU_STATE Configuration"
#endif

#if 	ICU_POLARITY == NON_IVERTED
	Polarity = ICU_NON_INVERTED;
#elif 	ICU_POLARITY == IVERTED
	Polarity = ICU_INVERTED;
#else
#error	"Invalid ICU_POLARITY Configuration"
#endif

#if 	ICU_EDGE_SELECT == RISING_EDGE
	SET_BIT(TCCR1B, TCCR1B_ICES1);
	Edge = ICU_RISING;
#elif	ICU_EDGE_SELECT == FALLING_EDGE
	CLR_BIT(TCCR1B, TCCR1B_ICES1);
	Edge = ICU_FALLING;
#else
#error	"Invalid ICU_EDGE_SELECT Configuration"
#endif

#if 	ICU_NOICE_CANCLER == ENABLE
	SET_BIT(TCCR1B, TCCR1B_ICNC1);
#elif	ICU_NOICE_CANCLER == DISABLE
	CLR_BIT(TCCR1B, TCCR1B_ICNC1);
#else
#error	"Invalid ICU_NOICE_CANCLER Configuration"
#endif
	SET_BIT(TIMSK , TIMSK_TICIE1);
}
u8 ICU_u8Enable		( 	u8 Copy_u8Polarity , u8 Copy_u8EdgeSelect	){
	u8 Local_u8ErreorState = OK;
	SET_BIT(TIMSK ,TIMSK_TICIE1);

	if (ICU_NON_INVERTED == Copy_u8Polarity){
		Polarity = ICU_NON_INVERTED;
	}
	else if (ICU_INVERTED == Copy_u8Polarity){
		Polarity = ICU_INVERTED;
	}else {
		Local_u8ErreorState = NOK;
	}
	if (ICU_RISING == Copy_u8EdgeSelect){
		SET_BIT(TCCR1B, TCCR1B_ICES1);
		Edge = ICU_RISING;
	}
	else if (ICU_FALLING == Copy_u8EdgeSelect){
		CLR_BIT(TCCR1B, TCCR1B_ICES1);
		Edge = ICU_FALLING;
	}
	else {
		Local_u8ErreorState = NOK;
	}
	return Local_u8ErreorState;
}
void ICU_voidDisable	( 	void	){
	CLR_BIT(TIMSK  , TIMSK_TICIE1);
	CLR_BIT(TCCR1B , TCCR1B_ICNC1);
}
u8 ICU_u8ChangeEdgeSelect	(	u8 Copy_u8EdgeSelect	){
	u8 Local_u8ErreorState = OK;
	if (ICU_RISING == Copy_u8EdgeSelect){
		SET_BIT(TCCR1B, TCCR1B_ICES1);
		Edge = ICU_RISING;
	}
	else if (ICU_FALLING == Copy_u8EdgeSelect){
		CLR_BIT(TCCR1B, TCCR1B_ICES1);
		Edge = ICU_FALLING;
	}
	else {
		Local_u8ErreorState = NOK;
	}
	return Local_u8ErreorState;
}
u8 ICU_u8ChangePolarity		(	u8 Copy_u8Polarity	){
	u8 Local_u8ErreorState = OK;
	if (ICU_NON_INVERTED == Copy_u8Polarity){
		Polarity = ICU_NON_INVERTED;
	}
	else if (ICU_INVERTED == Copy_u8Polarity){
		Polarity = ICU_INVERTED;
	}
	else {
		Local_u8ErreorState = NOK;
	}
	return Local_u8ErreorState;
}
u8 ICU_u8GetData	( 	ICU_Data * CopyObj_ICUData ){
	u8 Local_u8ErreorState = OK;
	if (CopyObj_ICUData != NULL){
		ICUData = CopyObj_ICUData;
		ISRAction = ICU_NORMAL_MODE;
	}
	else {
		Local_u8ErreorState = NULL_POINTER;
	}
	return Local_u8ErreorState;
}
u8 ICU_u8SenseEdge( u8 Copy_u8Edge , void(ptr8_NotificationICU)(void) ){
	u8 Local_u8ErreorState = OK;
	if (ptr8_NotificationICU != NULL){
		if ( ISRAction == ICU_EDGE_MODE ){
			ICU_u8ChangeEdgeSelect( Copy_u8Edge );
			NotificationICU = ptr8_NotificationICU;
			ISRAction = ICU_EDGE_MODE;
		}
		else{
			Local_u8ErreorState = NOK;
		}
	}
	else {
		Local_u8ErreorState = NULL_POINTER;
	}

	return Local_u8ErreorState;
}
u8 ICU_u8SenseMode ( u8 Copy_u8Mode){
	u8 Local_u8ErrorState = OK;
	if (Copy_u8Mode == ICU_NORMAL_MODE){
		ICU_u8ChangePolarity(NON_INVERTED);
		ICU_u8ChangeEdgeSelect(ICU_RISING);
		ISRAction = ICU_NORMAL_MODE;
	}
	else if (Copy_u8Mode == ICU_EDGE_MODE){
		ISRAction = ICU_EDGE_MODE;
	}
	else {
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
u8 LCU_u8NoiceCanceler		( u8 Copy_u8Case){
	u8 Local_u8ErrorState = OK;
	if (ICU_NOISE_CANCELER_ENABLE == Copy_u8Case){
		SET_BIT(TCCR1B , TCCR1B_ICNC1);
	}
	else if (ICU_NOISE_CANCELER_DISABLE == Copy_u8Case){
		CLR_BIT(TCCR1B , TCCR1B_ICNC1);
	}
	else {
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState ;
}

void __vector_6 (void) __attribute__ ((signal));
void __vector_6 (void){
	if (ISRAction == ICU_EDGE_MODE){
		if (NotificationICU != NULL){
			NotificationICU();
		}
	}
	else if (ISRAction == ICU_NORMAL_MODE){
		static u8 Local_u8Counter = 0;
		static u16 Local_u16Edge [3];

		Local_u8Counter++;

		if (3 > Local_u8Counter ){
			TIMER_u8Read(TCNT1_u16_READ, &(Local_u16Edge[Local_u8Counter-1]));
			if (2 == Local_u8Counter){
				ICU_u8ChangeEdgeSelect(ICU_FALLING);
			}
		}
		else if (3 == Local_u8Counter){
			ICUData->Period = Local_u16Edge[EDGE_1]-Local_u16Edge[EDGE_0];
			switch ( Polarity ){
			case NON_INVERTED:
				ICUData->OnTime = Local_u16Edge[EDGE_2]-Local_u16Edge[EDGE_1];
				ICUData->OffTime= ICUData->Period-ICUData->OnTime;
				break;
			case INVERTED:
				ICUData->OffTime = Local_u16Edge[EDGE_2]-Local_u16Edge[EDGE_1];
				ICUData->OnTime= ICUData->Period-ICUData->OnTime;
				break;
			}
			ICUData->Duty	= ICUData->OnTime/ICUData->Period;
			Local_u8Counter=0;
		}
	}

}
