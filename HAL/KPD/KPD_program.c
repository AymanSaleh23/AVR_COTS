/**************************************************************************************/
/**************************************************************************************/
/*******************************	Author : Ayman Saleh	***************************/
/*******************************	Date   : 30-8-2021		***************************/
/*******************************	Version: 1.0.0			***************************/
/*******************************	Layer  : HAL			***************************/
/*******************************	SWC    : Keypad			***************************/
/**************************************************************************************/
/**************************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"


u8 KPD_u8GetPressedKey(void){

	//	A SW trick to save Stack from high size consumption by save these variables on .bss section on memory
	static u8 Local_u8KPDArr [KPD_ROW_NUM][KPD_COL_NUM] = KPD_KEY_ARRAY_VALUE;

	static u8 Local_u8KPDRow [KPD_ROW_NUM]={ KPD_u8_ROW0_PIN , KPD_u8_ROW1_PIN , KPD_u8_ROW2_PIN , KPD_u8_ROW3_PIN};
	static u8 Local_u8KPDCol [KPD_COL_NUM]={ KPD_u8_COL0_PIN , KPD_u8_COL1_PIN , KPD_u8_COL2_PIN , KPD_u8_COL3_PIN};

	u8 Local_u8COlCheck = -1, Local_u8ROWCheck= -1;
	u8 Local_u8PinState = KPD_NO_PRESSED_KEY;
	u8 Local_u8SelectedRow , Local_u8SelectedCol;

	for (Local_u8COlCheck = 0  ; Local_u8COlCheck < KPD_COL_NUM ;Local_u8COlCheck++ ){
		DIO_u8SetPinValue(KPD_u8_PORT , Local_u8KPDCol[Local_u8COlCheck] , DIO_u8_PIN_LOW);

		Local_u8SelectedCol = Local_u8COlCheck;

		for (Local_u8ROWCheck = 0 ; Local_u8ROWCheck < KPD_ROW_NUM ; Local_u8ROWCheck++ ){
			DIO_u8GetPinValue(KPD_u8_PORT ,Local_u8KPDRow[Local_u8ROWCheck] , &Local_u8PinState);

			// SW Trick to not to forget the equality operator (attempt to assign value on a constant)
			if ( 0 == Local_u8PinState){
				Local_u8SelectedRow = Local_u8ROWCheck ;
				// Busy Wait till button is released
				while ( 0 == Local_u8PinState ){
					DIO_u8GetPinValue(KPD_u8_PORT ,Local_u8KPDRow[Local_u8ROWCheck] , &Local_u8PinState);
				}
				return Local_u8KPDArr[Local_u8SelectedRow][Local_u8SelectedCol];
			}
			// else Do Nothing

		}
		DIO_u8SetPinValue(KPD_u8_PORT , Local_u8KPDCol[Local_u8COlCheck] , DIO_u8_PIN_HIGH);


	}

	return KPD_NO_PRESSED_KEY;
}
