/***************************************************************************************/
/***************************************************************************************/
/*******************************	Author : Ayman Saleh				****************/
/*******************************	Date   : 8-9-2021					****************/
/*******************************	Layer  : MCAL						****************/
/*******************************	SWC    : ADC						****************/
/*******************************	Version: 1.0.0						****************/
/***************************************************************************************/
/***************************************************************************************/


#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_


/*	Choose your ADC required resolution
 *
 *  Options:	1- EIGHT_BIT
 *  			2- TEN_BIT
 */

#define ADC_RESOLUTION	TEN_BIT

/*
 *
 * Choose your ADC required Prescaler
 * 		Options:	1-	DEVIDED_BY_2
 * 					2-  DEVIDED_BY_2
 * 		            3-  DEVIDED_BY_4
 * 		            4-  DEVIDED_BY_8
 * 		            5-  DEVIDED_BY_16
 * 		            6-  DEVIDED_BY_32
 *                  7-  DEVIDED_BY_64
 *                  8-  DEVIDED_BY_128
 *
 *
 */
#define ADC_PRESCALER		DEVIDED_BY_128


/*
 * Choose your ADC required Trigger
 * 		Options:	1-	T_DISABLE
 * 					2-	T_ENABLE
 */
#define ADC_TRIGGER			T_DISABLE

#define ADC_u32_TIMEOUT_PERIOD	50000
#endif /* MCAL_ADC_ADC_CONFIG_H_ */
