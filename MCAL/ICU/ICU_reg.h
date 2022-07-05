/*
 * ICU_reg.h
 *
 *  Created on: Oct 11, 2021
 *      Author: 20114
 */


#define ICR1H	*((volatile u8*) 0x47)
#define ICR1L   	*((volatile u8*) 0x46)

#define ICR1   	*((volatile u16*) 0x46)

#define TIMSK	*((volatile u8*)0x59)

#define TIMSK_TICIE1	5

#define TIFR	*((volatile u8*)0x58)

#define TIFR_ICF1       5

#define TCCR1B	*((volatile u8*)0x4E)

#define TCCR1B_ICES1		6
#define TCCR1B_ICNC1		7
