/***************************************************************************************/
/***************************************************************************************/
/*******************************	Author : Ayman Saleh				****************/
/*******************************	Date   : 2-9-2021					****************/
/*******************************	Layer  : MCAL						****************/
/*******************************	SWC    : External Exception	(EXTI)	****************/
/*******************************	Version:1.0.0						****************/
/***************************************************************************************/
/***************************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/Err_Type.h"

#include "EXTI_private.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "EXTI_reg.h"

/*	@GLobal_Pointer_To_Function Holds INTx ISR Addresses	*/
static void (* EXTI_ptrv_CallBackFuncAddress[3]) (void) = {NULL};

void EXTI_voidInit(void){
	/***************************************		***************************************/
	//Set PIE (Peripheral Interrupt Enable)
#if INT0_u8_INITIAL_STATE == ENABLED
	SET_BIT(GICR , GICR_INT0);

#elif INT0_u8_INITIAL_STATE == DISABLED
	CLR_BIT(GICR , GICR_INT0);
#else
#error	"Wrong INT0_u8_INITIAL_STATE Configuration option"
#endif

#if INT1_u8_INITIAL_STATE == ENABLED
	SET_BIT(GICR , GICR_INT1);

#elif INT1_u8_INITIAL_STATE == DISABLED
	CLR_BIT(GICR , GICR_INT1);
#else
#error	"Wrong INT0_u8_INITIAL_STATE Configuration option"
#endif

#if INT2_u8_INITIAL_STATE == ENABLED
	SET_BIT(GICR , GICR_INT2);

#elif INT2_u8_INITIAL_STATE == DISABLED
	CLR_BIT(GICR , GICR_INT2);
#else
#error	"Wrong INT0_u8_INITIAL_STATE Configuration option"
#endif

	/***************************************		Set Interrupt Sense control		*********************************************************/
	/*		Check on Sense Control	INT0	*/
#if INT0_u8_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR , MCUCR_ISC00);
	CLR_BIT(MCUCR , MCUCR_ISC01);
#elif	INT0_u8_SENSE == ON_CHANGE_LEVEL
	SET_BIT(MCUCR , MCUCR_ISC00);
	CLR_BIT(MCUCR , MCUCR_ISC01);
#elif	INT0_u8_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR , MCUCR_ISC00);
	SET_BIT(MCUCR , MCUCR_ISC01);
#elif	INT0_u8_SENSE == RISING_EDGE
	SET_BIT(MCUCR , MCUCR_ISC00);
	SET_BIT(MCUCR , MCUCR_ISC01);
#else
#error " Wrong INT0_u8_SENSE Configuration option"
#endif

	/*		Check on Sense Control	INT1	*/

#if INT1_u8_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR , MCUCR_ISC10);
	CLR_BIT(MCUCR , MCUCR_ISC11);
#elif	INT1_u8_SENSE == ON_CHANGE_LEVEL
	SET_BIT(MCUCR , MCUCR_ISC10);
	CLR_BIT(MCUCR , MCUCR_ISC11);
#elif	INT1_u8_SENSE == FALLING_EDGE
	CLR_BIT(MCUCR , MCUCR_ISC10);
	SET_BIT(MCUCR , MCUCR_ISC11);
#elif	INT1_u8_SENSE == RISING_EDGE
	SET_BIT(MCUCR , MCUCR_ISC10);
	SET_BIT(MCUCR , MCUCR_ISC11);
#else
#error " Wrong INT1_u8_SENSE Configuration option"
#endif

	/*		Check on Sense Control	INT2	*/
#if INT2_u8_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR , MCUCSR_ISC2);
	SET_BIT(MCUCSR , MCUCSR_ISC2);
#elif	INT2_u8_SENSE == RISING_EDGE
	SET_BIT(MCUCSR , MCUCSR_ISC2);
	SET_BIT(MCUCSR , MCUCSR_ISC2);
#else
#error " Wrong INT2_u8_SENSE Configuration option"
#endif
}


u8 EXTI_u8EnableInit( u8 Copy_u8IntNum){
	u8 Local_u8ErrorState = OK;

	switch (Copy_u8IntNum){
	default	 : Local_u8ErrorState = NOK;break;
	case INT0: SET_BIT(GICR , GICR_INT0);break;
	case INT1: SET_BIT(GICR , GICR_INT1);break;
	case INT2: SET_BIT(GICR , GICR_INT2);break;
	}

	return Local_u8ErrorState;
}
u8 EXTI_u8DidableInit( u8 Copy_u8IntNum){
	u8 Local_u8ErrorState = OK;
	switch (Copy_u8IntNum){
	default	 : Local_u8ErrorState = NOK;break;
	case INT0: CLR_BIT(GICR , GICR_INT0);break;
	case INT1: CLR_BIT(GICR , GICR_INT1);break;
	case INT2: CLR_BIT(GICR , GICR_INT2);break;
	}
	return Local_u8ErrorState;
}

