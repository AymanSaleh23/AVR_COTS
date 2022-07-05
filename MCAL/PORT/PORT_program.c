/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 27-8-2021		***************************/
/*******************************	Layer  : MCAL			***************************/
/*******************************	SWC    : PORT			***************************/
/*******************************	Version:1.0.0			***************************/
/**************************************************************************************/
/**************************************************************************************/

#include "../../LIB/STD_TYPES.h"

#include "PORT_private.h"
#include "PORT_config.h"
#include "PORT_reg.h"
#include "PORT_interface.h"

#include "../DIO/DIO_interface.h"

void PORT_voidInit(void){

	DDRA = CONC(PORT_u8_A7_DIRECTION,PORT_u8_A6_DIRECTION,PORT_u8_A5_DIRECTION,PORT_u8_A4_DIRECTION,PORT_u8_A3_DIRECTION,PORT_u8_A2_DIRECTION,PORT_u8_A1_DIRECTION,PORT_u8_A0_DIRECTION);
	DDRB = CONC(PORT_u8_B7_DIRECTION,PORT_u8_B6_DIRECTION,PORT_u8_B5_DIRECTION,PORT_u8_B4_DIRECTION,PORT_u8_B3_DIRECTION,PORT_u8_B2_DIRECTION,PORT_u8_B1_DIRECTION,PORT_u8_B0_DIRECTION);
	DDRC = CONC(PORT_u8_C7_DIRECTION,PORT_u8_C6_DIRECTION,PORT_u8_C5_DIRECTION,PORT_u8_C4_DIRECTION,PORT_u8_C3_DIRECTION,PORT_u8_C2_DIRECTION,PORT_u8_C1_DIRECTION,PORT_u8_C0_DIRECTION);
	DDRD = CONC(PORT_u8_D7_DIRECTION,PORT_u8_D6_DIRECTION,PORT_u8_D5_DIRECTION,PORT_u8_D4_DIRECTION,PORT_u8_D3_DIRECTION,PORT_u8_D2_DIRECTION,PORT_u8_D1_DIRECTION,PORT_u8_D0_DIRECTION);

	PORTA = CONC(PORT_u8_A7_INITIAL_Value,PORT_u8_A6_INITIAL_Value,PORT_u8_A5_INITIAL_Value,PORT_u8_A4_INITIAL_Value,PORT_u8_A3_INITIAL_Value,PORT_u8_A2_INITIAL_Value,PORT_u8_A1_INITIAL_Value,PORT_u8_A0_INITIAL_Value);
	PORTB = CONC(PORT_u8_B7_INITIAL_Value,PORT_u8_B6_INITIAL_Value,PORT_u8_B5_INITIAL_Value,PORT_u8_B4_INITIAL_Value,PORT_u8_B3_INITIAL_Value,PORT_u8_B2_INITIAL_Value,PORT_u8_B1_INITIAL_Value,PORT_u8_B0_INITIAL_Value);
	PORTC = CONC(PORT_u8_C7_INITIAL_Value,PORT_u8_C6_INITIAL_Value,PORT_u8_C5_INITIAL_Value,PORT_u8_C4_INITIAL_Value,PORT_u8_C3_INITIAL_Value,PORT_u8_C2_INITIAL_Value,PORT_u8_C1_INITIAL_Value,PORT_u8_C0_INITIAL_Value);
	PORTD = CONC(PORT_u8_D7_INITIAL_Value,PORT_u8_D6_INITIAL_Value,PORT_u8_D5_INITIAL_Value,PORT_u8_D4_INITIAL_Value,PORT_u8_D3_INITIAL_Value,PORT_u8_D2_INITIAL_Value,PORT_u8_D1_INITIAL_Value,PORT_u8_D0_INITIAL_Value);

}
