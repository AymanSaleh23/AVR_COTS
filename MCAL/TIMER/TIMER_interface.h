/*
 * TIMER_interface.h
 *
 *  Created on: Sep 12, 2021
 *      Author: 20114
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

/**		Timer 2 will be to Schedule Tasks	**/

#define TIMER_T0		0
#define TIMER_T1		1
#define TIMER_T2		2

#define TIMER_INT_EN	1
#define TIMER_INT_DIS	2

#define TIMER_OFF					0
#define TIMER_PRESCALLER_1			1
#define TIMER_PRESCALLER_8			2
#define TIMER_PRESCALLER_32			3
#define TIMER_PRESCALLER_64			4
#define TIMER_PRESCALLER_128		5
#define TIMER_PRESCALLER_256		6
#define TIMER_PRESCALLER_1024		7
#define TIMER_EXTERNAL_CLK_RISING	8
#define TIMER_EXTERNAL_CLK_FALLING	9

#define	OC0_NO_HW_ACTION		1
#define OC0_TOGG				2
#define OC0_CLR					3
#define OC0_SET					4
#define OC0_CLR_OC0_SET_TOP 	5
#define OC0_SET_OC0_CLR_TOP   	6
#define OC0_CLR_UP_SET_DOWN 	7
#define OC0_SET_UP_CLR_DOWN    	8

#define OC1A_NO_HW_ACTION		1
#define OC1A_TOGG        		2
#define OC1A_CLR              	3
#define OC1A_SET              	4

#define OC1B_NO_HW_ACTION       5
#define OC1B_TOGG             	6
#define OC1B_CLR               	7
#define OC1B_SET				8

#define OC1A_CLR_OC1A_SET_TOP	9
#define OC1A_SET_OC1A_CLR_TOP   10
#define OC1A_CLR_UP_SET_DOWN	11
#define OC1A_SET_UP_CLR_DOWN	12

#define OC1B_CLR_OC1B_SET_TOP 	13
#define OC1B_SET_OC1B_CLR_TOP  	14
#define OC1B_CLR_UP_SET_DOWN	15
#define OC1B_SET_UP_CLR_DOWN   	16


#define OC2_NO_HW_ACTION		1
#define OC2_TOGG	        	2
#define OC2_CLR				    3
#define OC2_SET				    4
#define OC2_CLR_OC2_SET_TOP     5
#define OC2_SET_OC2_CLR_TOP     6
#define OC2_CLR_UP_SET_DOWN     7
#define OC2_SET_UP_CLR_DOWN     8

#define TIMER_NORMAL_MODE			0

#define TIMER_CTC_MODE				2


#define TIMER1_CTC_MODE_OCR1A		4
#define TIMER1_CTC_ICR1          	12

#define TCCR0_u8_READ		0
#define TCCR1A_u8_READ		1
#define TCCR1B_u8_READ		2
#define TCCR2_u8_READ		3
#define TCCR1_u16_READ		4

#define TCNT0_u8_READ		5
#define TCNT1_u16_READ		6
#define TCNT2_u8_READ		7

#define OCR0_u8_READ		8
#define OCR1A_u16_READ		9
#define OCR1B_u16_READ		10
#define OCR2_u8_READ		11
#define ICR1_u16_READ		12

#define OCR0_u8_UPDATE		0
#define OCR1A_u16_UPDATE	1
#define OCR1B_u16_UPDATE	2
#define OCR2_u8_UPDATE		3

#define ISR_T0_OV	0
#define ISR_T1_OV	1
#define ISR_T2_OV	2

#define ISR_T0_COMPARE_MATCH	3
#define ISR_T1A_COMPARE_MATCH	4
#define ISR_T1B_COMPARE_MATCH	5
#define ISR_T2_COMPARE_MATCH	6

#define ISR_INPUT_CAPTURE		7


#define PIE_T0_OV				0
#define PIE_T1_OV				1
#define PIE_T2_OV				2
#define PIE_T0_COMPARE_MATCH	3
#define PIE_T1A_COMPARE_MATCH	4
#define PIE_T1B_COMPARE_MATCH	5
#define PIE_T2_COMPARE_MATCH	6
#define PIE_INPUT_CAPTURE		7


#define HW_OC0		0
#define HW_OC1A		1
#define HW_OC1B		2
#define HW_OC2		3

#define CONTINUITY_ON	0
#define CONTINUITY_OFF	1

typedef struct{
	u8 Num;
	u8 Mode;
	u8 CLK;
	u8 OCAction;
	u8 OCChannel;
	u8 OverflowInt;
	u8 COMPInt;
} Timer_Type ;

//Pre Build Config Func
u8 		TIMER_u8Init			(	void		);

//Post Build Config Func
u8 		TIMER_u8SettingUp		(	const Timer_Type * Copy_TConfiguration	);

//Change Prescaler
u8		TIMER_u8ChangePrescaler	(	u8 Copy_u8TNum , u8 Copy_u8NewPrescaler	);

//Change Mode (WGM)
u8		TIMER_u8ChangeMode		(	u8 Copy_u8TNum , u8 Copy_u8Mode			);

//Change HW Action OCx (Phase correct PWM , CTC , Fast PWM )
u8		TIMER_u8ChangeHWAction	(	u8 Copy_u8OCNum , u8 Copy_u8Action		);

//Disable Timer
u8		TIMER_u8Disable			(	u8 Copy_u8TNum );

//Enable Timer Interrupts
u8		TIMER_u8DisableInterrupt(	u8 Copy_u8TimerPIEs);

//Disable Timer Interrupts
u8		TIMER_u8EnableInterrupt(	u8 Copy_u8TimerPIEs);

//Send ISR action to Timers
u8 		TIMER_u8SetISR			( 	void ( * ptrf_ISRFunc )(void)	, u8 Copy_u8TISR);

u8 		TIMER_u8SetICR  		( u16 Copy_u16NewValue	);
//Set  TCNT - OCR , read Timer
u8 		TIMER_u8SetTCNT					( u8 Copy_u8TNum , u16 Copy_u16NewValue		);
u8 		TIMER_u8SetOCR   				( u8 Copy_u8OCRNum , u16 Copy_u16NewValue	);
u8		TIMER_u8Read     				( u8 Copy_u8Reg , u16 * Copy_pu16ReadValue 	);


//Start a Schedule (Timer 2)
u8 		TIMER_u8Schedule			(	 void ( * ptrf_ScheduleFunc )(void) , u8 Copy_u8Continuity , u8 Copy_u8TimeUS	);
//End The Schedule (Timer 2)
void 	TIMER_u8ScheduleDisable		(	void		);


#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
