/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 26-8-2021		***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : CLCD			***************************/
/*******************************	Version: 1.0.0			***************************/
/**************************************************************************************/
/**************************************************************************************/


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_ExtraChar.h"

#include <util/delay.h>

u8 	CustomChar [8][8] = {
		{	CLCD_CUSTOM_CHAR0_BYTE0,CLCD_CUSTOM_CHAR0_BYTE1,CLCD_CUSTOM_CHAR0_BYTE2,CLCD_CUSTOM_CHAR0_BYTE3,CLCD_CUSTOM_CHAR0_BYTE4,CLCD_CUSTOM_CHAR0_BYTE5,CLCD_CUSTOM_CHAR0_BYTE6 },
		{	CLCD_CUSTOM_CHAR1_BYTE0,CLCD_CUSTOM_CHAR1_BYTE1,CLCD_CUSTOM_CHAR1_BYTE2,CLCD_CUSTOM_CHAR1_BYTE3,CLCD_CUSTOM_CHAR1_BYTE4,CLCD_CUSTOM_CHAR1_BYTE5,CLCD_CUSTOM_CHAR1_BYTE6	},
		{	CLCD_CUSTOM_CHAR2_BYTE0,CLCD_CUSTOM_CHAR2_BYTE1,CLCD_CUSTOM_CHAR2_BYTE2,CLCD_CUSTOM_CHAR2_BYTE3,CLCD_CUSTOM_CHAR2_BYTE4,CLCD_CUSTOM_CHAR2_BYTE5,CLCD_CUSTOM_CHAR2_BYTE6	},
		{	CLCD_CUSTOM_CHAR3_BYTE0,CLCD_CUSTOM_CHAR3_BYTE1,CLCD_CUSTOM_CHAR3_BYTE2,CLCD_CUSTOM_CHAR3_BYTE3,CLCD_CUSTOM_CHAR3_BYTE4,CLCD_CUSTOM_CHAR3_BYTE5,CLCD_CUSTOM_CHAR3_BYTE6	},
		{	CLCD_CUSTOM_CHAR4_BYTE0,CLCD_CUSTOM_CHAR4_BYTE1,CLCD_CUSTOM_CHAR4_BYTE2,CLCD_CUSTOM_CHAR4_BYTE3,CLCD_CUSTOM_CHAR4_BYTE4,CLCD_CUSTOM_CHAR4_BYTE5,CLCD_CUSTOM_CHAR4_BYTE6	},
		{	CLCD_CUSTOM_CHAR5_BYTE0,CLCD_CUSTOM_CHAR5_BYTE1,CLCD_CUSTOM_CHAR5_BYTE2,CLCD_CUSTOM_CHAR5_BYTE3,CLCD_CUSTOM_CHAR5_BYTE4,CLCD_CUSTOM_CHAR5_BYTE5,CLCD_CUSTOM_CHAR5_BYTE6	},
		{	CLCD_CUSTOM_CHAR6_BYTE0,CLCD_CUSTOM_CHAR6_BYTE1,CLCD_CUSTOM_CHAR6_BYTE2,CLCD_CUSTOM_CHAR6_BYTE3,CLCD_CUSTOM_CHAR6_BYTE4,CLCD_CUSTOM_CHAR6_BYTE5,CLCD_CUSTOM_CHAR6_BYTE6	},
		{	CLCD_CUSTOM_CHAR7_BYTE0,CLCD_CUSTOM_CHAR7_BYTE1,CLCD_CUSTOM_CHAR7_BYTE2,CLCD_CUSTOM_CHAR7_BYTE3,CLCD_CUSTOM_CHAR7_BYTE4,CLCD_CUSTOM_CHAR7_BYTE5,CLCD_CUSTOM_CHAR7_BYTE6	}
	};


