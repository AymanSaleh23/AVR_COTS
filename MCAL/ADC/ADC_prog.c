/***************************************************************************************/
/***************************************************************************************/
/*******************************	Author : Ayman Saleh				****************/
/*******************************	Date   : 8-9-2021					****************/
/*******************************	Layer  : MCAL						****************/
/*******************************	SWC    : ADC						****************/
/*******************************	Version: 1.0.0						****************/
/***************************************************************************************/
/***************************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Err_Type.h"

#include "ADC_private.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_register.h"

#include "../GIE/GIE_interface.h"

#include <util/delay.h>

/*	Global Pointer to Conversion to hold the conversion result for Asynch Function*/
static  void (*NotifictionFunc)(void) 	= NULL;

/*	Global pointer to hold the Read Conversion*/
static  u16 *ADC_pu16ConversionResult	= NULL;

/*	Global Variable to indicates That weather There is a Conversion running right now or not */
static u8 ADC_u8BusyState  = IDLE;

static u8 * ADC_pu8ChainChannelArr = NULL;

static u8 ADC_u8ChainSize;

static u8 ADC_u8ConversionIdx;

static u8 ADC_u8ISRSource = SINGLE_CONV;

void ADC_voidInit				(void){

	/*	Set AVCC as reference*/
	SET_BIT(ADMUX ,ADMUX_REFS0);
	CLR_BIT(ADMUX ,ADMUX_REFS1);

	/*	Set ADC left adjustment configuration*/
#if ADC_RESOLUTION == EIGHT_BIT
	SET_BIT(ADMUX  , ADMUX_ADLAR);
#elif ADC_RESOLUTION == TEN_BIT
	CLR_BIT(ADMUX  , ADMUX_ADLAR);
#else
#error "Wrong ADC_RESOLUTION Configuration option!"
#endif


	/*	Setting ADC Auto Trigger en/dis as it is in Config	*/
#if		ADC_TRIGGER == T_DISABLE
	CLR_BIT(ADCSRA , ADCSRA_ADATE);
#elif  	ADC_TRIGGER	== T_ENABLE
	SET_BIT(ADCSRA , ADCSRA_ADATE);
#else
#error "Wrong T_DISABLE Configuration option!"
#endif


	/*	Setting ADC Prescaler as it is in Config			*/
	ADCSRA = (ADMUX & ADCSRA_PERSCALER_BIT_MASK_VALUE) | ADC_PRESCALER ;


	/*	ADC enable
	 	Preferred to make the enable step as the final step 	*/
	SET_BIT(ADCSRA , ADCSRA_ADEN);

}

/*		For Critical Jobs that need polling until reading this ADC value
 * 		Prerequest :	To use this function properly you have to Enable PIE , GIE Because of Interrupt Handling */
u16 ADC_u16StartSingleConversionSync( u8 Copy_u8Channel	, u16* Copy_pu16Result ){
	u8 Local_u8ErrorState = OK;

	if (ADC_u8BusyState == IDLE ){
		u32 Local_u32Counter  = 0;
		ADC_u8BusyState = BUSY;
		/*	1= Clear the 5 LSB, leave the 3 MSBs as they  ware*/
		ADMUX = ( ADMUX & ADMUX_MUX_BIT_MASK_VALUE ) | Copy_u8Channel ;

		/*	2- Start conversion	*/
		SET_BIT(ADCSRA , ADCSRA_ADSC );

		/*	3- Polling on ADC conversion complete flag  or Timeout Period Passes*/
		while ( (GET_BIT(ADCSRA,ADCSRA_ADIF) == 0) && (ADC_u32_TIMEOUT_PERIOD > Local_u32Counter)){
			Local_u32Counter++;
		}

		if (Local_u32Counter == ADC_u32_TIMEOUT_PERIOD ){
			/*	Loops is broken because timeout counter has passed and flag not raised*/
			Local_u8ErrorState = TIMEOUT_ERROR;
		}
		/*	Loops is broken because the flag is raised*/
		else {
			/*	4- Clear complete flag	*/
			SET_BIT(ADCSRA , ADCSRA_ADIF);

#if ADC_RESOLUTION == EIGHT_BIT
			*Copy_pu16Result = ADCH;

#elif ADC_RESOLUTION == TEN_BIT
			*Copy_pu16Result = ADC;

#endif
		}
		/* ADC is IDLE*/
		ADC_u8BusyState = IDLE;
	}
	else if (ADC_u8BusyState == BUSY) {
		Local_u8ErrorState = BUSY_ERR;
	}
	return Local_u8ErrorState;
}

