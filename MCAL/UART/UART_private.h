/*
 * UART_private.h
 *
 *  Created on: Oct 1, 2021
 *      Author: 20114
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#define ENABLE	1
#define DISABLE	2

#define CHAR_SIZE_5		1
#define CHAR_SIZE_6		2
#define CHAR_SIZE_7		3
#define CHAR_SIZE_8		4
#define CHAR_SIZE_9		5

#define ASYNCHRONOUS	1
#define SYNCHRONOUS		2

#define EVEN_PARITY		1
#define ODD_PARITY		2
#define DISABLE_PARITY	3

#define ONE_BIT		1
#define TWO_BIT		2

#define T_RISING_R_FALLING	1
#define T_FALLING_R_RISING	2

#define B2400 	24
#define B4800 	48
#define B9600 	96
#define B14K4 	144
#define B19K2 	192
#define B28K8 	288
#define B38K4 	384
#define B57K6 	576
#define B76K8 	768
#define B115K2	1152
#define B230K4	2304
#define B250K 	2500

#define NO_PARITY			0b00000000
#define ODD					0b00110000
#define EVEN				0b00100000
#define PARITY_MASK_VALUE	0b1001111

#define STOP_1				0b0000000
#define STOP_2				0b0001000
#define STOP_MASK_VALUE		0b1110111


#define SYNC				0b1000000
#define ASYNC				0b0000000
#define SYNC_MASK_VALUE		0b0111111

#define RISING_T_FALLING_R	0b0000000
#define RISING_R_FALLING_T	0b0000001
#define POL_MASK_VALUE		0b1111110

#define SIZE_5				0b0000000
#define SIZE_6				0b0000010
#define SIZE_7				0b0000100
#define SIZE_8				0b0000110
#define SIZE_9				0b0000110
#define CHAR_SIZE_MASK_VALUE	0b1111001

#define BAUD_RATE_MASKING_VALUE	0b01111111

#define IDEL		0
#define CHAR		1
#define STRING		2
#define UN_READ		3

#endif /* MCAL_UART_UART_PRIVATE_H_ */
