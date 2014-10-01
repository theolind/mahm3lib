/*
 * test_delay.h
 *
 *  Created on: 1 October 2014
 *      Author: Mattias Nilsson
 */

/*
 * How to use: Include test/test_delay.h file in main.c and include either
 * function to test  * delay function. test_l_led will blink the L-LED.
 * test_pin_46 will turn pin 46 on and off and the delay can be read out by an
 * oscilloscope.
 * Both tests input parameter is in microseconds.
 */

#ifndef TEST_TEST_DELAY_H_
#define TEST_TEST_DELAY_H_

#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"

void test_delay_l_led(uint32_t delay);
void test_delay_pin_46(uint32_t delay);



#endif /* TEST_TEST_DELAY_H_ */
