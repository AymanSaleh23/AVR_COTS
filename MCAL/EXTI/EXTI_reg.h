/***************************************************************************************/
/***************************************************************************************/
/*******************************	Author : Ayman Saleh				****************/
/*******************************	Date   : 2-9-2021					****************/
/*******************************	Layer  : MCAL						****************/
/*******************************	SWC    : External Exception	(EXTI)	****************/
/*******************************	Version:1.0.0						****************/
/***************************************************************************************/
/***************************************************************************************/

#ifndef MCAL_EXTI_EXTI_REG_H_
#define MCAL_EXTI_EXTI_REG_H_



#define MCUCR	*((volatile u8 * ) 0x55 )
#define MCUCR_ISC00	0
#define MCUCR_ISC01	1
#define MCUCR_ISC10	2
#define MCUCR_ISC11	3

#define MCUCSR	*((volatile u8 * ) 0x54	)
#define MCUCSR_ISC2	1

#define GICR	*((volatile u8 * ) 0x5B	)

#define GICR_INT0	6
#define GICR_INT1	7
#define GICR_INT2	5

/*
 * we don't check flags on external INT  (Polling)
#define GIFR	*((volatile u8 * ) 0x5A	)
*/



#endif /* MCAL_EXTI_EXTI_REG_H_ */
