/*
 * Tarning.inc
 *
 *  Created: 2022-11-29 16:24:00
 *   Author: ASUS
 */ 

;==============================================================================
;  H�R KASTAR MAN T�RNINGEN.  N�R DEN G�R NER TILL 1 S� LOOPAR DEN OCH RESTARTAR V�RDET TILL 6 
;==============================================================================

roll_dice:
	LDI R16, 6 //T�RNING HAR 6 V�RDEN 
test: 
	NOP
	NOP
	RCALL read_keyboard
	CPI RVAL, ROLL_KEY //KEYVALUE I RVAL
	BREQ roll
	RCALL store_stat
	RET
roll: 
	DEC R16
	BREQ roll_dice
	RJMP test
	
	

rollagain: 
	RCALL lcd_clear_display
	PRINTSTRING Press2_str  //printar ut "press 2 to roll"

;==============================================================================
; /H�R LOOPAR VI IGENOM. DET V�RDET MAN TRYCKER NER P� TANGENT. OMM MAN TRYCKER P� T.EX 3 S� HOPPAR MAN TILL METODEN HANDLE_3
;==============================================================================
	
loopDice:
	RCALL read_keyboard
	CPI RVAL, ROLL_KEY  // ROLLKEY HAR V�RDET 2
	BREQ handle_2
	CPI RVAL, '3'
	BREQ handle_3
	CPI RVAL, '8'
	BREQ handle_8
	CPI RVAL, '9'
	BREQ handle_9
	RJMP loopDice

;==============================================================================
; Tangent 2 
;==============================================================================

handle_2:
	
	RCALL lcd_clear_display
	LDI R24, 70
	RCALL delay_ms

	PRINTSTRING Rolling_str
	
	LDI R24, 70
	RCALL delay_ms

	RCALL roll_dice
	RCALL lcd_clear_display
		
	LDI R24, 70
	RCALL delay_ms
	MOV RVAL, TEMP
	LDI TEMP, CONVERT //KONVERTERAR TANGETBORD KNAPP TILL BIN�R TAL
	ADD RVAL, TEMP
	PUSH RVAL
	PRINTSTRING Value_str
	POP RVAL
	LCD_WRITE_REG_CHAR RVAL
	RCALL delay_1_s
	RJMP rollagain

;==============================================================================
; Tangent 3
;==============================================================================
handle_3:
	RCALL showstat
	RCALL delay_1_s
	RJMP rollagain

;==============================================================================
; Tangent 8
;==============================================================================
handle_8:
	RCALL clearstat
	RCALL delay_1_s
	RJMP rollagain

;==============================================================================
; Tangent 9
;==============================================================================
handle_9:
	//PRINTSTRING Monitor_str
	RCALL monitor
	RCALL delay_1_s
	RJMP rollagain
