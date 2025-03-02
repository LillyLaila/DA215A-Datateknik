/*
 * keyboard.inc
 * tangentbords delarna. 
 *
 *  Created: 2022-11-29 13:11:25
 *   Laboranter : Alice Jeverdeanu, Laila Suleiman
 *	Datum = 2022-11-29
 */ 
 
;==============================================================================
; MAP tabell
;==============================================================================

 map_table: 
	.DB "147*2580369#"

;==============================================================================
; Subrutine
;==============================================================================
read_keyboard: 
	RCALL read_keyboard_num
to_ASCII:
	LDI ZH, high(map_table <<1)  ;Initialize Z pointer
	LDI ZL, low(map_table <<1)
	ADD ZL, RVAL  ;Add index
	LDI RVAL, 0x00
	ADC ZH, RVAL  ;Add 0 to catch Carry, if present
	LPM RVAL, Z
	RET

read_keyboard_num:
	LDI R18, 0		; reset counter  //LÄSER AV TANGENTEN


scan_key: //SCANNA VILKEN KNAPP DU TRYCKER PÅ TANGENTEN
	MOV R19, R18  
	LSL R19
	LSL R19
	LSL R19
	LSL R19

	OUT PORTB, R19		; set column and row //PUSHAR OCH PULLAR I STACK (OM DIN DISPLAY ÄR FULL SÅ PUSHAR MAN O PULLAR MAN FRÅN STACKEN SÅ MAN FÅR PLATS)
	PUSH R18
	LDI R24, 5
	RCALL delay_ms
	POP R18


	SBIC PINE, 6
	RJMP return_key_val
	INC R18
	CPI R18, 12
	BRNE scan_key
	LDI R18, NO_KEY		; no key was pressed! //IFALL INGEN KNAPP TRYCKS SÅ HAR MAN DETTA FÖR ATT UNDVIKA ATT SIFFROR SKRIVS AV SIG SJÄLV. 

return_key_val:
	MOV RVAL, R18
	RET



