/**
 * @file delay.h
 * @brief Delay - Software delay
 * @details The delays are not accurate enough for real time applications,
 * however the delays are accurate enough for most applications. The
 * largest deviation occures right after 10 microseconds, the
 * deviation are up to +20%.
 *
 * The deviation then gets lower and in the area between 20 - 500
 * microseconds the average deviation are +/- 5%. Below 10 microseconds the
 * deviation are down to 10-50 ns and above 500 microseconds the
 * deviation is between +/- 1-2% off.
 *
 * @pre Initialize the board
 *
 * @author Mattias Nilsson
 * @date 6 October 2014
 *
 */


#ifndef DELAY_H_
#define DELAY_H_

#include <inttypes.h>

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


///@cond

/*
 * Adds a pause for every for every 1000 microseconds.
 */
void delay_1000(uint32_t us_1000);
/*
 * Adds a pause for every for every 100 microseconds.
 */
void delay_100(uint32_t us_100);
/*
 * Adds a pause for every for every 10 microseconds.
 */
void delay_10(uint32_t us_10);
/*
 * Adds a pause for every for every 1 microseconds.
 */
void delay_1(uint32_t us_1);

///@endcond

#endif
