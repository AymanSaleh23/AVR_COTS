/******************************************************************************************************/
/******************************************************************************************************/
/*******************************	Author : Ayman Saleh					***************************/
/*******************************	Date   : 2-9-2021						***************************/
/*******************************	Layer  : MCAL							***************************/
/*******************************	SWC    : General Interrupt Enable (GIE)	***************************/
/*******************************	Version:1.0.0							***************************/
/******************************************************************************************************/
/******************************************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "GIE_reg.h"
#include "GIE_interface.h"


void GIE_voidEnable(void){
	SET_BIT(SREG,SREG_I);

	/*
	 volatile __asm("sei");
	 * */
}
void GIE_voidDisable(void){
	CLR_BIT(SREG,SREG_I);

	/*
	 volatile __asm("cli");
	 * */
}
