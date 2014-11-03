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

//#define PWM2
//#define PWM3
//#define PWM4
//#define PWM5
#define PWM6		(7)
#define PWM7		(6)
#define PWM8		(5)
#define PWM9		(4)
//#define PWM10
//#define PWM11
//#define PWM12
//#define PWM13

void due_pwm_init_channel(uint32_t channel);
void due_pwm_set_duty_cycle(uint32_t channel, uint32_t duty);
void due_pwm_enable_channel(uint32_t channel);
void due_pwm_disable_channel(uint32_t channel);

#endif
