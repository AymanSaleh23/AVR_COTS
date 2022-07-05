/*
 * RELAY_prog.c
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Err_Type.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "RELAY_private.h"
#include "RELAY_config.h"
#include "RELAY_interface.h"


u8 RELAY_u8Operation	(	const RELAY_Type * Copy_RelayObj , u8 Copy_u8Operation){
	u8 Local_u8ErrorState = OK;
	if ( (Copy_RelayObj->PORT <= DIO_u8_PORTD) && (Copy_RelayObj->PIN <= DIO_u8_PIN7) ){
		switch (Copy_u8Operation){
		default			: Local_u8ErrorState = NOK;	break;
		case RELAY_ON	: DIO_u8SetPinValue(Copy_RelayObj->PORT  , Copy_RelayObj->PIN , DIO_u8_PIN_HIGH);break;
		case RELAY_OFF 	: DIO_u8SetPinValue(Copy_RelayObj->PORT  , Copy_RelayObj->PIN , DIO_u8_PIN_LOW); break;
		}
	}
	else {
		Local_u8ErrorState = NOK;
	}
	return Local_u8ErrorState;
}
