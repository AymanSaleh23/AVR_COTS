/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 26-8-2021		***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : CLCD			***************************/
/*******************************	Version: 1.0.0			***************************/
/**************************************************************************************/
/**************************************************************************************/


#ifndef HAL_CLCD_CLCD_INTERFACE_H_
#define HAL_CLCD_CLCD_INTERFACE_H_

//  If you want to change on the Custom Chars on run time you have to ----> extern u8 CustomChar[8][8]


#include "../../LIB/STD_TYPES.h"

#define CLCD_R0		0
#define CLCD_R1		1

#define CLCD_C0		0
#define CLCD_C1		1
#define CLCD_C2		2
#define CLCD_C3		3
#define CLCD_C4		4
#define CLCD_C5		5
#define CLCD_C6		6
#define CLCD_C7		7
#define CLCD_C8		8
#define CLCD_C9		9
#define CLCD_C10	10
#define CLCD_C11	11
#define CLCD_C12	12
#define CLCD_C13	13
#define CLCD_C14	14
#define CLCD_C15	15

#define CLCD_u8_CLEAR_ALL	0b00000001

void CLCD_voidInit           	( void 					);
void CLCD_voidSendCmd   		( u8 Copy_u8Command 	);
void CLCD_voidSendData       	( u8 Copy_u8Data    	);
void CLCD_voidSendString     	( const char * Copy_u8ptrString );
void CLCD_voidSendNumber     	( u32  Copy_u8Number 	);
void CLCD_voidGoToXY			( u8 Copy_u8XPos , u8 Copy_u8YPos);
void CLCD_voidSendExtraChar		( u8 Copy_u8XPos , u8 Copy_u8YPos , u8 Copy_u8BlockNum );
#endif /* HAL_CLCD_CLCD_INTERFACE_H_ */
