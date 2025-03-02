/*
 * temp.h
 *
 * This is the device driver for the LM35 temperature sensor.
 *
 * Author:	Mathias Beckius
 *
 * Date:	2014-12-07
 */ 

#ifndef REGULATOR_H_
#define REGULATOR_H_

#include <inttypes.h>

void regulator_init(void);
uint8_t regulator_read_power(void);
uint8_t regulator_read_speed(void);
uint8_t temp_read_celsius(void);
uint8_t temp_read_fahrenheit(void);

#endif /* REGULATOR_H_ */