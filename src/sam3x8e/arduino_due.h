/**
 * @file
 * @brief Arduino Due PIN mapping
 * @details This file is used for physical pins on the Arduino Due board
 * @author Hisham Ramish
 * @author Stefan Angelov
 * @version 0.1
 * @date 07 oct 2014

 */


#ifndef ARDUINO_DUE_H_
#define ARDUINO_DUE_H_

#include "adc.h"
#include "dacc.h"
#include "pio.h"

/**
 * ADC mappings
 * Pins A0-A11 on the left side of the Arduino Due board
 */
#define A0			ADC_CHANNEL_7
#define A1			ADC_CHANNEL_6
#define A2			ADC_CHANNEL_5
#define A3			ADC_CHANNEL_4
#define A4			ADC_CHANNEL_3
#define A5			ADC_CHANNEL_2
#define A6			ADC_CHANNEL_1
#define A7			ADC_CHANNEL_0
#define A8			ADC_CHANNEL_10
#define A9			ADC_CHANNEL_11
#define A10			ADC_CHANNEL_12
#define A11			ADC_CHANNEL_13

/**
 * DACC mappings
 * Pins DAC0, DAC1 on the left side of the Arduino board
 */
#define DAC0		DACC_CHANNEL_0
#define DAC1		DACC_CHANNEL_1

/**
 * PIO mappings
 * Pins 2-13 on the right side of the Arduino board
 * Pins 22-53 on the lower part of the Arduino board
 */
#define D2_PORT		PIOB
#define D2			25

#define D3_PORT		PIOC
#define D3			28

#define D4_PORT		PIOC
#define D4			26

#define D5_PORT		PIOC
#define D5			25

#define D6_PORT		PIOC
#define D6			24

#define D7_PORT		PIOC
#define D7			23

#define D8_PORT		PIOC
#define D8			22

#define D9_PORT		PIOC
#define D9			21

#define D10_PORT	PIOC
#define D10			29

#define D11_PORT	PIOD
#define D11			7

#define D12_PORT	PIOD
#define D12			8

#define D13_PORT	PIOB
#define D13			27

#define D22_PORT	PIOB
#define D22			26

#define D23_PORT	PIOA
#define D23			14

#define D24_PORT	PIOA
#define D24			15

#define D25_PORT	PIOD
#define D25			0

#define D26_PORT	PIOD
#define D26			1

#define D27_PORT	PIOD
#define D27			2

#define D28_PORT	PIOD
#define D28			3

#define D29_PORT	PIOD
#define D29			6

#define D30_PORT	PIOD
#define D30			9

#define D31_PORT	PIOA
#define D31			7

#define D32_PORT	PIOD
#define D32			10

#define D33_PORT	PIOC
#define D33			1

#define D34_PORT	PIOC
#define D34			2

#define D35_PORT	PIOC
#define D35			3

#define D36_PORT	PIOC
#define D36			4

#define D37_PORT	PIOC
#define D37			5

#define D38_PORT	PIOC
#define D38			6

#define D39_PORT	PIOC
#define D39			7

#define D40_PORT	PIOC
#define D40			8

#define D41_PORT	PIOC
#define D41			9

#define D42_PORT	PIOA
#define D42			19

#define D43_PORT	PIOA
#define D43			20

#define D44_PORT	PIOC
#define D44			19

#define D45_PORT	PIOC
#define D45			18

#define D46_PORT	PIOC
#define D46			17

#define D47_PORT	PIOC
#define D47			16

#define D48_PORT	PIOC
#define D48			15

#define D49_PORT	PIOC
#define D49			14

#define D50_PORT	PIOC
#define D50			13

#define D51_PORT	PIOC
#define D51			12

#define D52_PORT	PIOB
#define D52			21

#define D53_PORT	PIOB
#define D53			14

#endif
