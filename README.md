# AVR_COTS
This approach is a way of many ways to implement the concept of "Layered Architecture which is discussed in "Reusable Firmware Development" by Jacob Bening.
This is my own way to implement a configurable reusable firmware for AVR controller -ATmega32-. Each Module of this project is a Software Component,
which is stored in the shelf so its called Component on the Shelf -COTS-

## APP Horizontal Layer

Is a layer that contains all needed files that designed for a specific application which is totally independent of the lower layers.
This layer contains the main function -The project's entry point.

## HAL Horizontal Layer

This layer is designed to make all drivers needed for any External Hardware.
This COTS contains Drivers for all basic external Peripherals:

- ED      (Light Emitting Diode)  : Sink Mode, Source Mode.
-	KPD     (Keypad)                : Port Configurable, Pin configurable Order.
-	Relay                           : Basic.
-	DCMOTOR (DC motor)              : Object-Based SW component, 2-pin controlled DC motor.
-	SERVO   (Servo motor)           : Basic.
-	SSD     (seven segments display): Object-Based SW component, Decimal mode, Hex mode, Controlled Common pin.
- SWITCH  (electrical switches and Buttons) : Object-Based SW component, Full configurable Port and Pin, Pull Up/Down feature.
-	CLCD    (Character LCD)                   : Supports 8-lines and 4-lines, External Character Generator, single control port, single data port, full configurable data lines in data port.
-	to be continued...

## MCAL Horizontal Layer

This layer is designed to implement all drivers needed for Internal Hardware features in the Microcontroller.
It is configurable for almost all AVRs -ATmega- This repository holds the most common internal drivers for ATmega32 Peripherals:

-	DIO     : Digital Input Output.
-	ADC     : Analog-Digital Converter, Support Post-Build and Pre-Build Configuration.
-	EXTI    : External Interrupts, Support Post-Build and Pre-Build Configuration..
-	GIE     : Global Interrupt -for isolation-
-	PORT    : Port driver to initiate all pins direction and initial values.
-	TIMER   : Timer Driver support modes Interval, CTC with or without a hardware action for Timers 0,1,2.
-	PWM     : Pulse Width Modulation driver.
-	ICU     : Input Capture Unit based on Timer1.
-	WDT     : Watch Dog Timer -Time Configurable-
-	UART    : Universal Synchronous Asynchronous Receiver Transmitter -Serial protocol- Full Configured (baud rate, stop bit, parity bit, data width) Support Post-Build and Pre-Build Configuration.
-	To be Continued...


## LIB Vertical Layer

This layer contains all support header files which is used in almost all files in this COTS.

This Layer contains:

-	STD_TYPES.h   : For type definition for all used types to make it easy to tracing the size and sign of the data in variable.
-	BIT_MATH.h    : For bit manipulation operations (Set, Get, Clear, Toggle).
-	Err_Type.h    : For define all possible error states and correct state as a flag used in function return.
-	MATH_FUNC.h   : For most used functions which is converted as Function Macro (MAPPING).
