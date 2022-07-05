/*
 * ICU_interface.h
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */

#ifndef MCAL_ICU_ICU_INTERFACE_H_
#define MCAL_ICU_ICU_INTERFACE_H_

#define ICU_INVERTED		0
#define ICU_NON_INVERTED	1

#define ICU_RISING		0
#define ICU_FALLING		1

#define ICU_NORMAL_MODE		0
#define ICU_EDGE_MODE		1

#define ICU_NOISE_CANCELER_ENABLE	0
#define ICU_NOISE_CANCELER_DISABLE	1

typedef struct{
	u16 Period;
	u8 	Duty;
	u16	OnTime;
	u16	OffTime;
}ICU_Data;

void ICU_u8Init				( 	void	);
u8 ICU_u8Enable				( 	u8 Copy_u8Polarity , u8 Copy_u8EdgeSelect	);
void ICU_voidDisable		( 	void	);
u8 ICU_u8ChangeEdgeSelect	(	u8 Copy_u8EdgeSelect	);
u8 ICU_u8ChangePolarity		(	u8 Copy_u8Polarity	);
u8 ICU_u8GetData			( 	ICU_Data * CopyObj_ICUData );
u8 ICU_u8SenseEdge			( 	u8 Copy_u8Edge , void(ptr8_NotificationICU)(void) );
u8 ICU_u8SenseMode 			( 	u8 Copy_u8Mode);
u8 LCU_u8NoiceCanceler		( 	u8 Copy_u8Case);
#endif /* MCAL_ICU_ICU_INTERFACE_H_ */
