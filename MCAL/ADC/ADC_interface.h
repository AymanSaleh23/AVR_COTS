/***************************************************************************************/
/***************************************************************************************/
/*******************************	Author : Ayman Saleh				****************/
/*******************************	Date   : 8-9-2021					****************/
/*******************************	Layer  : MCAL						****************/
/*******************************	SWC    : ADC						****************/
/*******************************	Version: 1.0.0						****************/
/***************************************************************************************/
/***************************************************************************************/


#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

#define ADC_ENABLE	1
#define ADC_DISABLE	2

#define ADC0		0
#define ADC1		1
#define ADC2		2
#define ADC3		3
#define ADC4		4
#define ADC5		5
#define ADC6		6
#define ADC7		7

#define ADC_PS0			1
#define ADC_PS2			2
#define ADC_PS4			3
#define ADC_PS8			4
#define ADC_PS16		5
#define ADC_PS32		6
#define ADC_PS64		7
#define ADC_PS128		8

#define ADC_LEFT_ADJ	1
#define ADC_RIGHT_ADJ	2

#define ADC_SINGLE_ENDED	1
#define ADC_DOUBLE_ENDED	2

#define ADC_TS_FREE_RUNNING				1
#define ADC_TS_ANALOG_COMPARATOR		2
#define ADC_TS_EXTI0_REQU				3
#define ADC_TS_T0_COMPARE_MATCH			4
#define ADC_TS_T0_OVERFLOW				5
#define ADC_TS_T_COMPARE_MATCH_B		6
#define ADC_TS_T1_OVERFLOW				7
#define ADC_TS_T1_COMPARE_MATCH			8

typedef struct{
	u8 ChainSize;
	u8* ChannelArr;
	u16* ResultArr;
	void (*NotificationFunc)(void);

}ADC_Chain_t;

void	ADC_voidInit						(	void	);
u16 	ADC_u16StartSingleConversionSync	( u8 Copy_u8Channel			, 	u16* Copy_pu16Result 	);
u8 		ADC_u8StartSingleConersionAsync		( u8 Copy_u8Channel			, 	void (*ptrv_NotifictionFunc)(void) , u16 * Copy_u16ptrRead  );

//	The address of the Copy_u16ptrRead should be an address of an array of u16 consists of 8 elements
u8 		ADC_u8StartChainConersionAsync		( ADC_Chain_t * Copy_pChainObj	);
#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