/*		For Long Time Job like EEPROM	(support no waiting)	*/
u8 ADC_u8StartSingleConersionAsync		( u8 Copy_u8Channel	, void (*ptrv_NotifictionFunc)(void) , u16 * Copy_u16ptrRead  ){

	u8 Local_u8ErrorState = OK;
	if (ADC_u8BusyState == IDLE ){

		/*	ADC is now Busy */
		ADC_u8BusyState = BUSY;

		/*	ISR will come because of single conversion*/
		ADC_u8ISRSource = SINGLE_CONV;

		if ( (NULL != ptrv_NotifictionFunc) && (NULL != Copy_u16ptrRead) ){

			/*	1- Clear the 5 LSB, leave the 3 MSBs as they  ware*/
			ADMUX = ( ADMUX & ADMUX_MUX_BIT_MASK_VALUE ) | Copy_u8Channel ;

			/*	2- Enable PIE for ADC*/
			SET_BIT(ADCSRA ,ADCSRA_ADIE);

			/*	3- Start conversion	*/
			SET_BIT(ADCSRA , ADCSRA_ADSC );

			NotifictionFunc = ptrv_NotifictionFunc;
			ADC_pu16ConversionResult =  Copy_u16ptrRead;
		}
		else {
			Local_u8ErrorState = NULL_POINTER;
		}

	}
	else if (ADC_u8BusyState == BUSY ){
		Local_u8ErrorState = BUSY_ERR;
	}
	return Local_u8ErrorState;
}

//						0b10001001
u8 	ADC_u8StartChainConersionAsync		( ADC_Chain_t *Copy_pChainObj	){
	u8 Local_u8ErrorState = OK;

	if ( (Copy_pChainObj != NULL)  && (Copy_pChainObj->ChannelArr != NULL) && (Copy_pChainObj->NotificationFunc != NULL) && (Copy_pChainObj->ResultArr != NULL) ){
		if (ADC_u8BusyState == IDLE){
			/*	ADC Now is Busy*/
			ADC_u8BusyState = BUSY;

			/*	ISR will come because of single conversion*/
			ADC_u8ISRSource = CHAIN_CONV;

			/*	Exchange Data Globally */
			ADC_u8ChainSize 		= Copy_pChainObj->ChainSize;
			ADC_pu8ChainChannelArr 	= Copy_pChainObj->ChannelArr;
			ADC_pu16ConversionResult= Copy_pChainObj->ResultArr;
			NotifictionFunc 		= Copy_pChainObj->NotificationFunc;

			ADC_u8ConversionIdx = 0;
			/*	1- Clear the 5 LSB, leave the 3 MSBs as they  ware*/
			ADMUX = ( ADMUX & ADMUX_MUX_BIT_MASK_VALUE ) ;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ConversionIdx] ;

			/*	3- Start conversion	*/
			SET_BIT(ADCSRA , ADCSRA_ADSC );

			/*	2- Enable PIE for ADC*/
			SET_BIT(ADCSRA ,ADCSRA_ADIE);

		}
		else {
			Local_u8ErrorState = BUSY_ERR;
		}
	}
	else {
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}



/*	@ISR_ADC	ADC	ISR			*/
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void){

	if (ADC_u8ISRSource == SINGLE_CONV) {
		/*	Read Conversion Result*/
#if 	ADC_RESOLUTION == EIGHT_BIT

		*ADC_pu16ConversionResult = ADCH;

#elif 	ADC_RESOLUTION == TEN_BIT

		*ADC_pu16ConversionResult = ADC;

#endif

		/*	Disable PIE to the ADC Conversion complete event*/
		CLR_BIT(ADCSRA ,ADCSRA_ADIE);

		/*	ADC is Now IDLE*/
		ADC_u8BusyState = IDLE;

		/*	Callback the function That needed Function that depends on the ADC read */
		if (NotifictionFunc != NULL){
			NotifictionFunc();
		}
		else {
			// Do Nothing
		}
	}


	else {
		/*		Read Data		*/
#if 	ADC_RESOLUTION == EIGHT_BIT

		ADC_pu16ConversionResult[ADC_u8ConversionIdx] = ADCH;

#elif 	ADC_RESOLUTION == TEN_BIT

		ADC_pu16ConversionResult[ADC_u8ConversionIdx] = ADC;

#endif

		ADC_u8ConversionIdx++;
		if (ADC_u8ConversionIdx == ADC_u8ChainSize){
			/*	Chain is finished*/
			/*	Disable PIE to the ADC Conversion complete event*/
			CLR_BIT(ADCSRA ,ADCSRA_ADIE);

			/*	ADC is Now IDLE*/
			ADC_u8BusyState = IDLE;


			/*	Callback the function That needed Function that depends on the ADC read */
			if (NotifictionFunc != NULL){
				NotifictionFunc();
			}
		}
		else {
			/*	Chain isn't finished*/
			ADMUX = ( ADMUX & ADMUX_MUX_BIT_MASK_VALUE ) ;
			ADMUX |= ADC_pu8ChainChannelArr[ADC_u8ConversionIdx] ;

			/*	3- Start conversion	*/
			SET_BIT(ADCSRA , ADCSRA_ADSC );
		}
	}
}
