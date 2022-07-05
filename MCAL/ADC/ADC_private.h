/***************************************************************************************/
/***************************************************************************************/
/*******************************	Author : Ayman Saleh				****************/
/*******************************	Date   : 8-9-2021					****************/
/*******************************	Layer  : MCAL						****************/
/*******************************	SWC    : ADC						****************/
/*******************************	Version: 1.0.0						****************/
/***************************************************************************************/
/***************************************************************************************/


#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define EIGHT_BIT    	1
#define TEN_BIT      	2

#define DEVIDED_BY_2	1
#define DEVIDED_BY_4	2
#define DEVIDED_BY_8	3
#define DEVIDED_BY_16	4
#define DEVIDED_BY_32	5
#define DEVIDED_BY_64	6
#define DEVIDED_BY_128	7

#define INT_DISABLE     1
#define INT_ENABLE      2

#define T_DISABLE     	1
#define T_ENABLE      	2

#define ADCSRA_PERSCALER_BIT_MASK_VALUE	0b11111000
#define ADMUX_MUX_BIT_MASK_VALUE		0b11100000

#define IDLE		0
#define BUSY		1

#define SINGLE_CONV			0
#define CHAIN_CONV			1

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
