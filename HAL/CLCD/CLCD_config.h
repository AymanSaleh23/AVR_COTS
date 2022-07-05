/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 26-8-2021		***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : CLCD			***************************/
/*******************************	Version: 1.0.0			***************************/
/**************************************************************************************/
/**************************************************************************************/


#ifndef HAL_CLCD_CLCD_CONFIG_H_
#define HAL_CLCD_CLCD_CONFIG_H_

/*
 * Port A ----> DIO_PORTA
 * Port B ----> DIO_PORTB
 * Port C ----> DIO_PORTC
 * Port D ----> DIO_PORTD
 */

#define CLCD_u8_DATA_PORT_CONFIG		DIO_u8_PORTC
#define CLCD_u8_CTRL_PORT_CONFIG		DIO_u8_PORTC

/*
 * PIN0   ----> DIO_PIN0
 * PIN1   ----> DIO_PIN1
 * PIN2   ----> DIO_PIN2
 * PIN3   ----> DIO_PIN3
 * PIN4   ----> DIO_PIN4
 * PIN5   ----> DIO_PIN5
 * PIN6   ----> DIO_PIN6
 * PIN7   ----> DIO_PIN7
 */

//Enable Bit
#define CLCD_EN_CONFIG	DIO_u8_PIN0

//Read or Write Bit
#define CLCD_RW_CONFIG	DIO_u8_PIN1

// Register Select Bit
#define CLCD_RS_CONFIG	DIO_u8_PIN2

/*
  Options:
  	  LINES_8
  	  LINES_4
 */
#define CLCD_u8_INTERFACE_LINES		LINES_4

/*
	Options :
		function Set
			LCD_8BIT
			LCD_4BIT
			LCD_ONE_LINE
			LCD_TWO_LINE
			LCD_FONT_5_7
			LCD_FONT_5_8

		Display ON/OFF
			LCD_DISPLAY_ON
			LCD_DISPLAY_OFF
			LCD_CURSOR_ON
			LCD_CURSOR_OFF
			LCD_CURSOR_BLINK
			LCD_CURSOR_NOT_BLINK

*/

#if CLCD_u8_INTERFACE_LINES == LINES_8

#define CLCD_u8_FUNCTION_SET			0b00110000 | CLCD_u8_N | CLCD_u8_F
#define CLCD_u8_DISPLAY_ON_OFF			0b00001000 | CLCD_u8_D  | CLCD_u8_C | CLCD_u8_B
#define CLCD_u8_DISPLAY_CLEAR			0b00000001

#elif CLCD_u8_INTERFACE_LINES == LINES_4

#define CLCD_u8_FUNCTION_SET			0b00100000 | CLCD_u8_N | CLCD_u8_F
#define CLCD_u8_DISPLAY_ON_OFF			0b00001000 | CLCD_u8_D  | CLCD_u8_C | CLCD_u8_B
#define CLCD_u8_DISPLAY_CLEAR			0b00000001

/*	Options:-
  		DIO_u8_PIN0
 		DIO_u8_PIN1
  		DIO_u8_PIN2
  		DIO_u8_PIN3
 		DIO_u8_PIN4
  		DIO_u8_PIN5
  		DIO_u8_PIN6
  		DIO_u8_PIN7
 */

#define CLCD_u8_D7		DIO_u8_PIN7
#define CLCD_u8_D6		DIO_u8_PIN6
#define CLCD_u8_D5		DIO_u8_PIN5
#define CLCD_u8_D4		DIO_u8_PIN4

#endif

#define CLCD_u8_N	(CLCD_u8_TWO_LINE  << CLCD_u8_N_BIT)
#define CLCD_u8_F	(CLCD_u8_FONT_5_8  << CLCD_u8_F_BIT)

#define CLCD_u8_D	(CLCD_u8_DISPLAY_ON  	 <<   CLCD_u8_D_BIT)
#define CLCD_u8_C	(CLCD_u8_CURSOR_OFF  	 <<   CLCD_u8_C_BIT)
#define CLCD_u8_B	(CLCD_u8_CURSOR_NOT_BLINK<<   CLCD_u8_B_BIT)





#endif /* HAL_CLCD_CLCD_CONFIG_H_ */
