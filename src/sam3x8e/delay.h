/**
 * @file delay.h
 * @brief Delay - Software delay API
 * @details The API contains two functions for delaying. One for microseconds
 * and one for milliseconds.
 * This library introduces a software implementation of two delay functions
 * that do not rely on any hardware peripheral or internal clocks to
 * operate. The solution implements a loop written in C code and it only
 * needs the processor clock speed to be exactly 84MHz such as the one
 * running the ARM Cortex-M3 MCU that this API is developed for. There are
 * two functions included in the API. There is one for microseconds and
 * one for milliseconds as shown below. Both functions must be invoked
 * with integers or float without any fractional part.
 *
 * @pre Initialize the board
 *
 * Word of caution: There are disadvantages and shortcomings to a software
 * delay. Such delay use CPU-time and make the code inefficient, at the
 * same time interrupts will interfere with the length of the delay and
 * their use should therefore be avoided in timing critical applications.
 * This is however not entirely avoided using hardware timers either.
 *
 * @author Saeed Ghasemi
 * @author Andreas Drotth
 * @date 28 September 2014
 *
 */


#ifndef DELAY_H_
#define DELAY_H_

#include <inttypes.h>

/**
 * This function will delay in microseconds.
 * This function is tested to perform fairly accurate within 15 to 20000 us.
 * It can be used perfectly down to 15 us. Below this value there
 * may be fluctuation around the specified value. The maximum fluctuation is
 * close to 1.5us. The lowest delay achievable is 2.6 us with inputs in the
 * range 0-3.
 *
 * @param us Amount of time in us to delay
 */
void delay_us(float us);

/**
 * This function will delay in milliseconds.
 * The function is tested to perform fairly accurate within 1 to 100 ms with an
 * accuracy of maximum 300 us in this range which yields 0.3% deviation at
 * 100ms delay.
 *
 * @param ms Amount of time in ms to delay
 */
void delay_ms(uint32_t ms);

#endif
