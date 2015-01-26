/**
 * @file delay.h
 * @brief Delay - Software delay
 * @details The delays are not accurate enough for real time applications,
 * however the delays are accurate enough for most applications.
 *
 * The longer the delay, the more accurate. Below 10 us, the deviation
 * fluctuates from +2us to -2us. The shortest delay that is 2 us.
 *
 * @pre Initialize the board
 *
 * @author Mattias Nilsson
 * @date 21 October 2014
 *
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <inttypes.h>
extern void wait(void);

/**
 * The function makes a pause in the system.
 * @param us The length of the pause in microseconds. Range from 1 microsecond
 * to several seconds
 */
void delay_micros(uint32_t us);

/**
 * The function makes a pause in the system.
 * @param ms The length of the pause in milliseconds. Range from 1 millisecond
 * to several seconds
 */
void delay_ms(uint32_t ms);

#endif
