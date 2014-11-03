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

#include "sam3x8e/pwm.h"
#include "sam3x8e/tc.h"
#include "sam3x8e/pio.h"

// http://www.robgray.com/temp/Due-pinout-WEB.png
// http://arduino.cc/en/Hacking/PinMappingSAM3X

/////@{
//// Software based PWM pins
//#define DUE_PWM_CHANNEL_2	(2)
//#define DUE_PWM_CHANNEL_3	(3)
//#define DUE_PWM_CHANNEL_4	(4)
//#define DUE_PWM_CHANNEL_5	(5)
//#define DUE_PWM_CHANNEL_10	(10)
//#define DUE_PWM_CHANNEL_11	(11)
//#define DUE_PWM_CHANNEL_12	(12)
//#define DUE_PWM_CHANNEL_13	(13)
//
//// Hardware based PWM pins
//#define DUE_PWM_CHANNEL_6	(6)	//PC24	PWML7
//#define DUE_PWM_CHANNEL_7	(7)	//PC23	PMWL6
//#define DUE_PWM_CHANNEL_8	(8)	//PC22	PWML5
//#define DUE_PWM_CHANNEL_9	(9)	//PC21	PWML4
/////@}

void due_pwm_init_channel(uint32_t channel);
void due_pwm_set_duty_cycle(uint32_t channel, uint32_t duty);
void due_pwm_enable_channel(uint32_t channel);
void due_pwm_disable_channel(uint32_t channel);

#endif
