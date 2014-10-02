/**
 * @file
 * @brief Arduino Due pin mapping
 * @details This file is used for pins on the Arduino boards
 * @author Hisham Ramish
 * @author Stefan Angelov
 * @version 0.1
 * @date 29 sep 2014

 */


#ifndef ARDUINO_DUE_PIN_MAPPING_H_
#define ARDUINO_DUE_PIN_MAPPING_H_

#include <inttypes.h>

/**
 * ADC mappings
 */
#define A0_pin		7
#define A1_pin		6
#define A2_pin		5
#define A3_pin		4
#define A4_pin		3
#define A5_pin		2
#define A6_pin		1
#define A7_pin		0
#define A8_pin		10
#define A9_pin		11
#define A10_pin		12
#define A11_pin		13

/**
 * DACC mappings
 */
#define DAC0_pin	0
#define DAC1_pin	1

/**
 * PIO mappings
 */

#define PIOA ((pio_reg_t *) 0x400E0E00)
#define PIOB ((pio_reg_t *) 0x400E1000)
#define PIOC ((pio_reg_t *) 0x400E1200)
#define PIOD ((pio_reg_t *) 0x400E1400)
#define PIOE ((pio_reg_t *) 0x400E1600)
#define PIOF ((pio_reg_t *) 0x400E1800)

#define D2_pin		25
#define D3_pin		28
#define D4_pin		26
#define D5_pin		25
#define D6_pin		24
#define D7_pin		23
#define D8_pin		22
#define D9_pin		21
#define D10_pin		29
#define D11_pin		7
#define D12_pin		8
#define D22_pin		26
#define D23_pin		14
#define D24_pin		15
#define D25_pin		0
#define D26_pin		1
#define D27_pin		2
#define D28_pin		3
#define D29_pin		6
#define D30_pin		9
#define D31_pin		7
#define D32_pin		10
#define D33_pin		1
#define D34_pin		2
#define D35_pin		3
#define D36_pin		4
#define D37_pin		5
#define D38_pin		6
#define D39_pin		7
#define D40_pin		8
#define D41_pin		9
#define D42_pin		19
#define D43_pin		20
#define D44_pin		19
#define D45_pin		18
#define D46_pin		17
#define D47_pin		16
#define D48_pin		15
#define D49_pin		14
#define D50_pin		13
#define D51_pin		12
#define D52_pin		21
#define D53_pin		14

#define D2_port		PIOB
#define D3_port		PIOC
#define D4_port		PIOC
#define D5_port		PIOC
#define D6_port		PIOC
#define D7_port		PIOC
#define D8_port		PIOC
#define D9_port		PIOC
#define D10_port	PIOC
#define D11_port	PIOD
#define D12_port	PIOD
#define D22_port	PIOB
#define D23_port	PIOA
#define D24_port	PIOA
#define D25_port	PIOD
#define D26_port	PIOD
#define D27_port	PIOD
#define D28_port	PIOD
#define D29_port	PIOD
#define D30_port	PIOD
#define D31_port	PIOA
#define D32_port	PIOD
#define D33_port	PIOC
#define D34_port	PIOC
#define D35_port	PIOC
#define D36_port	PIOC
#define D37_port	PIOC
#define D38_port	PIOC
#define D39_port	PIOC
#define D40_port	PIOC
#define D41_port	PIOC
#define D42_port	PIOA
#define D43_port	PIOA
#define D44_port	PIOC
#define D45_port	PIOC
#define D46_port	PIOC
#define D47_port	PIOC
#define D48_port	PIOC
#define D49_port	PIOC
#define D50_port	PIOC
#define D51_port	PIOC
#define D52_port	PIOB
#define D53_port	PIOB



#endif /* ARDUINO_DUE_PIN_MAPPING_H_ */
