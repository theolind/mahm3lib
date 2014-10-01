#include "unity/unity.h"
#include "test_runner.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	// run unit tests
	//run_tests();


	//Test delay on pin 46
	/*
	pio_conf_pin(PIOC, 17,  0, 0);
	for(;;){
		pio_set_pin(PIOC, 17, 0);
		//delay_milliseconds(1);
		delay_microseconds(30);
		pio_set_pin(PIOC, 17, 1);
	}
	*/

	//Test delay on L-LED (amber light)
	pio_conf_pin(PIOB, 27, 0, 0);
	for(;;){
		pio_set_pin(PIOB, 27, 1);
		//delay_microseconds(10000000);
		delay_milliseconds(5000);
		pio_set_pin(PIOB, 27, 0);
		delay_milliseconds(5000);
	}

	return 0;
}
