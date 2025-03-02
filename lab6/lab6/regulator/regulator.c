/*
 * temp.c
 * Laboranter : Laila Suleiman och Alice Jeverdenau
 * Datum: 2022-12-20
 * This is the device driver for the LM35 temperature sensor.
 *
 * Author:	Mathias Beckius
 *
 * Date:	2014-12-07
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "regulator.h"

/*	For storage of ADC value from temperature sensor.
	Initial value is good to use before A/D conversion is configured!	*/
static volatile uint8_t adc = 221;

/*
 * Interrupt Service Routine for the ADC.
 * The ISR will execute when a A/D conversion is complete.
 */
ISR(ADC_vect)
{
		adc = ADCH;

}

/*
 * Initialize the ADC and ISR.
 */
void regulator_init(void)
{
	// UPPGIFT: konfigurera ADC-enheten genom ställa in ADMUX och ADCSRA enligt kommentarerna nedanför!
	ADMUX |= (1<<REFS0);		// set reference voltage (internal 5V)
	ADMUX |= (1<<MUX0) | (1<<ADLAR)  ;		// select diff.amp 10x on  ADC1
								// right adjustment of ADC value
	
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);	// prescaler 128
	ADCSRA |= (1<<ADATE);	// enable Auto Trigger
	ADCSRA |= (1<<ADIE);		// enable Interrupt
	ADCSRA |= (1<<ADEN);		// enable ADC

	// disable digital input on  ADC1
	DIDR0 = (1<<ADC1D);
		
	// disable USB controller (to make interrupts possible)
	USBCON = 0;	
	// enable global interrupts
	sei();

	// start initial conversion
	ADCSRA |= (1<<ADSC);	// UPPGIFT: gör så att den initiala A/D-omvandlingen sker
}
	
/*
 * ´Läser motorn
 *
 */ 

uint8_t regulator_read_power(void)
 {
	 
	 return (adc * 100) / 255;	
}


