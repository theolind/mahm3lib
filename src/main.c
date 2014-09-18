#include <stdio.h>

#include "unity_hw_setup.h"
#include "unity.h"
#include "test_runner.h"
#include "adc.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// Needed for running tests?
	adc_init(2);

	adc_set_resolution(12);

	//run_tests();

	adc_enable_channel(ADC_CHANNEL_0);

	uint16_t data;

	data = adc_read_channel(ADC_CHANNEL_0);


	while (1){
		data = adc_read_channel(ADC_CHANNEL_0);
		print_int(data);

		for(int i = 0; i<100000; i++);
	}
    return 0;
}

void print_int(uint16_t data){
	uint16_t first, second, third, fourth;

	first = (data - (data % 1000)) / 1000;
	data = (data - first*1000);
	second = (data - (data % 100)) / 100;
	data = (data - second*100);
	third = (data -(data % 10)) / 10;
	data = (data - second *10);
	fourth = data % 10;

	char dataprint[4];
	dataprint[0] = (char)first;
	dataprint[1] = (char)second;
	dataprint[2] = (char)third;
	dataprint[3] = (char)fourth;

	for(int i = 0; i<4; i++){
		UNITY_OUTPUT_CHAR(dataprint[i]+48);
	}

	UNITY_OUTPUT_CHAR('\r');
    UNITY_OUTPUT_CHAR('\n');
}
