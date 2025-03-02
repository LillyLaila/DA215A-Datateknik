/*
 * main.c
 * Laboranter : Laila Suleiman och Alice Jeverdeanu
 * Datum : 2022-12-20
 *
 * Created: 12/13/2022 1:29:05 PM
 *  Author: ASUS
 */ 

#include "hmi/hmi.h"
#include "numkey/numkey.h"
#include "regulator/regulator.h"
#include "delay/delay.h"
#include "lcd/lcd.h"
#include <stdio.h>
#include "motor/motor.h"

/*
 * Enums - lagrar olika variabler
 *
 */ 

 typedef enum{
	MOTOR_OFF,
	MOTOR_ON,
	MOTOR_RUNNING
	} state_t;
	
	state_t current_state = MOTOR_OFF;
	state_t next_state;
	
	
/*
 * main-programmet - tillståndsmaskin. Tre tillstånd finns med.
 *
 */ 
	

int main()
{	
	hmi_init();
	regulator_init();
	motor_init();
	char key;
	char regulator_str[17];
	char textoff[] = "Motor OFF";
	char texton[] = "Motor ON";
	char textrunning[] = "Motor RUNNING";


	
    while(1)
    {
		key = numkey_read();
	
		switch(current_state){
			
		case MOTOR_OFF:
			if((key == '2') && (regulator_read_power() == 0)) {
				next_state = MOTOR_ON;
			}
			sprintf(regulator_str, "%u%%", regulator_read_power());
			output_msg(textoff, regulator_str,0);
			motor_set_speed(0);
			break;
			
		case MOTOR_ON:
			if (key == '1')
			{
				next_state= MOTOR_OFF;
			}
			else if (regulator_read_power() > 0) 
			{ 
				next_state = MOTOR_RUNNING;
			}
			sprintf(regulator_str, "%u%%", regulator_read_power());
			output_msg(texton, regulator_str,0);
			break;
			
		case MOTOR_RUNNING:
			if (key == '1')
			{
				next_state = MOTOR_OFF;
			}
			sprintf(regulator_str, "%u%%", regulator_read_power());
			output_msg(textrunning, regulator_str,0);
			motor_set_speed(regulator_read_power());
			break;
		}
		current_state = next_state;	
	}
}