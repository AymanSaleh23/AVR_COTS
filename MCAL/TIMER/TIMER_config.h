/*
 * TIMER_config.h
 *
 *  Created on: Sep 12, 2021
 *      Author: 20114
 */

#ifndef MCAL_TIMER_TIMER_CONFIG_H_
#define MCAL_TIMER_TIMER_CONFIG_H_



/************************************	Timer 0 , Timer 1	*****************************************************/

/*
 *	Options:
 *      1-	DISABLE
 *      2- 	Enable
 */
#define T01_STATE		ENABLE


#if T01_STATE 	== ENABLE

/*		For Timer 0 only
 * Options :
 * 	1-	OVERFLOW       					1
 * 	2-  PWM_PHASE_CORRECT           	2
 * 	3-  CTC                         	3
 * 	4-  FAST_PWM                    	4
 */

#define T0_MODE		OVERFLOW

/*
 * Options:
 * 	1-	TIMER_INT_EN
 * 	2-  TIMER_INT_DIS
 */

#define T0_OVERFLOW_PIE			TIMER_INT_DIS
#define T0_COMPARE_MATCH_PIE	TIMER_INT_DIS


/*	For Timer 1 only
 * 	Options :
 * 		1-  OVERFLOW       					1
 * 		2-  PWM_PHASE_CORRECT           	2
 * 		3-  CTC                         	3
 * 		4-  FAST_PWM                    	4
 * 		5-  PWM_PHASE_CORRECT_8BIT     		5
 * 		6-  PWM_PHASE_CORRECT_9BIT      	6
 * 		7-  PWM_PHASE_CORRECT_10BIT     	7
 * 		8-  FAST_PWM_8BIT               	8
 * 		9-  FAST_PWM_9BIT               	9
 * 		10- FAST_PWM_10BIT              	10
 * 		11- PWM_PHASE_FRQ_CORRECT_ICR1      11
 * 		12- PWM_PHASE_FRQ_CORRECT_OCR1A	   	12
 * 		13- PWM_PHASE_CORRECT_ICR1      	13
 * 		14- PWM_PHASE_CORRECT_OCR1A     	14
 * 		15- CTC_ICR1                   		15
 * 		16-	FAST_PWM_ICR1               	16
 * 		17- FAST_PWM_OCR1A              	17
 */
#define T1_MODE		OVERFLOW

/*
 * Options:
 * 	1-	TIMER_INT_EN
 * 	2-  TIMER_INT_DIS
 */

#define T1_OVERFLOW_PIE			TIMER_INT_DIS
#define T1_COMPARE_MATCH_PIE	TIMER_INT_DIS

/*
 * 	Options:	Timer 0, Timer 1 only
 *      1-	PRESCALER_1
 *      2-	PRESCALER_8
 *      3-	PRESCALER_64
 *      4-	PRESCALER_256
 *      5-	PRESCALER_1024
 *      6-	EXTERNAL_COUNT_FALLING
 *      7-	EXTERNAL_COUNT_RISING
 */


#define T01_PRESCALER	EXTERNAL_COUNT_FALLING

#endif

/************************************	Timer 2		*****************************************************/

/*
 *	Options:
 *      1-	DISABLE
 *      2- 	ENABLE
 *      3-	SCHEDULE
 *
 */
#define T2_STATE	ENABLE


#if T2_STATE	==	ENABLE

/*	Timer 2 as Schedule EN/DIS
 *	Option :
 *		1-	ENABLE_SCHEDULE
 *		2-	DISABLE_SCHEDULE
 */

#define SCHDULE_TIMER	DISABLE_SCHEDULE

#if SCHDULE_TIMER == DISABLE_SCHEDULE

/*
 * Options:
 * 	1-	TIMER_INT_EN
 * 	2-  TIMER_INT_DIS
 */

#define T2_OVERFLOW_PIE			TIMER_INT_DIS
#define T2_COMPARE_MATCH_PIE	TIMER_INT_DIS

/*		For Timer 2 only
 * Options :
 * 	1-	OVERFLOW       					1
 * 	2-  PWM_PHASE_CORRECT           	2
 * 	3-  CTC                         	3
 * 	4-  FAST_PWM                    	4
 */

#define T2_MODE		OVERFLOW


/*
 * 	Options:	Timer 2	only
 *      1-	PRESCALER_1
 *      2-	PRESCALER_8
 *      3-	PRESCALER_32
 *      4-	PRESCALER_64
 *      5-	PRESCALER_128
 *      6-	PRESCALER_256
 *      7-	PRESCALER_1024
 */
#define T2_PRESCALER	PRESCALER_1024

#elif SCHDULE_TIMER == ENABLE_SCHEDULE

/*
 * Options:
 * 	1-	SCHDULE_CTC
 * 	2-  SCHDULE_PRELOAD
 */

#define T2_SCHEDULE_HANDLE	SCHDULE_CTC
#endif




#endif

#endif /* MCAL_TIMER_TIMER_CONFIG_H_ */
