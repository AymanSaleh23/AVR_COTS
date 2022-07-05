/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 31-8-2021		***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : DC MOTOR		***************************/
/*******************************	Version: 1.0.0			***************************/
/**************************************************************************************/
/**************************************************************************************/

#ifndef HAL_DCMOTOR_DCMOTOR_INTERFACE_H_
#define HAL_DCMOTOR_DCMOTOR_INTERFACE_H_

typedef struct {
	u8 PORT;
	u8 PINA;
	u8 PINB;
}DC_MOTOR_Type;

void DCMOTOR_voidStop	( const DC_MOTOR_Type * Copy_MOTORObj);
void DCMOTOR_voidCW		( const DC_MOTOR_Type * Copy_MOTORObj);
void DCMOTOR_voidCCW	( const DC_MOTOR_Type * Copy_MOTORObj);

#endif /* HAL_DCMOTOR_DCMOTOR_INTERFACE_H_ */
