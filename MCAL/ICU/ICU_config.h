/*
 * ICU_config.h
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#ifndef MCAL_ICU_ICU_CONFIG_H_
#define MCAL_ICU_ICU_CONFIG_H_


/*
 * 	Options:
 * 		- ENABLE
 * 		- DISABLE
 *
 */
#define ICU_STATE	ENABLE

#if ICU_STATE == ENABLE

/*
 * 	Options:
 * 		- NORMAL_MODE
 * 		- EDGE_MODE
 *
 */

#define ICU_MODE	NORMAL_MODE
#endif
/*
 * 	Options:
 * 		- INVERTED
 * 		- NON_INVERTED
 */
#define ICU_POLARITY	NON_IVERTED

/*
 * 	Options:
 * 		- FALLING_EDGE
 * 		- RISING_EDGE
 */
#define ICU_EDGE_SELECT	RISING_EDGE

/*
 * 	Options:
 * 		- ENABLE
 * 		- DISABLE
 *
 */
#define ICU_NOICE_CANCLER	DISABLE

#endif /* MCAL_ICU_ICU_CONFIG_H_ */
