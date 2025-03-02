/*
 * lab1.asm
 * 
 * This is a very simple demo program made for the course DA215A at
 * Malmö University. The purpose of this program is:
 *	-	To test if a program can be transferred to the ATmega32U4
 *		microcontroller.
 *	-	To provide a base for further programming in "Laboration 1".
 *
 * After a successful transfer of the program, while the program is
 * running, the embedded LED on the Arduino board should be turned on.
 * The LED is connected to the D13 pin (PORTC, bit 7).
 *
 * Programmet gjorde så att man kunde styra LED med tangentbordet. Så om man trycker på kolumn 1 så tänds LED i form av 1 osv.
 *
 * Author:	Laila Suleiman, Alice Jeverdeanu
 *
 * Date:	2022-11-15
 */ 
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000 
	.EQU PM_START	= 0x0056
	.DEF TEMP = R16
	.DEF RVAL = R24
	.EQU NO_KEY = 0X0F

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG RESET
	RJMP init

	.ORG PM_START
;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	; Set stack pointer to point at the end of RAM.
	LDI TEMP, LOW(RAMEND) //
	OUT SPL, TEMP
	LDI TEMP, HIGH(RAMEND)
	OUT SPH, TEMP
	; Initialize pins
	CALL init_pins
	; Jump to main part of program
	RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:	
	

	LDI TEMP, 0xFF
	OUT DDRB, TEMP //PORTEN UTGÅNG
	//CBI DDRE,6  //CLERA PORT E6 TILL 0 (INGÅNG) TILLFÄLLIGT (ANVÄNDS EN GÅNG)
	OUT DDRF, TEMP //´LYSDIOD UTGÅNG
	LDI TEMP, 0x00
	OUT DDRE, TEMP
	
	RET

;==============================================================================
; Main part of program
;==============================================================================
main:	

//IN TEMP, PINB // LÄSA IN PINB TILL TEMP
//MOV RVAL, TEMP //KOPIERA IN TEMP (R16) I RVAL (R24)
CALL read_keyboard //ANROPA READ_KEYBOARD
LSL RVAL
LSL RVAL //SKIFTA R24 TILL VÄNSTER ETT PAR GÅNGER
LSL RVAL
LSL RVAL
OUT PORTF, RVAL //SKRIVA UT RVAL (R24) TILL PORTF
NOP  //TVÅ KLOCKSLAG 
NOP


/*	
	SBI PORTC, 7		; 2 cycles

	NOP					; 1 cycle x 6
	NOP
	NOP
	NOP
	NOP
	NOP
	CBI PORTC, 7		; 2 cycles
	NOP					; 1 cycle x 4
	NOP
	NOP
	NOP
	*/
	RJMP main			; 2 cycles

read_keyboard: 
	LDI R18, 0		; reset counter
scan_key:
	MOV R19, R18
	LSL R19
	LSL R19
	LSL R19
	LSL R19
	OUT PORTB, R19		; set column and row
	NOP ; a minimum of 2 NOP's is necessary!
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	SBIC PINE, 6
	RJMP return_key_val
	INC R18
	CPI R18, 12
	BRNE scan_key
	LDI R18, NO_KEY		; no key was pressed!
return_key_val:
	MOV RVAL, R18
	RET