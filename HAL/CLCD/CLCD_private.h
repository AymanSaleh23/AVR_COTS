/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 26-8-2021		***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : CLCD			***************************/
/*******************************	Version: 1.0.0			***************************/
/**************************************************************************************/
/**************************************************************************************/


#ifndef HAL_CLCD_CLCD_PRIVATE_H_
#define HAL_CLCD_CLCD_PRIVATE_H_

/* Function Set
	DB7		DB6		DB5		DB4		DB3		DB2		DB1		DB0
	 0		 0		 1		1		 N		 F		 -		 -


	 N  = Number Of Length		1 (Single Line) , 	0 (Double Line)
	 F  = Font					1 (5*7) 		, 	0 (5*8)
*/


// Function Set
#define CLCD_u8_ONE_LINE	0
#define CLCD_u8_TWO_LINE	1
#define CLCD_u8_FONT_5_11	1
#define CLCD_u8_FONT_5_8	0

#define CLCD_u8_N_BIT 	3
#define CLCD_u8_F_BIT	2

/*	Display On/Off
 * 	DB7		DB6		DB5		DB4		DB3		DB2		DB1		DB0
	0		 0		 0		 0		 1		 D		 C		 B

	D = Display  		1 (on)  				, 	0	(off)
	C = Cursor  		1 (not Display) 		, 	0 	(Display)
	B = Cursor Blink	1 (Blinking for 0.4s)	,	0 	(Blinking Off)
 */

// Display On/Off
#define CLCD_u8_DISPLAY_ON			1
#define CLCD_u8_DISPLAY_OFF			0
#define CLCD_u8_CURSOR_ON			1
#define CLCD_u8_CURSOR_OFF			0
#define CLCD_u8_CURSOR_BLINK		1
#define CLCD_u8_CURSOR_NOT_BLINK	0

#define CLCD_u8_D_BIT	2
#define CLCD_u8_C_BIT	1
#define CLCD_u8_B_BIT	0

#define LINES_8		1
#define LINES_4		2

#define CLCD_u8_TO_CGRAM	64
#define CLCD_u8_TO_DDRAM	128
#endif /* HAL_CLCD_CLCD_PRIVATE_H_ */
