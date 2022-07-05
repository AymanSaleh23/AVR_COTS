/*
 * TIMER_private.h
 *
 *  Created on: Sep 12, 2021
 *      Author: 20114
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

#define T02_MAX		255
#define T1_MAX		65535
#define T_BOTTOM	0

#define ENABLE			1
#define DISABLE			2
#define SCHEDULE		3

#define IDLE			0
#define BUSY_TIMER		1
#define IDLE_SCHEDULE	2
#define BUSY_SCHEDULE	3

#define ENABLE_SCHEDULE		1
#define DISABLE_SCHEDULE	2

#define SCHDULE_CTC     	1
#define SCHDULE_PRELOAD 	2
/******************************	Timer/Counter 0		***********************/

/*	Wave Generator Mode For Timer 0 (WGM0)			*/

#define T0_WGM_NORMAL_MODE				0b00000000
#define T0_WGM_PWM_PHASE_CORRECT_MODE	0b01000000
#define T0_WGM_CTC_MODE					0b00001000
#define T0_WGM_FAST_PWM_MODE			0b01001000

#define T0_WGM_MASKING_VALUE			0b10110111

/*	Compare Match Output Mode For Timer 0	(COM0)	*/

/*	COM at non-PWM	(CTC on)	*/
#define T0_COM0_NO_HW_ACTION		0b00000000
#define T0_COM0_TOGG_OC0			0b00010000
#define T0_COM0_CLR_OC0				0b00100000
#define T0_COM0_SET_OC0				0b00110000

/*	COM at Fast-PWM				*/
#define T0_COM0_NO_HW_ACTION   		0b00000000
//	case 01 reserved
#define T0_COM0_CLR_OC0_SET_TOP     0b00100000
#define T0_COM0_SET_OC0_CLR_TOP		0b00110000

/*	COM at PWM-Phase Correct	*/
#define T0_COM0_NO_HW_ACTION		0b00000000
//	case 01 reserved
#define T0_COM0_CLR_UP_SET_DOWN		0b00100000
#define T0_COM0_SET_UP_CLR_DOWN		0b00110000

#define T0_COM_MASKING_VALUE		0b11001111


/******************************	Timer/Counter 1		***********************/

/*		COM A/B at non-PWM 			*/
#define T1_COM1A_NO_HW_ACTION		0b00000000
#define T1_COM1A_TOGG_OC1A          0b01000000
#define T1_COM1A_CLR_OC1A           0b10000000
#define T1_COM1A_SET_OC1A           0b11000000

#define T1_COM1B_NO_HW_ACTION       0b00000000
#define T1_COM1B_TOGG_OC1B          0b00010000
#define T1_COM1B_CLR_OC1B           0b00100000
#define T1_COM1B_SET_OC1B           0b00110000

/*		COM A/B at Fast-PWM 			*/
#define T1_COM1A_NO_HW_ACTION		0b00000000
#define T1_COM1A_TOGG_OC1A 			0b01000000
#define T1_COM1A_CLR_OC1A_SET_TOP	0b10000000
#define T1_COM1A_SET_OC1A_CLR_TOP   0b11000000

#define T1_COM1B_NO_HW_ACTION       0b00000000
#define T1_COM1B_TOGG_OC1B          0b00010000
#define T1_COM1B_CLR_OC1A_SET_TOP   0b00100000
#define T1_COM1B_SET_OC1A_CLR_TOP	0b00110000

/*		COM A/B at PWM-Phase Correct	*/

#define T1_COM1A_NO_HW_ACTION		0b00000000
#define T1_COM1A_TOGG_OC1A 			0b01000000
#define T1_COM1A_CLR_UP_SET_DOWN	0b10000000
#define T1_COM1A_SET_UP_CLR_DOWN	0b11000000



#define T1_COM1B_NO_HW_ACTION       0b00000000
#define T1_COM1B_TOGG_OC1B          0b00010000
#define T1_COM1B_CLR_UP_SET_DOWN	0b00100000
#define T1_COM1B_SET_UP_CLR_DOWN	0b00110000

#define T1_COM1A_MASKING_VALUE		0b00111111
#define T1_COM1B_MASKING_VALUE		0b11001111

/*		TCCR1
 * 			COM1A1 	COM1A0 	COM1B1 	COM1B0 	FOC1A 	FOC1B 	WGM11 	WGM10	ICNC1	-	ICES1	WGM13	WGM12 	CS12 	CS11 	CS10
 */