void CLCD_voidInit           	( void){

	u8 LOC_u8FunctionSet 	=	CLCD_u8_FUNCTION_SET; 	// 0011NFxx  0010NFxx
	u8 LOC_u8DisplayOnOff	=	CLCD_u8_DISPLAY_ON_OFF;	// 			 00001111
#if CLCD_u8_INTERFACE_LINES == LINES_8
	_delay_ms(40);
	//Function Set
	CLCD_voidSendCmd(LOC_u8FunctionSet);
	//Display ON/OFF Control
	CLCD_voidSendCmd(LOC_u8DisplayOnOff);
	//Display Control
	CLCD_voidSendCmd(CLCD_u8_DISPLAY_CLEAR);
	_delay_ms(1);

#elif CLCD_u8_INTERFACE_LINES == LINES_4
	//Function Set
	CLCD_voidSendCmd( 0b00100000			);
	CLCD_voidSendCmd( LOC_u8FunctionSet 	);
	//Display ON/OFF Control
	CLCD_voidSendCmd( 0b00000000			);
	CLCD_voidSendCmd( LOC_u8DisplayOnOff	);
	//Display Control
	CLCD_voidSendCmd( CLCD_u8_DISPLAY_CLEAR	);
	_delay_ms(2);
#endif

}								/*0010NFxx
 	 	 	 	 	 	 	 	  0010NFxx
 	 	 	 	 	 	 	 	 */
void CLCD_voidSendCmd    		( u8 Copy_u8Command ){
	DIO_u8SetPinValue		(CLCD_u8_CTRL_PORT_CONFIG,CLCD_RW_CONFIG , DIO_u8_PIN_LOW);
	DIO_u8SetPinValue		(CLCD_u8_CTRL_PORT_CONFIG,CLCD_RS_CONFIG , DIO_u8_PIN_LOW);

#if CLCD_u8_INTERFACE_LINES == LINES_8

	DIO_u8SetPortValue		(CLCD_u8_DATA_PORT_CONFIG, Copy_u8Command);


#elif CLCD_u8_INTERFACE_LINES == LINES_4
	if ( 0b00100000 ==  Copy_u8Command ){
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D7,  GET_BIT(Copy_u8Command,7) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D6,  GET_BIT(Copy_u8Command,6) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D5,  GET_BIT(Copy_u8Command,5) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D4,  GET_BIT(Copy_u8Command,4) );
	}
	else {
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D7,  GET_BIT(Copy_u8Command,7) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D6,  GET_BIT(Copy_u8Command,6) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D5,  GET_BIT(Copy_u8Command,5) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D4,  GET_BIT(Copy_u8Command,4) );
		//Enable Pulse
		DIO_u8SetPinValue		(CLCD_u8_CTRL_PORT_CONFIG,CLCD_EN_CONFIG , DIO_u8_PIN_HIGH);
		_delay_ms(1);
		DIO_u8SetPinValue		(CLCD_u8_CTRL_PORT_CONFIG,CLCD_EN_CONFIG , DIO_u8_PIN_LOW );
		_delay_ms(1);
		Copy_u8Command <<= 4 ;

		DIO_u8SetPinValue 	(CLCD_u8_CTRL_PORT_CONFIG , CLCD_RS_CONFIG    , DIO_u8_PIN_LOW  );
		DIO_u8SetPinValue 	(CLCD_u8_CTRL_PORT_CONFIG , CLCD_RW_CONFIG    , DIO_u8_PIN_LOW   );

		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D7,  GET_BIT(Copy_u8Command,7) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D6,  GET_BIT(Copy_u8Command,6) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D5,  GET_BIT(Copy_u8Command,5) );
		DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D4,  GET_BIT(Copy_u8Command,4) );
	}

