#include <stdio.h>
#include <inttypes.h>
#include "unity/unity_hw_setup.h"
#include "unity/unity.h"
#include "test_runner.h"

#include "sam3x8e/pmc.h"
#include "sam3x8e/adc.h"


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	run_tests();

	// REMOVE BEFORE MERGE, used to test adc manually
//	pmc_start_peripheral_clock(37); //temp, but needed for adc tests
//	adc_init();
//	uint8_t channel = ADC_CHANNEL_0;
//	adc_enable_channel(channel);
//	adc_start();
//
//	while(adc_channel_enabled(channel)){
//
//		// Read channel
//		uint16_t data;
//
//		while(!(ADC->ADC_ISR & 0x01000000));
//
//		data = (uint16_t) adc_read_channel(channel);
//
//		// Print value through serial communicatin
//		uint16_t first, second, third, fourth;
//
//		first = (data - (data % 1000)) / 1000;
//		data = (data - first * 1000);
//		second = (data - (data % 100)) / 100;
//		data = (data - second * 100);
//		third = (data - (data % 10)) / 10;
//		data = (data - second * 10);
//		fourth = data % 10;
//
//		char dataprint[4];
//		dataprint[0] = (char) first;
//		dataprint[1] = (char) second;
//		dataprint[2] = (char) third;
//		dataprint[3] = (char) fourth;
//
//		for (int i = 0; i < 4; i++) {
//			UNITY_OUTPUT_CHAR(dataprint[i] + 48);
//		}
//
//		UNITY_OUTPUT_CHAR('\r');
//		UNITY_OUTPUT_CHAR('\n');
//
//		// Delay
//		for (int i = 0; i < 10000000; i++);
//
//		adc_start(); //Why is this one needed?
//	}

	return 0;
}
