/***************************************************************************************/
/***************************************************************************************/
/*******************************	Author : Ayman Saleh				****************/
/*******************************	Date   : 2-9-2021					****************/
/*******************************	Layer  : MCAL						****************/
/*******************************	SWC    : External Exception	(EXTI)	****************/
/*******************************	Version:1.0.0						****************/
/***************************************************************************************/
/***************************************************************************************/

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"
/* @ Interrupt Number*/
#define INT0	0
#define INT1	1
#define INT2	2

/* @ Interrupt Sense Control*/
#define LOW_LEVEL_SENSE			0
#define ON_SHANGE_SENSE			1
#define FALLING_EDGE_SENSE		2
#define RISING_EDGE_SENSE		3

void EXTI_voidInit(void);

/* Description
 * Parameter:  1- Copy_u8IntNum:	Required Interrupt Numbers , choose an option @ Interrupt Number
 * return 	:	Error State: OK or NOK
 */

u8 EXTI_u8EnableInit( u8 Copy_u8IntNum);

/* Description
 * Parameter:  1- Copy_u8IntNum:	Required Interrupt Numbers , choose an option @ Interrupt Number
 * return 	:	Error State: OK or NOK
 */
u8 EXTI_u8DidableInit( u8 Copy_u8IntNum);


/* Description
 * Parameter:  	1- Copy_u8IntNum:	Required Interrupt Numbers , choose an option @ Interrupt Number
 * 				2- Copy_u8Sense		Required Sense Control     , choose an option @ Interrupt Sense Control
 * return 	:	Error State: OK or NOK
 */
u8 EXTI_u8SetSenseControl( u8 Copy_u8IntNum , u8 Copy_u8Sense);

u8 EXTI_u8SetCallBack( void (*ptrv_CallBackFunc) (void) , u8 Copy_u8EXTINumber);
#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