#endif
	//Enable Pulse
	DIO_u8SetPinValue		(CLCD_u8_CTRL_PORT_CONFIG,CLCD_EN_CONFIG , DIO_u8_PIN_HIGH);
	_delay_ms(1);
	DIO_u8SetPinValue		(CLCD_u8_CTRL_PORT_CONFIG,CLCD_EN_CONFIG , DIO_u8_PIN_LOW );
	_delay_ms(1);
}
void CLCD_voidSendData      	( u8 Copy_u8Data    ){

	DIO_u8SetPinValue 	(CLCD_u8_CTRL_PORT_CONFIG , CLCD_RS_CONFIG    , DIO_u8_PIN_HIGH  );
	DIO_u8SetPinValue 	(CLCD_u8_CTRL_PORT_CONFIG , CLCD_RW_CONFIG    , DIO_u8_PIN_LOW   );

#if CLCD_u8_INTERFACE_LINES == LINES_8


	DIO_u8SetPortValue	(CLCD_u8_DATA_PORT_CONFIG , Copy_u8Data);


#elif CLCD_u8_INTERFACE_LINES == LINES_4
	DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D7,  GET_BIT(Copy_u8Data,7) );
	DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D6,  GET_BIT(Copy_u8Data,6) );
	DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D5,  GET_BIT(Copy_u8Data,5) );
	DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D4,  GET_BIT(Copy_u8Data,4) );

	DIO_u8SetPinValue		(CLCD_u8_CTRL_PORT_CONFIG , CLCD_EN_CONFIG, DIO_u8_PIN_HIGH  );
	_delay_ms(1);
	DIO_u8SetPinValue 	( CLCD_u8_CTRL_PORT_CONFIG , CLCD_EN_CONFIG   , DIO_u8_PIN_LOW   );
	_delay_ms(1);
	Copy_u8Data <<=4;

	DIO_u8SetPinValue 	(CLCD_u8_CTRL_PORT_CONFIG , CLCD_RS_CONFIG    , DIO_u8_PIN_HIGH  );
	DIO_u8SetPinValue 	(CLCD_u8_CTRL_PORT_CONFIG , CLCD_RW_CONFIG    , DIO_u8_PIN_LOW   );

	DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D7,  GET_BIT(Copy_u8Data,7) );
	DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D6,  GET_BIT(Copy_u8Data,6) );
	DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D5,  GET_BIT(Copy_u8Data,5) );
	DIO_u8SetPinValue		(CLCD_u8_DATA_PORT_CONFIG,CLCD_u8_D4,  GET_BIT(Copy_u8Data,4) );
#endif
	//Enable Pulse
	DIO_u8SetPinValue		(CLCD_u8_CTRL_PORT_CONFIG , CLCD_EN_CONFIG, DIO_u8_PIN_HIGH  );
	_delay_ms(1);
	DIO_u8SetPinValue 	( CLCD_u8_CTRL_PORT_CONFIG , CLCD_EN_CONFIG   , DIO_u8_PIN_LOW   );
	_delay_ms(1);
}
void CLCD_voidSendString     	( const char* Copy_u8ptrString ){
	u8 Local_u8Iterator  = 0;
	while ( Copy_u8ptrString[ Local_u8Iterator ] != '\0'){
		CLCD_voidSendData(Copy_u8ptrString[ Local_u8Iterator ]);
		Local_u8Iterator++;
	}
}
void CLCD_voidSendNumber     	( u32  Copy_u8Number ){
	s32 LOC_u32FlippedNumber = 1;
	if( Copy_u8Number == 0 ){
		CLCD_voidSendData('0');
	}
	while( Copy_u8Number != 0 ){
		LOC_u32FlippedNumber = ( LOC_u32FlippedNumber * 10 ) + ( Copy_u8Number % 10 ) ;
		Copy_u8Number  /= 10 ;
	}
	while( LOC_u32FlippedNumber != 1 ){

		CLCD_voidSendData( ( LOC_u32FlippedNumber % 10 ) + 48 );
		LOC_u32FlippedNumber  /= 10 ;

	}
}
void CLCD_voidGoToXY			( u8 Copy_u8XPos , u8 Copy_u8YPos){
	u8 Local_u8Position = 		( Copy_u8XPos*0x40 + Copy_u8YPos)+128;
	CLCD_voidSendCmd(Local_u8Position);
}
void CLCD_voidSendExtraChar		( u8 Copy_u8XPos , u8 Copy_u8YPos , u8 Copy_u8BlockNum ){

	u8 Local_u8CGRAMAddress = (Copy_u8BlockNum * 8)+CLCD_u8_TO_CGRAM , Local_u8Iterator = 0 ;

	CLCD_voidSendCmd(Local_u8CGRAMAddress);

	for (Local_u8Iterator =0 ;Local_u8Iterator < 8 ; Local_u8Iterator++){
		CLCD_voidSendData(CustomChar[Copy_u8BlockNum][Local_u8Iterator]);
	}

	CLCD_voidGoToXY(Copy_u8XPos ,Copy_u8YPos);
	CLCD_voidSendData(Copy_u8BlockNum);

}
