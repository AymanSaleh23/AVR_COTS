/*
 * WDT_interface.h
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#ifndef MCAL_WDT_WDT_INTERFACE_H_
#define MCAL_WDT_WDT_INTERFACE_H_

#define WDT_16ms3	1
#define WDT_32ms5	2
#define WDT_65ms	3
#define WDT_0s13	4
#define WDT_0s26	5
#define WDT_0s52	6
#define WDT_1s0		7
#define WDT_2s1		8

void	WDT_voidInit		(	void	);
u8 		WDT_u8Enable		(	u8 Copy_u8Time	);
u8 		WDT_u8ChangeTime	(	u8 Copy_u8Time	);
u8 		WDT_u8ReEnable		(	void	);
void 	WDT_voidDisable		(	void	);


#endif /* MCAL_WDT_WDT_INTERFACE_H_ */
