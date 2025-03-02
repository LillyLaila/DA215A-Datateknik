;
; lab2.asm
;
; Created: 2022-11-22 15:55:55
; Author : ASUS
;


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

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG RESET
	RJMP init

	.ORG PM_START
	.include "lcd.inc"
	.include "delay.inc"

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
	; Jump to main part of program
	RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:	
	LDI TEMP, 0xFF
	OUT DDRB, TEMP //PORTEN UTG�NG
	//CBI DDRE,6  //CLERA PORT E6 TILL 0 (ING�NG) TILLF�LLIGT (ANV�NDS EN G�NG)
	OUT DDRF, TEMP //�LYSDIOD UTG�NG
	LDI TEMP, 0x00
	OUT DDRE, TEMP
	
	LDI TEMP, 0XFF 
	OUT DDRD, TEMP //UTG�NG
	CBI PORTE,6 //ING�NG

	RET



	;==============================================================================
; Main part of program
;==============================================================================
main:
	LDI R24, 0x80
	RCALL lcd_write_instr
	LCD_WRITE_CHAR 'K'
	LCD_WRITE_CHAR 'E'
	LCD_WRITE_CHAR 'Y'
	LCD_INSTRUCTION 0xC0 //LAGRAS I DATAREGISTER KOLUMN ANDRA RADEN.. 
key_release:
	LDI LVAL, NO_KEY  //SISTA V�RDET BLIR NOKEY
LOOP: 
	RCALL read_keyboard
	CPI RVAL, NO_KEY //J�MF�R TV� REGISTER. EN REGISTER MED NO_KEY MED V�RDET 0X0F
	BREQ key_release //HOPPA TILL KEYRELEASE OM DE �R LIKA ANNARS FORTS�TT
	CP LVAL, RVAL
	BREQ LOOP
	MOV LVAL, RVAL 
	CPI RVAL, 10
	BRLO write
	LDI TEMP, 7
	ADD RVAL, TEMP
write: 
	LDI TEMP, CONVERT //KONVERTERAR TANGETBORD KNAPP TILL BIN�R TAL
	ADD RVAL, TEMP
	LCD_WRITE_REG_CHAR RVAL
	RCALL delay_ms
	RJMP LOOP

//subrutine---------------------------------

read_keyboard: 
	LDI R18, 0		; reset counter  //L�SER AV TANGENTEN
scan_key: //SCANNA VILKEN KNAPP DU TRYCKER P� TANGENTEN
	MOV R19, R18  
	LSL R19
	LSL R19
	LSL R19
	LSL R19

	OUT PORTB, R19		; set column and row //PUSHAR OCH PULLAR I STACK (OM DIN DISPLAY �R FULL S� PUSHAR MAN O PULLAR MAN FR�N STACKEN S� MAN F�R PLATS)
	PUSH R18
	LDI R24, 10
	RCALL delay_ms
	POP R18


	SBIC PINE, 6
	RJMP return_key_val
	INC R18
	CPI R18, 12
	BRNE scan_key
	LDI R18, NO_KEY		; no key was pressed! //IFALL INGEN KNAPP TRYCKS S� HAR MAN DETTA F�R ATT UNDVIKA ATT SIFFROR SKRIVS AV SIG SJ�LV. 

return_key_val:
	MOV RVAL, R18
	RET




	