/******************************************************************************************/
/******************************************************************************************/
/*******************************	Author : Ayman Saleh		***************************/
/*******************************	Date   : 26-8-2021			***************************/
/*******************************	Version: 1.0.0				***************************/
/*******************************	Layer  : HAL				***************************/
/*******************************	SWC    : SSD (7 segments)	***************************/
/******************************************************************************************/
/******************************************************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Err_Type.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "SWITCH_config.h"
#include "SWITCH_interface.h"
#include "SWITCH_private.h"


u8 SW_u8Init		(const SW_Type* SW_configuration){

	u8 Local_u8ErrorState = OK;
	if (SW_configuration->PORT <= DIO_u8_PORTD){
		if(SW_configuration->PIN<=DIO_u8_PIN7){

			if (SW_configuration->Pull_State == SW_u8_PULL_UP){
				DIO_u8SetPinValue(SW_configuration->PORT , SW_configuration->PIN , DIO_u8_PIN_HIGH);
			}
			else if (SW_configuration->Pull_State == SW_u8_PULL_DOWN){
				DIO_u8SetPinValue(SW_configuration->PORT , SW_configuration->PIN , DIO_u8_PIN_LOW);
			}
		}
		else Local_u8ErrorState = NOK;
	}
	else Local_u8ErrorState = NOK;
	return Local_u8ErrorState ;
}

u8 SW_u8readSwitch 	(const SW_Type* SW_configuration , u8* copy_u8ReadValue){
//var
	u8 Local_u8ErrorState = OK;
	DIO_u8GetPinValue(SW_configuration->PORT ,SW_configuration->PIN , copy_u8ReadValue);

	if(SW_configuration->Pull_State == SW_u8_PULL_DOWN){
		*copy_u8ReadValue  = (*copy_u8ReadValue );
	}
	else if (SW_configuration->Pull_State == SW_u8_PULL_UP){
		*copy_u8ReadValue =  ( GET_BIT( (~*copy_u8ReadValue ) , 0 )) ;
	}
	else Local_u8ErrorState = NOK ;
	return Local_u8ErrorState;
}
