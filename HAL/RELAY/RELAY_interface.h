/*
 * RELAY_interface.h
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#ifndef HAL_RELAY_RELAY_INTERFACE_H_
#define HAL_RELAY_RELAY_INTERFACE_H_

#define RELAY_ON	1
#define RELAY_OFF	2

typedef struct{
	u8 PORT;
	u8 PIN;

}RELAY_Type;

u8 RELAY_u8Operation	(	const RELAY_Type * Copy_RelayObj , u8 Copy_u8Operation);

#endif /* HAL_RELAY_RELAY_INTERFACE_H_ */
