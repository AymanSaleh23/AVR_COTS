/*
 * UART_interface.h
 *
 *  Created on: Oct 1, 2021
 *      Author: 20114
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#define UART_DATA_RESOLUTION_5	0
#define UART_DATA_RESOLUTION_6	1
#define UART_DATA_RESOLUTION_7	2
#define UART_DATA_RESOLUTION_8	3
#define UART_DATA_RESOLUTION_9	4

#define UART_STOP_BITS_ONE		0
#define UART_STOP_BITS_TWO		1

#define UART_PARITY_ODD			0
#define UART_PARITY_EVEN		1
#define UART_PARITY_DISABLED	2

#define UART_SYNC				0
#define UART_ASYNC				1

#define UART_BAUD_RATE_2400		0
#define UART_BAUD_RATE_4800 	1
#define UART_BAUD_RATE_9600  	2
#define UART_BAUD_RATE_14400 	3
#define UART_BAUD_RATE_19200 	4
#define UART_BAUD_RATE_28800	5
#define UART_BAUD_RATE_38400 	6
#define UART_BAUD_RATE_57600 	7
#define UART_BAUD_RATE_76800	8
#define UART_BAUD_RATE_115200	9
#define UART_BAUD_RATE_230400	10
#define UART_BAUD_RATE_250000	11

#define UART_TX_INTERRUPT		0
#define UART_RX_INTERRUPT		1
#define UART_UDR_INTERRUPT		2

void UART_u8Init 				(	void		);
u8 UART_u8SynchSendChar 		(u16 Copy_u16Data	);
u8 UART_u8SynchRecive 			(u16*Copy_u16Data	);
u8 UART_u8SynchSendString		(u16*Copy_u16Data	);
u8 UART_u8ChangeCharSize		(u8 Copy_u8NewConfig);
u8 UART_u8ChangeStopBit			(u8 Copy_u8NewConfig);
u8 UART_u8ChangeParity			(u8 Copy_u8NewConfig);
u8 UART_u8ChangeSyncState		(u8 Copy_u8NewConfig);
u8 UART_u8Disable				(	void		);
//u8 UART_u8SetActionToISR		(void (*fptr_Function)(void) , Copy_u8Interrupt);
u8 UART_u8InterruptEnable		(u8 Copy_u8Interrupt);
u8 UART_u8InterruptDisable		(u8 Copy_u8Interrupt);

u8 UART_u8AsynchSendChar 		( u16 *Copy_u16Data	, void (*fptr_Function)(void));
u8 UART_u8AsynchRecive 			(void (*fptr_Function)(u16*));
u8 UART_u8AsynchSendString		( u16*Copy_u16Data	, void (*fptr_Function)(void));

#endif /* MCAL_UART_UART_INTERFACE_H_ */
