/**
 * @file due_pwm.h
 * @brief Pulse Width Modulation on Arduino Due
 * @details This API is used to use the different PWM options available on
 * the Arduino Due board, which consists of both hardware and software based PWM.
 * @pre Initiate board.
 *
 * @author Andreas Drotth
 * @author Mattias Nilsson
 * @date 29 October 2014
 */

#ifndef DUW_PWM_H_
#define DUE_PWM_H_

#include <pwm.h>
#include <tc.h>

// http://www.robgray.com/temp/Due-pinout-WEB.png
// http://arduino.cc/en/Hacking/PinMappingSAM3X

///@{
// Software based PWM pins
//#define DUE_PWM_CHANNEL_2
//#define DUE_PWM_CHANNEL_3
//#define DUE_PWM_CHANNEL_4
//#define DUE_PWM_CHANNEL_5
//#define DUE_PWM_CHANNEL_10
//#define DUE_PWM_CHANNEL_11
//#define DUE_PWM_CHANNEL_12
//#define DUE_PWM_CHANNEL_13
//
//// Hardware based PWM pins
//#define DUE_PWM_CHANNEL_6	PC24	PWML7
//#define DUE_PWM_CHANNEL_7	PC23	PMWL6
//#define DUE_PWM_CHANNEL_8	PC22	PWML5
//#define DUE_PWM_CHANNEL_9	PC21	PWML4
///@}

#endif
