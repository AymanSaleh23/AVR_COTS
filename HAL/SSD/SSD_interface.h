/******************************************************************************************/
/******************************************************************************************/
/*******************************	Author : Ayman Saleh		***************************/
/*******************************	Date   : 19-8-2021			***************************/
/*******************************	Version: 1.0.0				***************************/
/*******************************	Layer  : HAL				***************************/
/*******************************	SWC    : SSD (7 segments)	***************************/
/******************************************************************************************/
/******************************************************************************************/


#ifndef SEG_INTERFACE_H_
#define SEG_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

#define SSD_u8_OUTSIDE_UC					8
#define SSD_u8_NO_COMMON_PIN_PORT_SUPPORTED	4

#define SSD_u8_COMMON_ANODE 		0
#define SSD_u8_COMMON_CATHODE 		1

#define SSD_u8_DEC					9
#define SSD_u8_HEX					15

typedef struct {
	u8 PORT;
	u8 CommonMode;
	u8 CommonPin;
	u8 CommonPinPort;
	u8 NumberSystem;
}SSD_type;

u8 SSD_u8Init	 	(const SSD_type* copy_u8SSDObject);
u8 SSD_u8SendNum 	(const SSD_type* copy_u8SSDObject , u8 copy_u8Number);
void SSD_voidOff	(const SSD_type* copy_u8SSDObject);
void SSD_voidOn		(const SSD_type* copy_u8SSDObject);

#endif
