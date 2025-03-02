/*
 * motor.c
 * Laboranter: Laila Suleiman och Alice Jeverdenau
 * Datum: 2022-12-20
 *
 * Created: 2022-12-20 13:43:29
 *  Author: ASUS
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "motor.h"
	
/*
 * initiering
 *
 */ 

void motor_init(void) {
	// set PC6 (digital pin 5) as output
	DDRC |= 0xFF; //???
	// Set OC3A (PC6) to be cleared on Compare Match (Channel A)
	TCCR3A |= (1<<COM3A1);
	// Waveform Generation Mode 5, Fast PWM (8-bit)
	TCCR3A |= (1<<WGM30);
	TCCR3B |= (1<<WGM32);
	// Timer Clock, 16/64 MHz = 1/4 MHz
	TCCR3B |= (1<<CS31) | (1<<CS30);
}

void motor_set_speed(uint8_t speed) {	OCR3AH = 0; //NOT USED	OCR3AL = (speed * 255) /100; // SET PWM VALUE}