u8 EXTI_u8SetSenseControl( u8 Copy_u8IntNum , u8 Copy_u8Sense){
	u8 Local_u8ErrorState = OK;

	switch (Copy_u8IntNum){
	default	 : Local_u8ErrorState = NOK;break;
	case INT0:
		if ( LOW_LEVEL_SENSE == Copy_u8Sense){
			CLR_BIT(MCUCR , MCUCR_ISC00);
			CLR_BIT(MCUCR , MCUCR_ISC01);
		}
		else if (ON_SHANGE_SENSE == Copy_u8Sense){
			SET_BIT(MCUCR , MCUCR_ISC00);
			CLR_BIT(MCUCR , MCUCR_ISC01);
		}
		else if (FALLING_EDGE_SENSE == Copy_u8Sense){
			CLR_BIT(MCUCR , MCUCR_ISC00);
			SET_BIT(MCUCR , MCUCR_ISC01);
		}
		else if (RISING_EDGE_SENSE == Copy_u8Sense){
			SET_BIT(MCUCR , MCUCR_ISC00);
			SET_BIT(MCUCR , MCUCR_ISC01);
		}
		else {
			Local_u8ErrorState = NOK;
		}
		break;
	case INT1:
		if ( LOW_LEVEL_SENSE == Copy_u8Sense){
			CLR_BIT(MCUCR , MCUCR_ISC10);
			CLR_BIT(MCUCR , MCUCR_ISC11);
		}
		else if (ON_SHANGE_SENSE == Copy_u8Sense){
			SET_BIT(MCUCR , MCUCR_ISC10);
			CLR_BIT(MCUCR , MCUCR_ISC11);
		}
		else if (FALLING_EDGE_SENSE == Copy_u8Sense){
			CLR_BIT(MCUCR , MCUCR_ISC10);
			SET_BIT(MCUCR , MCUCR_ISC11);
		}
		else if (RISING_EDGE_SENSE == Copy_u8Sense){
			SET_BIT(MCUCR , MCUCR_ISC10);
			SET_BIT(MCUCR , MCUCR_ISC11);
		}
		else {
			Local_u8ErrorState = NOK;
		}
		break;
	case INT2:
		if (FALLING_EDGE_SENSE == Copy_u8Sense){
			CLR_BIT(MCUCSR , MCUCSR_ISC2);
		}
		else if (RISING_EDGE_SENSE == Copy_u8Sense){
			SET_BIT(MCUCSR , MCUCSR_ISC2);
		}
		else {
			Local_u8ErrorState = NOK;
		}
		break;
	}

	return Local_u8ErrorState;
}

/*************Call Back Function Passes Functions Addresses to the GLobal pointer to Function @GLobal_Pointer_To_Function********************/
u8 EXTI_u8SetCallBack( void (*ptrv_CallBackFunc) (void) , u8 Copy_u8EXTINumber){
	u8 Local_u8ErrorState = OK;
	if (ptrv_CallBackFunc != NULL){

		if (INT2 >= Copy_u8EXTINumber){
			EXTI_ptrv_CallBackFuncAddress[Copy_u8EXTINumber] = ptrv_CallBackFunc;
		}
		else {
			Local_u8ErrorState = NOK;
		}
	}
	else{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}

/******************************			ISR for INT0		*********************************/
void __vector_1 (void)	__attribute__((signal));
void __vector_1 (void){
	if (EXTI_ptrv_CallBackFuncAddress[INT0] != NULL){
		EXTI_ptrv_CallBackFuncAddress[INT0]();
	}
	else {

	}
}

/******************************			ISR for INT1		*********************************/
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void){
	if (EXTI_ptrv_CallBackFuncAddress[INT1] != NULL){
		EXTI_ptrv_CallBackFuncAddress[INT1]();
	}
	else {

	}
}

/******************************			ISR for INT2		*********************************/
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void){
	if (EXTI_ptrv_CallBackFuncAddress[INT2] != NULL){
		EXTI_ptrv_CallBackFuncAddress[INT2]();
	}
	else {

	}
}
