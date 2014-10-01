/*
 * Test runner.
 *
 * Author:	Theodor Lindquist
 * 			Mathias Beckius
 *
 * Date: 	29 September 2014
 */

#ifndef TEST_RUNNER_H_
#define TEST_RUNNER_H_

#include "sam3x8e/uart.h"

#define HORIZONTAL_LINE_BREAK()	\
	uart_write_str("-----------------------\n");

void run_tests(void);

#endif
