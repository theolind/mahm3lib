/**
 * \class PWM
 * \brief Pulse Width Modulation (PWM)
 * \details This class is used to output a pulse width modulated waveform using
 * \details the PWM peripheral on the MCU.
 * \author Saeed Ghasemi
 * \version 0.1
 * \date 25 sep 2014
 * \pre
 * \bug
 */


#include "global_entities.h"
#include "pwm.h"

///\cond
// The first register in the Power Management Controller
uint32_t *const p_pwm_base_add = (uint32_t *) 0x40094000U;
/*
 *  Necessary registers addressed by incrementing the base address by an
 *  register-specific offset.
 */
#define PWM_CLK 	*(p_pwm_base_add + 0x000) // PWM Clock Register
#define PWM_ENA 	*(p_pwm_base_add + 0x004) // PWM Enable Register
#define PWM_DIS 	*(p_pwm_base_add + 0x008) // PWM Disable Register
#define PWM_SR 		*(p_pwm_base_add + 0x00C) // PWM Status Register
#define PWM_CMR 	*(p_pwm_base_add + 0x200) // PWM Channel Mode Register
#define PWM_CDTY 	*(p_pwm_base_add + 0x204) // PWM Channel Duty Cycle Register
#define PWM_CDTYUPD *(p_pwm_base_add + 0x208) // PWM Channel Duty Cycle Update Register
#define PWM_CPRD 	*(p_pwm_base_add + 0x20C) // PWM Channel Period Register
#define PWM_CPRDUPD *(p_pwm_base_add + 0x210) // PWM Channel Period Update Register


///\endcond

