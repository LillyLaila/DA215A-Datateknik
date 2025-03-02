;
; lab3.asm
;
; Created: 2022-11-29 13:06:22
; Author : ASUS
;  Created: 2022-11-29 13:11:25
 ;   Author: Alice Jeverdeanu, Laila Suleiman
 ; Datum = 2022-11-29
;

/*
 * keyboard.inc
 * tangentbords delarna. 
 *
 *  Created: 2022-11-29 13:11:25
 *   Laboranter : Alice Jeverdeanu, Laila Suleiman
 *	Datum = 2022-11-29
 */ 
 
;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000 
	.EQU PM_START	= 0x0056
	.DEF TEMP = R16
	.EQU CONVERT = 0x30
	.DEF RVAL = R24
	.DEF LVAL = R17
	.EQU NO_KEY = 0X0F
	.EQU ROLL_KEY = '2'
	.EQU endofDice = 0x01

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG RESET
	RJMP init

	.ORG PM_START
	.include "lcd.inc"
	.include "delay.inc"
	.include "keyboard.inc"
	.include "Tarning.inc"
	.include "stats.inc"
	.include "monitor.inc"
	.include "stat_data.inc"

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
	CALL lcd_init
	RCALL clear_stat
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
	
	LDI TEMP, 0XFF 
	OUT DDRD, TEMP //UTGÅNG
	CBI PORTE,6 //INGÅNG

	RET

//-----------------------------------------------------
/*write_welcome:

LDI ZH, high(Str_1<<1)
LDI ZL, low(Str_1<<1)
CLR R16
Nxt1: LPM R24, Z+
 RCALL lcd_write_chr
INC R16
CPI R16, sz_str1
BRLT Nxt1
RET
*/

;==============================================================================
; Main part of program
;==============================================================================
main:
	//RCALL write_welcome
	
	PRINTSTRING Hello_str  // printar ut welcome to dice 
	RCALL delay_1_s
	RCALL lcd_clear_display
	RCALL delay_1_s

	PRINTSTRING Press2_str  //printar ut "press 2 to roll"

	
	RCALL loopDice




	




