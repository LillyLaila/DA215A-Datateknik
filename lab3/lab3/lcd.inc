/*
 * lcd.inc
 * This file contains subroutines for communicating with a Hitachi HD44780
 * LCD controller (or compatible circuit).
 * These subroutines are created for the course Datateknik DA215A at
 * Malmo University.

 *  Created: 2022-11-29 13:11:25
 *  Laboranter : Alice Jeverdeanu, Laila Suleiman
 *	Datum = 2022-11-29
 *
 * Author:	Mathias Beckius
 *
 * Date:	2014-11-24
 */

 ;==============================================================================
 ; Defines of ports and pins used by the LCD
 ;==============================================================================
	.EQU E_PORT		= PORTD		; port for Enable pin
	.EQU E			= 7			; Enable pin, bit 7
	.EQU RS_PORT	= PORTD		; port for RS pin
 	.EQU RS			= 6			; RS pin, bit 6
	.EQU D_PORT		= PORTF		; port for data/instructions 

//-------------------------------------------------------------
//SKRIVA UT TEXT (KONSTANT DATA)
Str_1: .DB "Welcome!,0"
	.EQU Sz_str1 = 8			; Size of ”str_1”
	
Hello_str: .DB "Welcome to dice",0

Rolling_str: .DB "Rolling...",0,0

Press2_str: .DB "Press 2 to roll",0

Value_str: .DB "Value: ",0

Showstat_str: .DB "Show stat: ",0

Monitor_str: .DB "Monitor: ",0

Clearstat_str: .DB "Clearing..",0,0


//-------------------------------------------------------------
//GÅR IGENOM KONSTANT DATA MAN LAGRAT O GÅR IGENOM STRÄNGAR EN I TAGET
/*Nxt1: 
	LPM R24, Z+
	RCALL lcd_write_chr
	INC R16
	CPI R16, sz_str1
	BRLT Nxt1
	RET*/

Nxt2:
	LPM R24, Z+   //pekar på en Z och incrementerar
	CPI R24, 0 //jämför och ser om registern är 0 
	BREQ Nxt2_End //om det är 0 så return.
	RCALL lcd_write_chr //annars kalla på lcd
	RJMP Nxt2

Nxt2_End:	RET


	

//------------------------------------------
//ANROPA MACRO FÖR ATT ANVÄNDA REGISTORERNA HÄR 
	.MACRO LCD_WRITE_CHAR
	LDI R24, @0
	RCALL lcd_write_chr
	.ENDMACRO

	.MACRO LCD_WRITE_REG_CHAR
	MOV R24, @0
	RCALL lcd_write_chr
	.ENDMACRO

	.MACRO LCD_INSTRUCTION
	LDI R24, @0
	RCALL lcd_write_instr
	.ENDMACRO

	.MACRO PRINTSTRING
	LDI ZH, high(@0<<1)
	LDI ZL, low(@0<<1)
	RCALL Nxt2
	.ENDMACRO




;==============================================================================
; Write the most significant nibble (of the content in R24) to the LCD.
;==============================================================================
lcd_write_nibble:
	OUT	D_PORT, R24			; write data
	SBI	E_PORT, E			; set Enable pin for...
	RCALL delay_1_micros	; ...1 µs!
	CBI	E_PORT, E			; clear Enable pin
	RET

;==============================================================================
; Write to the Instruction Register.
; Instruction is stored in R24.
; A minimum of 39 µs delay must be generated after each instruction!
;==============================================================================
lcd_write_instr:
	CBI	RS_PORT, RS			; select Instruction Register
	RCALL lcd_write_nibble	; write MSB's
	SWAP R24
	RCALL lcd_write_nibble	; write LSB's
	LDI R24, 45
	RCALL delay_micros
	RET

;==============================================================================
; Write a character to the Data Register.
; Character is stored in R24.
; After the character has been written, a delay of 43 µs is generated! 
;==============================================================================
lcd_write_chr:
	SBI RS_PORT, RS			; select Data Register
	RCALL lcd_write_nibble	; write MSB's
	SWAP R24
	RCALL lcd_write_nibble	; write LSB's
	LDI R24, 45
	RCALL delay_micros
	RET

;==============================================================================
; Initialize the LCD.
;==============================================================================
lcd_init:		
	LDI	R24, 20				; wait more than 15 ms after power-up!
	RCALL delay_ms
	CBI	RS_PORT, RS			; select Instruction Register
	LDI	R24, 0x30			; Function Set: 8 bit data interface
	RCALL lcd_write_nibble
	LDI	R24, 10				; wait 10 ms
	RCALL delay_ms
	LDI	R24, 0x30			; Function Set: 8 bit data interface
	RCALL lcd_write_nibble
	LDI	R24, 10				; wait 10 ms
	RCALL delay_ms
	LDI	R24, 0x30			; Function Set: 8 bit data interface
	RCALL lcd_write_nibble
	LDI	R24, 10				; wait 10 ms
	RCALL delay_ms

	LDI	R24, 0x20			; Function Set: switch to 4 bit data interface
	RCALL lcd_write_nibble
	LDI R24, 45				; must be followed by a minimum
	RCALL delay_micros		; delay of 39 µs

	LDI	R24, 0x28			; Function Set: 4 bit data interface, 2 lines,
	RCALL lcd_write_instr	;				Font 5x10

	LDI	R24, 0x0E			; Display on, Cursor On, Blinking Cursor (((markör av)
	RCALL lcd_write_instr

	LDI	R24, 0x01			; Clear Display
	RCALL lcd_write_instr
	LDI	R24, 2				; must be followed by a minimum
	RCALL delay_ms			; delay of 1.53 ms

	LDI R24, 0x06			; Entry Mode Set: incremental cursor movement,
	RCALL lcd_write_instr	;				  no display shift
	RET



lcd_clear_display:
	LCD_INSTRUCTION 0x01
	//
	LDI R24, 25
	RCALL delay_ms
	RET