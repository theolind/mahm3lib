/**
 * @file delay.h
 * @brief Delay - Software delay API
 * @details The API contains two functions for delaying. One for microseconds
 * and one for milliseconds.
 * This library introduces a software implementation of two delay functions
 * that do not rely on any hardware peripheral or internal clocks to
 * operate. The solution implements a loop written in assembly code and it only
 * needs the processor clock speed to be exactly 84MHz such as the one
 * running the ARM Cortex-M3 MCU that this API is developed for. There are
 * two functions included in the API. There is one for microseconds and
 * one for milliseconds as shown below.
 *
 * @pre Initialize the board
 *
 * Word of caution: There are disadvantages and shortcomings to a software
 * delay. Such delay use CPU-time and make the code inefficient, at the
 * same time interrupts will interfere with the length of the delay and
 * their use should therefore be avoided in timing critical applications.
 * This is however not entirely avoided using hardware timers either.
 *
 * @author Mattias Nilsson
 * @date 2 October 2014
 *
 */


#ifndef DELAY_H_
#define DELAY_H_

#include <inttypes.h>

void delay_micros(uint32_t us);
void delay_ms(uint32_t ms);

#endif
