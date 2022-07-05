/*
 * UART_prog.c
 *
 *  Created on: Oct 1, 2021
 *      Author: 20114
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Err_Type.h"

#include "UART_private.h"
#include "UART_config.h"
#include "UART_interface.h"
#include "UART_reg.h"

static void (*TX_Func ) (void) = NULL;
//static void (*UDR_Func) (void) = NULL;
static void (*RX_Func ) (u16 * Copy_ptr8Receive ) = NULL;

static u8 ResolutionData = 0;
static u8 Transmit = IDEL;
static u16 *TransmittData	= NULL;
static u8 Receive  = IDEL;
static u16 *ReceivedData 	= NULL;


void UART_u8Init 				(	void		){
	u16 Local_u16BaudRate = 0;
	u8  Local_u8UCSRCBuffer = 0;
#if 	UART_STATE == ENABLE

#if 	UART_TRANSMIT == ENABLE
	SET_BIT(UCSRB ,UCSRB_TXEN);
#elif 	UART_TRANSMIT == DISABLE
	CLR_BIT(UCSRB ,UCSRB_TXEN);
#else
#error	"Invalid UART_TRANSMIT Configuration "
#endif

#if 	UART_RECEIVE == ENABLE
	SET_BIT(UCSRB ,UCSRB_RXEN);
#elif 	UART_RECEIVE  == DISABLE
	CLR_BIT(UCSRB ,UCSRB_RXEN);
#else
#error	"Invalid UART_RECEIVE Configuration "
#endif

#if 	UART_RESOLUTION == CHAR_SIZE_5
	Local_u8UCSRCBuffer &= CHAR_SIZE_MASK_VALUE;
	Local_u8UCSRCBuffer |= SIZE_5;
	ResolutionData = 5;

#elif 	UART_RESOLUTION == CHAR_SIZE_6
	Local_u8UCSRCBuffer &= CHAR_SIZE_MASK_VALUE;
	Local_u8UCSRCBuffer |= SIZE_6;
	ResolutionData = 6;

#elif 	UART_RESOLUTION == CHAR_SIZE_7
	Local_u8UCSRCBuffer &= CHAR_SIZE_MASK_VALUE;
	Local_u8UCSRCBuffer |= SIZE_7;
	ResolutionData = 7;

#elif 	UART_RESOLUTION == CHAR_SIZE_8
	Local_u8UCSRCBuffer &= CHAR_SIZE_MASK_VALUE;
	Local_u8UCSRCBuffer |= SIZE_8;
	ResolutionData = 8;

#elif 	UART_RESOLUTION == CHAR_SIZE_9
	Local_u8UCSRCBuffer &= CHAR_SIZE_MASK_VALUE;
	Local_u8UCSRCBuffer |= SIZE_9;
	SET_BIT(UCSRB ,UCSRB_UCSZ2);
	ResolutionData = 9;

#else
#error	"Invalid UART_RESOLUTION Configuration"
#endif

#if 	UART_PARITY == EVEN_PARITY
	Local_u8UCSRCBuffer &= PARITY_MASK_VALUE;
	Local_u8UCSRCBuffer |= EVEN;
#elif 	UART_PARITY == ODD_PARITY
	Local_u8UCSRCBuffer &= PARITY_MASK_VALUE;
	Local_u8UCSRCBuffer |= ODD;
#elif 	UART_PARITY == DISABLE_PARITY
	Local_u8UCSRCBuffer &= PARITY_MASK_VALUE;
	Local_u8UCSRCBuffer |= NO_PARITY;
#else
#error "Invalid UART_PARITY Configuration"
#endif

#if		UART_STOP_BIT == ONE_BIT
	Local_u8UCSRCBuffer &= STOP_MASK_VALUE;
	Local_u8UCSRCBuffer |= STOP_1;
#elif	UART_STOP_BIT == TWO_BIT
	Local_u8UCSRCBuffer &= STOP_MASK_VALUE;
	Local_u8UCSRCBuffer |= STOP_2;
#else
#error	"Invalid UART_STOP_BIT Configuration"
#endif

#if 	UART_SYNC_STATE	== ASYNCHRONOUS
	Local_u8UCSRCBuffer &= SYNC_MASK_VALUE;
	Local_u8UCSRCBuffer |= ASYNC;
#elif	UART_SYNC_STATE	== SYNCHRONOUS
	Local_u8UCSRCBuffer &= SYNC_MASK_VALUE;
	Local_u8UCSRCBuffer |= SYNC;

#if		UART_CLK_POL == T_RISING_R_FALLING
	Local_u8UCSRCBuffer &= POL_MASK_VALUE;
	Local_u8UCSRCBuffer |= RISING_T_FALLING_R;

#elif	UART_CLK_POL == T_FALLING_R_RISING
	Local_u8UCSRCBuffer &= POL_MASK_VALUE;
	Local_u8UCSRCBuffer |= RISING_R_FALLING_T;
#else
#error 	"Invalid UART_CLK_POL Configuration"
#endif

#else
#error 	"Invalid UART_SYNC_STATE Configuration"
#endif


	UCSRC = (1<<UCSRC_URSEL)|Local_u8UCSRCBuffer;

#if 	UART_DUABLE_SPEED == ENABLE
	SET_BIT(UCSRA , UCSRA_U2X);
#elif	UART_DUABLE_SPEED == DISABLE
	CLR_BIT(UCSRA , UCSRA_U2X);
#else
#error	"Invalid UART_DUABLE_SPEED Configuration"
#endif

#if 	UART_RECEIVE_INTERRUPT == ENABLE
	SET_BIT(UCSRB , UCSRB_RXCIE);
#elif	UART_RECEIVE_INTERRUPT == DISABLE
	CLR_BIT(UCSRB , UCSRB_RXCIE);
#else
#error	"Invalid UART_RECEIVE_INTERRUPT Configuration"

#endif

#if 	UART_TRANSMIT_INTERRUPT == ENABLE
	SET_BIT(UCSRB , UCSRB_TXCIE);
#elif	UART_TRANSMIT_INTERRUPT == DISABLE
	CLR_BIT(UCSRB , UCSRB_TXCIE);
#else
#error	"Invalid UART_TRANSMIT_INTERRUPT Configuration"
#endif

#if 	UART_DATA_EMPTY_INTERRUPT== ENABLE
	SET_BIT(UCSRB , UCSRB_UDRIE);
#elif	UART_DATA_EMPTY_INTERRUPT == DISABLE
	CLR_BIT(UCSRB , UCSRB_UDRIE);
#else
#error	"Invalid UART_DATA_EMPTY_INTERRUPT Configuration"

#endif

#elif	UART_STATE == DISABLE
	CLR_BIT(UCSRB ,UCSRB_TXEN);
	CLR_BIT(UCSRB ,UCSRB_RXEN);
#else
#error	"Invalid UART_STATE Configuration"
#endif


	Local_u16BaudRate = ( (F_CPU / 16)/(UART_u16_BAUDRATE*100)  )+1;

	if (Local_u16BaudRate > 255){
		Local_u16BaudRate++;
	}
	if (GET_BIT(UCSRA , UCSRA_MPCM) == 0 ){
		if (GET_BIT(UCSRA , UCSRA_U2X)){
			Local_u16BaudRate*=2;
		}
		else if (!GET_BIT(UCSRA , UCSRA_U2X)){
			Local_u16BaudRate*=1;
		}
	}
	else if (GET_BIT(UCSRA , UCSRA_MPCM) == 1){
		Local_u16BaudRate *=8;
	}
	UBRRL = (Local_u16BaudRate )-1;
	UBRRH = (((Local_u16BaudRate-1)>>8)&(BAUD_RATE_MASKING_VALUE));

}
u8 UART_u8SynchSendChar 			(u16 Copy_u16Data	){
	while (GET_BIT(UCSRA,UCSRA_UDRE) == 0);
	UDR = Copy_u16Data;
	return OK;
}
u8 UART_u8SynchRecive 			(u16*Copy_u16Data	){

	while (GET_BIT(UCSRA,UCSRA_RXC) == 0);
	*Copy_u16Data = UDR;
	if (ResolutionData == 9){
		*Copy_u16Data = GET_BIT(UCSRB,UCSRB_RXB8)<<8;
	}
	return OK;
}
u8 UART_u8SynchSendString		(u16*Copy_u16Data	){

	u16 *Local_ptr16 = Copy_u16Data;
	while (Local_ptr16 != '\0'){
		UART_u8SynchSendChar(*Local_ptr16);
		Local_ptr16++;
	}
	return OK;
}
u8 UART_u8ChangeCharSize	(u8 Copy_u8NewConfig){
	u8 Local_u8ErrorState = OK;
	UCSRC &= ((1<<UCSRC_URSEL)|CHAR_SIZE_MASK_VALUE);
	switch (Copy_u8NewConfig){
	default : Local_u8ErrorState = NOK;		break;
	case UART_DATA_RESOLUTION_5:CLR_BIT(UCSRB , UCSRB_UCSZ2);	break;
	case UART_DATA_RESOLUTION_6:CLR_BIT(UCSRB , UCSRB_UCSZ2);	UCSRC |= ((1<<UCSRC_URSEL)| (1<<UCSRC_UCSZ0));	break;
	case UART_DATA_RESOLUTION_7:CLR_BIT(UCSRB , UCSRB_UCSZ2);	UCSRC |= ((1<<UCSRC_URSEL)| (1<<UCSRC_UCSZ1));	break;
	case UART_DATA_RESOLUTION_8:CLR_BIT(UCSRB , UCSRB_UCSZ2);	UCSRC |= ((1<<UCSRC_URSEL)| (1<<UCSRC_UCSZ1)|(1<<UCSRC_UCSZ0));	break;
	case UART_DATA_RESOLUTION_9:SET_BIT(UCSRB , UCSRB_UCSZ2);	UCSRC |= ((1<<UCSRC_URSEL)| (1<<UCSRC_UCSZ1)|(1<<UCSRC_UCSZ0));	break;
	}
	ResolutionData = 5 + UART_DATA_RESOLUTION_5 ;
	return Local_u8ErrorState;
}
u8 UART_u8ChangeStopBit		(u8 Copy_u8NewConfig){
	u8 Local_u8ErrorState = OK;
	UCSRC &= ((1<<UCSRC_URSEL)|STOP_MASK_VALUE);
	switch (Copy_u8NewConfig){
	default : Local_u8ErrorState = NOK;				break;
	case UART_STOP_BITS_ONE	:/*No Action Needed */	break;
	case UART_STOP_BITS_TWO	:UCSRC |= ((1<<UCSRC_URSEL)| (1<<UCSRC_USBS));	break;
	}
	return Local_u8ErrorState;}
