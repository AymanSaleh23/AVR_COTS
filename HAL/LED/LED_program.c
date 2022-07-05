/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 12-8-2021		***************************/
/*******************************	Version: 1.0.0			***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : LED			***************************/
/**************************************************************************************/
/**************************************************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../LIB/Err_Type.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "LED_config.h"
#include "LED_private.h"
#include "LED_interface.h"



u8 LED_u8TurnOff(const LED_Type* LED_configuration){
	u8 Local_u8ErrorState = OK;
	if (LED_configuration->PORT <= DIO_u8_PORTD ){
		if (LED_configuration->PIN <= DIO_u8_PIN7 ){
			DIO_u8SetPinValue(LED_configuration->PORT , LED_configuration->PIN , 1&(~(LED_configuration->MODE)) );
		}
		else {
			Local_u8ErrorState = NOK;
		}
	}
	else {
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

u8 LED_u8TurnOn	(const LED_Type* LED_configuration){
	u8 Local_u8ErrorState = OK;
	if (LED_configuration->PORT <= DIO_u8_PORTD ){
		if (LED_configuration->PIN <= DIO_u8_PIN7 ){
			DIO_u8SetPinValue(LED_configuration->PORT , LED_configuration->PIN , (LED_configuration->MODE) );
		}
		else {
			Local_u8ErrorState = NOK;
		}
	}
	else {
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}

void LED_voidTogg	(const LED_Type* LED_configuration ){
	DIO_u8ToggPin(LED_configuration->PORT , LED_configuration->PIN);
}

