/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 30-8-2021		***************************/
/*******************************	Version: 1.0.0			***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : Keypad			***************************/
/**************************************************************************************/
/**************************************************************************************/

#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_



#define KPD_u8_PORT			DIO_u8_PORTB

#define KPD_u8_COL0_PIN		DIO_u8_PIN0
#define KPD_u8_COL1_PIN		DIO_u8_PIN1
#define KPD_u8_COL2_PIN		DIO_u8_PIN2
#define KPD_u8_COL3_PIN		DIO_u8_PIN3


#define KPD_u8_ROW0_PIN		DIO_u8_PIN4
#define KPD_u8_ROW1_PIN		DIO_u8_PIN5
#define KPD_u8_ROW2_PIN		DIO_u8_PIN6
#define KPD_u8_ROW3_PIN		DIO_u8_PIN7

#define KPD_NO_PRESSED_KEY	0xff

#define KPD_KEY_ARRAY_VALUE		 {{7, 8 ,9,'R'},{4,5,6,'R'},{1,2,3,'R'},{'c',0,'x','R'}};

#endif /* HAL_KPD_KPD_CONFIG_H_ */