u8 UART_u8ChangeParity		(u8 Copy_u8NewConfig){
	u8 Local_u8ErrorState = OK;
	UCSRC &= ((1<<UCSRC_URSEL)|PARITY_MASK_VALUE);
	switch (Copy_u8NewConfig){
	default : Local_u8ErrorState = NOK;		break;
	case UART_PARITY_EVEN	:UCSRC |= ((1<<UCSRC_URSEL)| (1<<UCSRC_UPM1));	break;
	case UART_PARITY_ODD	:UCSRC |= ((1<<UCSRC_URSEL)| (1<<UCSRC_UPM0) | (1<<UCSRC_UPM1));	break;
	}
	return Local_u8ErrorState;
}
u8 UART_u8ChangeSyncState	(u8 Copy_u8NewConfig){
	u8 Local_u8ErrorState = OK;
	UCSRC &= ((1<<UCSRC_URSEL)|SYNC_MASK_VALUE);
	switch (Copy_u8NewConfig){
	default : Local_u8ErrorState = NOK;		break;
	case UART_ASYNC	:/*No action needed to clear UMSEL*/			break;
	case UART_SYNC	:UCSRC |= ((1<<UCSRC_URSEL)| (1<<UCSRC_UMSEL));	break;
	}
	return Local_u8ErrorState;
}
u8 UART_u8Disable			(	void		){
	CLR_BIT(UCSRB, UCSRB_TXEN);
	CLR_BIT(UCSRB, UCSRB_RXEN);
	return OK;
}
//u8 UART_u8SetActionToISR	(void (*fptr_Function)(void) , Copy_u8Interrupt);
u8 UART_u8InterruptEnable	(u8 Copy_u8Interrupt){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8Interrupt){
	default : Local_u8ErrorState = NOK;					break;
	case UART_RX_INTERRUPT:SET_BIT(UCSRB, UCSRB_RXCIE);	break;
	case UART_TX_INTERRUPT:SET_BIT(UCSRB, UCSRB_TXCIE);	break;
	case UART_UDR_INTERRUPT:SET_BIT(UCSRB, UCSRB_UDRIE);break;
	}
	return Local_u8ErrorState;
}
u8 UART_u8InterruptDisable	(u8 Copy_u8Interrupt){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8Interrupt){
	default : Local_u8ErrorState = NOK;					break;
	case UART_RX_INTERRUPT:CLR_BIT(UCSRB, UCSRB_RXCIE);	break;
	case UART_TX_INTERRUPT:CLR_BIT(UCSRB, UCSRB_TXCIE);	break;
	case UART_UDR_INTERRUPT:CLR_BIT(UCSRB, UCSRB_UDRIE);break;
	}
	return Local_u8ErrorState;
}


