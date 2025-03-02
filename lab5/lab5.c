/*
 * main.c
 * Laboranter : Laila Suleiman och Alice Jeverdeanu
 * Datum : 2022-12-13
 *
 * Created: 12/13/2022 1:29:05 PM
 *  Author: ASUS
 */ 

#include "hmi/hmi.h"
#include "numkey/numkey.h"
#include "temp/temp.h"
#include "delay/delay.h"
#include "lcd/lcd.h"
#include <stdio.h>

/*
 * Enums - lagrar olika variabler
 *
 */ 

 typedef enum{
	SHOW_TEMP_C,
	SHOW_TEMP_F,
	SHOW_TEMP_CF
	} state_t;
	
	state_t current_state = SHOW_TEMP_C;
	state_t next_state;
	
	
/*
 * main-programmet - tillståndsmaskin. Tre tillstånd finns med.
 *
 */ 
	

int main()
{	
	hmi_init();
	temp_init();
	char key;
	char temp_str[17];
	char str[] = "TEMPERATURE:";
	
    while(1)
    {
	
		key = numkey_read();
		if(current_state == SHOW_TEMP_C){
			if(key == '1'||key == NO_KEY){
				next_state = SHOW_TEMP_C;
			}
			if(key == '2') {
				next_state = SHOW_TEMP_F;
			}
			if(key == '3') {
				next_state = SHOW_TEMP_CF;
			}
		}
		else if(current_state == SHOW_TEMP_F) {
			if(key == '2' || key == NO_KEY) {
				next_state = SHOW_TEMP_F;
			}
			if(key == '3') {
				next_state = SHOW_TEMP_CF;
			}
			if(key == '1') {
				next_state = SHOW_TEMP_C;
			}
		}
		else if(current_state == SHOW_TEMP_CF) {
			if(key == '3' || key == NO_KEY) {
				next_state = SHOW_TEMP_CF;
			}
			if(key == '1') {
				next_state = SHOW_TEMP_C;
			}
			if(key == '2') {
				next_state = SHOW_TEMP_F;
			}
			
		}
	
	
		switch(current_state){
			case SHOW_TEMP_C:
			sprintf(temp_str, "%u%cC", temp_read_celsius(), 0xDF);
			output_msg(str, temp_str,0);
			break;
			
			case SHOW_TEMP_F:
			sprintf(temp_str, "%u%cF", temp_read_fahrenheit(), 0xDF);
			output_msg(str, temp_str,0);
			break;
			
			case SHOW_TEMP_CF:
			sprintf(temp_str, "%u%cC, %u%cF", temp_read_celsius(), 0xDF, temp_read_fahrenheit(), 0xDF);
			output_msg(str, temp_str,0);
			break;
		}
		
		current_state = next_state;
	}
	
	
	
}