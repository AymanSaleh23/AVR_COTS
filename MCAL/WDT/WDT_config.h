/*
 * WDT_config.h
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#ifndef MCAL_WDT_WDT_CONFIG_H_
#define MCAL_WDT_WDT_CONFIG_H_

/*
 * 	Options:
 * 		- ENABLE
 * 		- DISABLE
 */

#define WDT_STATE	ENABLE

#if 	WDT_STATE == ENABLE

/*
 * 	Options:
 * 		- PS_16MS3
 * 		- PS_32MS5
 * 		- PS_65MS
 * 		- PS_0S13
 * 		- PS_0S26
 * 		- PS_0S52
 * 		- PS_1S0
 * 		- PS_2S1
 */
#define WDT_PS	PS_2S1
#endif

#endif /* MCAL_WDT_WDT_CONFIG_H_ */