u8 UART_u8AsynchSendChar 		( u16 *Copy_u16Data	, void (*fptr_Function)(void)){
	u8 Local_u8ErrorState = OK;
	if ( (fptr_Function != NULL) && (Copy_u16Data != NULL)){
		if (Transmit == IDEL){
			Transmit = CHAR;
			TransmittData = Copy_u16Data;
			TX_Func = fptr_Function;
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
u8 UART_u8AsynchRecive 			(void (*fptr_Function)(u16*)){
	u8 Local_u8ErrorState = OK;
	if (fptr_Function != NULL){
		if (Receive == IDEL){
			Receive = UN_READ;
			RX_Func = fptr_Function;
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
u8 UART_u8AsynchSendString		( u16*Copy_u16Data	, void (*fptr_Function)(void)){
	u8 Local_u8ErrorState = OK;
	if ( (fptr_Function != NULL) && (Copy_u16Data != NULL)){
		if (Transmit == IDEL){
			Transmit = STRING;
			TransmittData = Copy_u16Data;
			TX_Func = fptr_Function;
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

/*Receive Complete*/
void __vector_13 (void)	__attribute__((signal));
void __vector_13 (void){
	if (Receive == UN_READ){
		RX_Func(ReceivedData);
		Receive = IDEL;
	}
}
/*UDR Empty*/
/*	Entered only when UDR empty (Transmit done)*/
void __vector_14 (void)	__attribute__((signal));
void __vector_14 (void){

	if (Transmit != IDEL){
		UDR = *TransmittData;
	}
}
/*Transmit Complete*/
void __vector_15 (void)	__attribute__((signal));
void __vector_15 (void){

	if (Transmit == CHAR){

		// Do nothing
	}
	else if (Transmit == STRING){
		//Update the TransmittData pointer
		if (TransmittData != '\0'){
			//UDR_Func();
			TransmittData++;
		}
		else if (Transmit == '\0'){
			// String is Sent
		}
	}
	//Do the needed action as user needs
	TX_Func();
	Transmit  = IDEL;
}
