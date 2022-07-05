/*
 * WDT_private.h
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#ifndef MCAL_WDT_WDT_PRIVATE_H_
#define MCAL_WDT_WDT_PRIVATE_H_

#define DISABLE	1
#define ENABLE	2

#define PS_16MS3	0
#define PS_32MS5	1
#define PS_65MS		2
#define PS_0S13		3
#define PS_0S26		4
#define PS_0S52		5
#define PS_1S0		6
#define PS_2S1		7
#define UNDEFINED	8

#define PS_MASKING_VALUE 	0b11111000

#define DISABLE_WDT_STEP_1	0b00011000
#define DISABLE_WDT_STEP_2	0b00000000

#endif /* MCAL_WDT_WDT_PRIVATE_H_ */