#define T1_WGM_NORMAL						0b0000000000000000
#define T1_WGM_PWM_PHASE_CORRECT_8BIT       0b0000000100000000
#define T1_WGM_PWM_PHASE_CORRECT_9BIT       0b0000001000000000
#define T1_WGM_PWM_PHASE_CORRECT_10BIT      0b0000001100000000
#define T1_WGM_CTC_OCR1A                    0b0000000000001000
#define T1_WGM_FAST_PWM_8BIT                0b0000000100001000
#define T1_WGM_FAST_PWM_9BIT                0b0000001000001000
#define T1_WGM_FAST_PWM_10BIT               0b0000001100001000
#define T1_WGM_PWM_PHASE_FRQ_CORRECT_ICR1   0b0000000000010000
#define T1_WGM_PWM_PHASE_FRQ_CORRECT_OCR1A 	0b0000000100010000
#define T1_WGM_PWM_PHASE_CORRECT_ICR1       0b0000001000010000
#define T1_WGM_PWM_PHASE_CORRECT_OCR1A		0b0000001100010000
#define T1_WGM_CTC_ICR1                     0b0000000000011000
//	case 1101 reserved
#define T1_WGM_FAST_PWM_ICR1                0b0000001000011000
#define T1_WGM_FAST_PWM_OCR1A               0b0000001100011000

#define T1_WGM_MASKING_VALUE				0b1111110011100111


/******************************	Timer/Counter 2		***********************/
/*	Wave Generator Mode For Timer 2 (WGM2)			*/

#define T2_WGM_NORMAL_MODE				0b00000000
#define T2_WGM_PWM_PHASE_CORRECT_MODE	0b01000000
#define T2_WGM_CTC_MODE					0b00001000
#define T2_WGM_FAST_PWM_MODE			0b01001000

#define T2_WGM_MASKING_VALUE			0b10110111

/*	Compare Match Output Mode For Timer 2	(COM2)	*/

/*	COM at non-PWM	(CTC on)	*/
#define T2_COM2_NO_HW_ACTION		0b00000000
#define T2_COM2_TOGG_OC2			0b00010000
#define T2_COM2_CLR_OC2				0b00100000
#define T2_COM2_SET_OC2				0b00110000

/*	COM at Fast-PWM				*/
#define T2_COM2_NO_HW_ACTION   		0b00000000
//	case 01 reserved
#define T2_COM2_CLR_OC2_SET_TOP     0b00100000
#define T2_COM2_SET_OC2_CLR_TOP		0b00110000

/*	COM at PWM-Phase Correct	*/
#define T2_COM2_NO_HW_ACTION		0b00000000
//	case 01 reserved
#define T2_COM2_CLR_UP_SET_DOWN		0b00100000
#define T2_COM2_SET_UP_CLR_DOWN		0b00110000

#define T2_COM_MASKING_VALUE		0b11001111

/********************************************************************************/
/****	Common to T0 , T1	Prescaler 	*****************************************/
/*	Prescaler (Clock Select) For Timer0 / Timer1	*/

#define T01_STOP						0b00000000
#define T01_DIVIDED_BY_1				0b00000001
#define T01_DIVIDED_BY_8                0b00000010
#define T01_DIVIDED_BY_64               0b00000011
#define T01_DIVIDED_BY_256              0b00000100
#define T01_DIVIDED_BY_1024             0b00000101
#define T01_EXTRNAL_ON_T01_FALLING   	0b00000110
#define T01_EXTRNAL_ON_T01_RISING      	0b00000111

#define T01_CLK_SLECT_MASKING_VALUE		0b11111000

/*	Prescaler (Clock Select) For Timer2				*/

#define T2_STOP						0b00000000
#define T2_DIVIDED_BY_1				0b00000001
#define T2_DIVIDED_BY_8             0b00000010
#define T2_DIVIDED_BY_32            0b00000011
#define T2_DIVIDED_BY_64            0b00000100
#define T2_DIVIDED_BY_128           0b00000101
#define T2_DIVIDED_BY_256           0b00000110
#define T2_DIVIDED_BY_1024          0b00000111

#define T2_CLK_SLECT_MASKING_VALUE	0b11111000

/*		Prescaler For Configuration file 			*/

#define PRESCALER_1				1
#define PRESCALER_8				8
#define PRESCALER_32			32
#define PRESCALER_64			64
#define PRESCALER_128			128
#define PRESCALER_256			256
#define PRESCALER_1024			1024

#define EXTERNAL_COUNT_FALLING	3
#define EXTERNAL_COUNT_RISING	4

/*		Modes	For Configuration file 			*/


#define OVERFLOW       					1
#define PWM_PHASE_CORRECT           	2
#define CTC                         	3
#define FAST_PWM                    	4

#define CTC_ICR1                   		15

/*		OC Pin Options*/
#define NO_HW_ACTION		1
#define TOGG_OC0			2
#define CLR_OC0				3
#define SET_OC0				4

#define T0_RESOLUTION 		256
#define T2_RESOLUTION 		256
#define T1_RESOLUTION 		65536

#define EXTERNAL_RISING		2
#define EXTERNAL_FALLING	3

#define CLR_COUNTER 		0
/*
static u32 Timer0_Freq = 0;
static u32 Timer1_Freq = 0;
static u32 Timer2_Freq = 0;*/

#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
