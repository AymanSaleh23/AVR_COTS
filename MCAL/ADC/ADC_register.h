/***************************************************************************************/
/***************************************************************************************/
/*******************************	Author : Ayman Saleh				****************/
/*******************************	Date   : 8-9-2021					****************/
/*******************************	Layer  : MCAL						****************/
/*******************************	SWC    : ADC						****************/
/*******************************	Version: 1.0.0						****************/
/***************************************************************************************/
/***************************************************************************************/


#ifndef MCAL_ADC_ADC_REGISTER_H_
#define MCAL_ADC_ADC_REGISTER_H_

#define ADMUX 			*((volatile u8*)0x27)		/*ADC Multiplexer selection register*/
#define ADMUX_REFS1		7							/*Reference selection bit 1*/
#define ADMUX_REFS0		6                           /*Reference selection bit 0*/
#define ADMUX_ADLAR		5                           /*Left adjust result*/

#define ADCSRA 			*((volatile u8*)0x26)		/*ADC Control and status register A*/
#define ADCSRA_ADEN		7							/*ADC enable*/
#define ADCSRA_ADSC		6                           /*ADC start conversion*/
#define ADCSRA_ADATE	5	                        /*Auto trigger enable*/
#define ADCSRA_ADIF		4                           /*ADC interrupt flag*/
#define ADCSRA_ADIE		3                           /*ADC Interrupt enable*/


#define ADCH 			*((volatile u8*)0x25)		/*Data high register*/
#define ADCL 			*((volatile u8*)0x24)       /*Data low register*/
#define ADC 			*((volatile u16*)0x24)      /*u16 pointer to fetch 10 bit data*/


#endif /* MCAL_ADC_ADC_REGISTER_H_ */
