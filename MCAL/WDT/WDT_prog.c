/*
 * WDT_prog.c
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Err_Type.h"
#include "../../LIB/MATH_FUNC.h"

#include "WDT_private.h"
#include "WDT_config.h"
#include "WDT_interface.h"
#include "WDT_reg.h"

static u8 WDT_PRESCALER = UNDEFINED;

void	WDT_voidInit		(	void	){

#if 	WDT_STATE == ENABLE
	SET_BIT(WDTCR , WDTCR_WDE);
	WDTCR &= PS_MASKING_VALUE;
#if 	WDT_PS == PS_16MS3
	WDTCR |= PS_16MS3;
#elif 	WDT_PS == PS_32MS5
	WDTCR |= PS_32MS5;
#elif 	WDT_PS == PS_65MS
	WDTCR |= PS_65MS;
#elif 	WDT_PS == PS_0S13
	WDTCR |= PS_0S13;
#elif 	WDT_PS == PS_0S26
	WDTCR |= PS_0S26;
#elif 	WDT_PS == PS_0S52
	WDTCR |= PS_0S52;
#elif 	WDT_PS == PS_1S0
	WDTCR |= PS_1S0;
#elif 	WDT_PS == PS_2S1
	WDTCR |= PS_2S1;
#else
#error	"Invalid WDT_PS Configuration"
#endif

#elif	WDT_STATE == DISABLE
	WDTCR = DISABLE_WDT_STEP_1 ;
	WDTCR = DISABLE_WDT_STEP_2 ;
#else
#error	"Invalid WDT_STATE Configuration"
#endif
}
u8 		WDT_u8Enable		(	u8 Copy_u8Time		){
	u8 Local_u8ErrorState = OK;
	if (Copy_u8Time <= WDT_2s1){
		static u8 Local_u8PSArray [8] = { PS_16MS3,PS_32MS5,PS_65MS,PS_0S13,PS_0S26,PS_0S52,PS_1S0,PS_2S1	};
		SET_BIT(WDTCR , WDTCR_WDE);
		WDT_PRESCALER = Copy_u8Time;
		WDTCR &= PS_MASKING_VALUE;
		WDTCR |= Local_u8PSArray[Copy_u8Time-1];
	}
	return Local_u8ErrorState;
}
u8 		WDT_u8ChangeTime	(	u8 Copy_u8Time	){
	u8 Local_u8ErrorState = OK;
	Local_u8ErrorState = WDT_u8Enable(Copy_u8Time);
	return Local_u8ErrorState;
}
u8 		WDT_u8ReEnable		(	void	){
	u8 Local_u8ErrorState = OK;
	Local_u8ErrorState = WDT_u8Enable	(WDT_PS);
	return Local_u8ErrorState;
}
void 	WDT_voidDisable		(	void	){
	WDTCR = DISABLE_WDT_STEP_1 ;
	WDTCR = DISABLE_WDT_STEP_2 ;
}
