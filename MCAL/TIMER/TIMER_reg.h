/*
 * TIMER_reg.h
 *
 *  Created on: Sep 12, 2021
 *      Author: 20114
 */

#ifndef MCAL_TIMER_TIMER_REG_H_
#define MCAL_TIMER_TIMER_REG_H_


/*	Timer/Counter Maskable Interrupt Reg 	*/

#define TIMSK	*((volatile u8*)0x59)

#define TIMSK_TOIE0		0
#define TIMSK_OCIE0		1
#define TIMSK_TOIE1		2
#define TIMSK_OCIE1B	3
#define TIMSK_OCIE1A	4
#define TIMSK_TOIE2		6
#define TIMSK_OCIE2		7

/*	Timer/Counter  Interrupt Flag Reg		*/

#define TIFR	*((volatile u8*)0x58)
#define TIFR_TOV0       0
#define TIFR_OCF0       1
#define TIFR_TOV1       2
#define TIFR_OCF1B      3
#define TIFR_OCF1A      4
#define TIFR_TOV2       6
#define TIFR_OCF2       7

/*	Timer/Counter Prescaler Control		SFIOR	*/

#define SFIOR	*((volatile u8*)0x50)

#define SFIOR_PSR10		0
#define SFIOR_PSR2		1

/*********************	Timer/Counter 0		8-Bit with PWM	*******************/
/*	Timer/Counter 0 Output Compare Reg				*/

#define OCR0	*((volatile u8*)0x5C)

/*	Timer/Counter 0 Control Reg						*/

#define TCCR0	*((volatile u8*)0x53)

#define TCCR0_FOC0		0
#define TCCR0_WGM00		1
#define TCCR0_COM01		2
#define TCCR0_COM00		3
#define TCCR0_WGM01		4
#define TCCR0_CS02		5
#define TCCR0_CS01		6
#define TCCR0_CS00		7
/*	Timer/Counter 0 Count	Reg						*/

#define TCNT0	*((volatile u8*)0x52)


/*********************	Timer/Counter 1	16-Bit	*******************/

/*	Timer/Counter 1 Count	Reg						*/

#define TCNT1H	*((volatile u8*)0x4D)
#define TCNT1L	*((volatile u8*)0x4C)
#define TCNT1	*((volatile u16*)0x4C)

/*	Timer/Counter 1 A Control Reg						*/

#define TCCR1A	*((volatile u8*)0x4F)

#define TCCR1A_WGM10       0
#define TCCR1A_WGM11       1
#define TCCR1A_FOC1B       2
#define TCCR1A_FOC1A       3
#define TCCR1A_COM1B0      4
#define TCCR1A_COM1B1      5
#define TCCR1A_COM1A0      6
#define TCCR1A_COM1A1      7

/*	Timer/Counter 1 B Control Reg						*/

#define TCCR1B	*((volatile u8*)0x4E)

#define TCCR1B_CS10			0
#define TCCR1B_CS11			1
#define TCCR1B_CS12			2
#define TCCR1B_WGM12		3
#define TCCR1B_WGM13		4
//	Bit 5  Reserved


#define TCCR1	*((volatile u16*)0x4E)


/*	Timer/Counter 1 A Output Compare Reg				*/

#define OCR1AH	*((volatile u8*)0x4B)
#define OCR1Al  *((volatile u8*)0x4A)
#define OCR1A   *((volatile u16*)0x4A)

/*	Timer/Counter 1 B Output Compare Reg				*/

#define OCR1BH	*((volatile u8*)0x49)
#define OCR1Bl  *((volatile u8*)0x48)
#define OCR1B   *((volatile u16*)0x48)


/*********************	Timer/Counter 2		*******************/
/*	Timer/Counter 2 Control Reg						*/

#define TCCR2	*((volatile u8*)0x45)

#define TCCR2_CS20			0
#define TCCR2_CS21			1
#define TCCR2_CS22			2
#define TCCR2_WGM21			3
#define TCCR2_COM20			4
#define TCCR2_COM21 		5
#define TCCR2_WGM20 		6
#define TCCR2_FOC2			7

/*	Timer/Counter 1 Count	Reg						*/

#define TCNT2	*((volatile u8*)0x44)

/*	Timer/Counter 2 Output Compare Reg				*/

#define OCR2 	*((volatile u8*)0x43)

#endif /* MCAL_TIMER_TIMER_REG_H_ */
