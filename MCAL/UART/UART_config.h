/*
 * UART_config.h
 *
 *  Created on: Oct 1, 2021
 *      Author: 20114
 */

#ifndef MCAL_UART_UART_CONFIG_H_
#define MCAL_UART_UART_CONFIG_H_

/*	Options:
 * 		ENABLE
 * 		DISABLE
 */

#define UART_STATE		ENABLE

/*	Options:
 * 		ENABLE
 * 		DISABLE
 */

#define UART_TRANSMIT	ENABLE

/*	Options:
 * 		ENABLE
 * 		DISABLE
 */

#define UART_RECEIVE		ENABLE

/*	Options:
 * 		ENABLE
 * 		DISABLE
 */
#define UART_TRANSMIT_INTERRUPT	DISABLE

/*	Options:
 * 		ENABLE
 * 		DISABLE
 */
#define UART_RECEIVE_INTERRUPT	DISABLE

/*	Options:
 * 		ENABLE
 * 		DISABLE
 */
#define UART_DATA_EMPTY_INTERRUPT	DISABLE
/*	Options:
 * 		CHAR_SIZE_5
 * 		CHAR_SIZE_6
 * 		CHAR_SIZE_7
 * 		CHAR_SIZE_8
 * 		CHAR_SIZE_9
 */

#define UART_RESOLUTION	CHAR_SIZE_8

/*	Options:
 * 		ODD_PARITY
 * 		EVEN_PARITY
 * 		DISABLE_PARITY
 */

#define UART_PARITY		DISABLE_PARITY

/*	Options:
 * 		ONE_BIT
 * 		TWO_BIT
 */

#define UART_STOP_BIT	ONE_BIT

/*	Options:
 * 		SYNCHRONOUS
 * 		ASYNCHRONOUS
 */

#define UART_SYNC_STATE	ASYNCHRONOUS

#if UART_SYNC_STATE == 	SYNCHRONOUS

/*	Options:
 * 		T_RISING_R_FALLING
 * 		T_FALLING_R_RISING
 */

#define	UART_CLK_POL	T_RISING_R_FALLING
#endif

/*	Options:
 * 		B2400
 * 		B4800
 * 		B9600
 * 		B14K4
 * 		B19K2
 * 		B28K8
 * 		B38K4
 * 		B57K6
 * 		B76K8
 * 		B115K2
 * 		B230K4
 * 		B250K
 */

#define UART_u16_BAUDRATE	B9600

/*	Options:
 * 		ENABLE
 * 		DISABLE
 */

#define UART_DUABLE_SPEED	DISABLE

#endif /* MCAL_UART_UART_CONFIG_H_ */
