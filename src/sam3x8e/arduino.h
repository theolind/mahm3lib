/**
 * @file
 * @brief Arduino Due PIN mapPINg
 * @details This file is used for PINs on the Arduino boards
 * @author Hisham Ramish
 * @author Stefan Angelov
 * @version 0.1
 * @date 29 sep 2014

 */


#ifndef ARDUINO_H_
#define ARDUINO_H_

#include <inttypes.h>
#include <pio.h>
#include <adc.h>
#include <dacc.h>

/**
 * ADC mapPINgs
 */
#define A0_PIN		ADC_CHANNEL_7
#define A1_PIN		ADC_CHANNEL_6
#define A2_PIN		ADC_CHANNEL_5
#define A3_PIN		ADC_CHANNEL_4
#define A4_PIN		ADC_CHANNEL_3
#define A5_PIN		ADC_CHANNEL_2
#define A6_PIN		ADC_CHANNEL_1
#define A7_PIN		ADC_CHANNEL_0
#define A8_PIN		ADC_CHANNEL_10
#define A9_PIN		ADC_CHANNEL_11
#define A10_PIN		ADC_CHANNEL_12
#define A11_PIN		ADC_CHANNEL_13

/**
 * DACC mapPINgs
 */
#define DAC0_PIN	DACC_CHANNEL_0
#define DAC1_PIN	DACC_CHANNEL_1

/**
 * PIO mapPINgs
 */

//#define PIOA ((pio_reg_t *) 0x400E0E00)
//#define PIOB ((pio_reg_t *) 0x400E1000)
//#define PIOC ((pio_reg_t *) 0x400E1200)
//#define PIOD ((pio_reg_t *) 0x400E1400)
//#define PIOE ((pio_reg_t *) 0x400E1600)
//#define PIOF ((pio_reg_t *) 0x400E1800)

#define D2_PIN		25
#define D3_PIN		28
#define D4_PIN		26
#define D5_PIN		25
#define D6_PIN		24
#define D7_PIN		23
#define D8_PIN		22
#define D9_PIN		21
#define D10_PIN		29
#define D11_PIN		7
#define D12_PIN		8
#define D22_PIN		26
#define D23_PIN		14
#define D24_PIN		15
#define D25_PIN		0
#define D26_PIN		1
#define D27_PIN		2
#define D28_PIN		3
#define D29_PIN		6
#define D30_PIN		9
#define D31_PIN		7
#define D32_PIN		10
#define D33_PIN		1
#define D34_PIN		2
#define D35_PIN		3
#define D36_PIN		4
#define D37_PIN		5
#define D38_PIN		6
#define D39_PIN		7
#define D40_PIN		8
#define D41_PIN		9
#define D42_PIN		19
#define D43_PIN		20
#define D44_PIN		19
#define D45_PIN		18
#define D46_PIN		17
#define D47_PIN		16
#define D48_PIN		15
#define D49_PIN		14
#define D50_PIN		13
#define D51_PIN		12
#define D52_PIN		21
#define D53_PIN		14

#define D2_PORT		PIOB
#define D3_PORT		PIOC
#define D4_PORT		PIOC
#define D5_PORT		PIOC
#define D6_PORT		PIOC
#define D7_PORT		PIOC
#define D8_PORT		PIOC
#define D9_PORT		PIOC
#define D10_PORT	PIOC
#define D11_PORT	PIOD
#define D12_PORT	PIOD
#define D22_PORT	PIOB
#define D23_PORT	PIOA
#define D24_PORT	PIOA
#define D25_PORT	PIOD
#define D26_PORT	PIOD
#define D27_PORT	PIOD
#define D28_PORT	PIOD
#define D29_PORT	PIOD
#define D30_PORT	PIOD
#define D31_PORT	PIOA
#define D32_PORT	PIOD
#define D33_PORT	PIOC
#define D34_PORT	PIOC
#define D35_PORT	PIOC
#define D36_PORT	PIOC
#define D37_PORT	PIOC
#define D38_PORT	PIOC
#define D39_PORT	PIOC
#define D40_PORT	PIOC
#define D41_PORT	PIOC
#define D42_PORT	PIOA
#define D43_PORT	PIOA
#define D44_PORT	PIOC
#define D45_PORT	PIOC
#define D46_PORT	PIOC
#define D47_PORT	PIOC
#define D48_PORT	PIOC
#define D49_PORT	PIOC
#define D50_PORT	PIOC
#define D51_PORT	PIOC
#define D52_PORT	PIOB
#define D53_PORT	PIOB



#endif
