/******************************************************************************************/
/******************************************************************************************/
/*******************************	Author : Ayman Saleh		***************************/
/*******************************	Date   : 19-8-2021			***************************/
/*******************************	Version: 1.0.0				***************************/
/*******************************	Layer  : HAL				***************************/
/*******************************	SWC    : SSD (7 segments)	***************************/
/******************************************************************************************/
/******************************************************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Err_Type.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "SSD_config.h"
#include "SSD_interface.h"
#include "SSD_private.h"

#include <util/delay.h>

static u8 MaxNumber ;

u8 SSD_u8Init	 	(const SSD_type* copy_u8SSDObject){

	u8 Local_ErrorState = OK;

	if (copy_u8SSDObject->PORT <= DIO_u8_PORTD){


		if (( copy_u8SSDObject->CommonPin <= DIO_u8_PIN7 ) && ( copy_u8SSDObject->CommonPinPort <= DIO_u8_PORTD) ){

			if (copy_u8SSDObject->CommonMode == SSD_u8_COMMON_CATHODE){
				DIO_u8SetPinValue( copy_u8SSDObject->CommonPinPort , copy_u8SSDObject->CommonPin , DIO_u8_PIN_LOW);
			}
			else if (copy_u8SSDObject->CommonMode == SSD_u8_COMMON_ANODE){
				DIO_u8SetPinValue( copy_u8SSDObject->CommonPinPort , copy_u8SSDObject->CommonPin , DIO_u8_PIN_HIGH);
			}
			else Local_ErrorState = NOK;
		}
		else if (copy_u8SSDObject->CommonPin == SSD_u8_OUTSIDE_UC){
			//	Do Noting
		}
		else {
			Local_ErrorState = NOK;
		}
	}
	else{
		Local_ErrorState = NOK;
	}

	if 	(copy_u8SSDObject->NumberSystem < SSD_u8_DEC ){
		MaxNumber = copy_u8SSDObject->NumberSystem;
	}
	else if ( copy_u8SSDObject->NumberSystem == SSD_u8_DEC ){
			MaxNumber = SSD_u8_DEC;
		}
	else if  ( copy_u8SSDObject->NumberSystem == SSD_u8_HEX){
		MaxNumber = SSD_u8_HEX;
	}
	else {
		Local_ErrorState = NOK;
	}

	return Local_ErrorState;
}

u8 SSD_u8SendNum 	(const SSD_type* copy_u8SSDObject , u8 copy_u8Number){
	static u8 SSDNumbers [] = { SEG_0 ,SEG_1 ,SEG_2 ,SEG_3, SEG_4, SEG_5, SEG_6, SEG_7, SEG_8, SEG_9, SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F  };

	u8 Local_ErrorState = OK;
	if (copy_u8Number >= copy_u8SSDObject->NumberSystem){
		Local_ErrorState = NOK;
	}
	if ( copy_u8SSDObject->CommonMode == SSD_u8_COMMON_CATHODE){
		DIO_u8SetPortValue( copy_u8SSDObject->PORT , SSDNumbers[copy_u8Number]);
	}
	else if ( copy_u8SSDObject->CommonMode == SSD_u8_COMMON_ANODE){
		DIO_u8SetPortValue( copy_u8SSDObject->PORT , ~(SSDNumbers[copy_u8Number]) );
	}
	return Local_ErrorState;
}
void SSD_voidOff	(const SSD_type* copy_u8SSDObject){
	if ( copy_u8SSDObject->CommonMode == SSD_u8_COMMON_CATHODE){
		DIO_u8SetPinValue( copy_u8SSDObject->CommonPinPort , copy_u8SSDObject->CommonPin , 1 );
	}
	else if ( copy_u8SSDObject->CommonMode == SSD_u8_COMMON_ANODE){
		DIO_u8SetPinValue( copy_u8SSDObject->CommonPinPort , copy_u8SSDObject->CommonPin , 0 );
	}
}

void SSD_voidOn	(const SSD_type* copy_u8SSDObject){
	if ( copy_u8SSDObject->CommonMode == SSD_u8_COMMON_CATHODE){
		DIO_u8SetPinValue( copy_u8SSDObject->CommonPinPort , copy_u8SSDObject->CommonPin , 0 );
	}
	else if ( copy_u8SSDObject->CommonMode == SSD_u8_COMMON_ANODE){
		DIO_u8SetPinValue( copy_u8SSDObject->CommonPinPort , copy_u8SSDObject->CommonPin , 1 );
	}
}
