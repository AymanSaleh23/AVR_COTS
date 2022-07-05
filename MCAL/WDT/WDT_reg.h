/*
 * WDT_reg.h
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#ifndef MCAL_WDT_WDT_REG_H_
#define MCAL_WDT_WDT_REG_H_


#define WDTCR	*((volatile u8*) 0x41)

#define WDTCR_WDTOE		4
#define WDTCR_WDE 		3
#define WDTCR_WDP2 		2
#define WDTCR_WDP1 		1
#define WDTCR_WDP0		0


#endif /* MCAL_WDT_WDT_REG_H_ */
