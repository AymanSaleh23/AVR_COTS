/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 31-8-2021		***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : DC MOTOR		***************************/
/*******************************	Version: 1.0.0			***************************/
/**************************************************************************************/
/**************************************************************************************/


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "DCMOTOR_interface.h"
#include "DCMOTOR_private.h"

#include "../../MCAL/DIO/DIO_interface.h"

void DCMOTOR_voidStop	( const DC_MOTOR_Type * Copy_MOTORObj){
	if ( ( DIO_u8_PIN7 >= Copy_MOTORObj->PINA ) && (( DIO_u8_PORTD >= Copy_MOTORObj->PORT ) ) ){
		DIO_u8SetPinValue(Copy_MOTORObj->PORT , Copy_MOTORObj->PINA , MOTOR_OFF);
		DIO_u8SetPinValue(Copy_MOTORObj->PORT , Copy_MOTORObj->PINB , MOTOR_OFF);
	}
}
void DCMOTOR_voidCW		( const DC_MOTOR_Type * Copy_MOTORObj){
	if ( ( DIO_u8_PIN7 >= Copy_MOTORObj->PINA ) && (( DIO_u8_PORTD >= Copy_MOTORObj->PORT ) ) ){
		DIO_u8SetPinValue(Copy_MOTORObj->PORT , Copy_MOTORObj->PINA , MOTOR_OFF);
		DIO_u8SetPinValue(Copy_MOTORObj->PORT , Copy_MOTORObj->PINB , MOTOR_ON);
	}
}

void DCMOTOR_voidCCW	( const DC_MOTOR_Type * Copy_MOTORObj){
	if ( ( DIO_u8_PIN7 >= Copy_MOTORObj->PINA ) && (( DIO_u8_PORTD >= Copy_MOTORObj->PORT ) ) ){
		DIO_u8SetPinValue(Copy_MOTORObj->PORT , Copy_MOTORObj->PINB , MOTOR_OFF);
		DIO_u8SetPinValue(Copy_MOTORObj->PORT , Copy_MOTORObj->PINA , MOTOR_ON);
	}
}
