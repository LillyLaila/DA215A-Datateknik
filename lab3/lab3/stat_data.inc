/* sparar resultaten från värdet från tärningen i RAM
 * stat_data.inc
 *
 *  Created: 2022-12-01 11:05:53
 *   Author: ASUS
 */ 

 ;==============================================================================
; Olika stats 
;==============================================================================

			.DSEG 
			.ORG 0x100
 total_stat: 
			.BYTE 7  // 7 eftersom vi ska lagra 7 värden. alla 1or alla 2or alla 3or osv
			.CSEG
store_stat: 
			LDI XL, low(total_stat) 
			LDI XH, high(total_stat)
			LD R17,X //LADDA DET SOM FINNS I X LOCATION  OCH LAGRA I R17
			INC R17 
			ST X, R17 //ÖKA ANTALET TÄRNINGSKAST O SPARA TILL MINNET

			ADD XL, R16
			LDI R24, 0
			ADC XH, R24
			LD R17, X  //LADDA DET SOM FINNS I X LOCATION I R17
			INC R17
			ST X, R17


			RET
get_stat:
        LDI XH, HIGH(total_stat)
        LDI XL, LOW(total_stat)
        ADD XL, RVAL
        LDI RVAL, 0
        ADC XH, RVAL
        LD RVAL, X
        RET 

clear_stat:
	LDI R16, 0x00
	STS total_stat, R16
	STS total_stat+1, R16 
	STS total_stat+2, R16 
	STS total_stat+3, R16 
	STS total_stat+4, R16 
	STS total_stat+5, R16 
	STS total_stat+6, R16 
	RET

/*


        LDI XH, HIGH(total_stat)
        LDI XL, LOW(total_stat)
        ADD XL, RVAL
        LDI RVAL, 0
        ADC XH, RVAL
        LD RVAL, X
        RET 
		*/




