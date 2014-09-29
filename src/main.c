#include <stdio.h>
#include <inttypes.h>
#include "sam3x8e/global_entities.h"
#include "unity/unity_hw_setup.h"
#include "unity/unity.h"
#include "test_runner.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/delay_soft.h"

/*
int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	run_tests();

	return 0;
}
*/

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	pmc_start_peripheral_clock(ID_PWM);

	pio_init_param param;
	param.porta = ON;
	param.portb = OFF;
	param.portc = ON;
	param.portd = OFF;
	param.porte = OFF;
	param.portf = OFF;

	pio_init(&param);

	//0b0000 0000 0000 1010 1010 0001 0000 0000
//	pio_conf_pins(PIO_PORTC,  0b00000000000010101010000100000000,  0,  0);
	pio_conf_pin(PIO_PORTC,  13,  0,  0);
//	pio_conf_pin(PIO_PORTC,  17,  0,  0);
//	pio_conf_pin(PIO_PORTC,  15,  0,  0);
//	pio_conf_pin(PIO_PORTC,  19,  0,  0);
//	pio_conf_pin(PIO_PORTC,  8,  0,  0);
    pio_conf_pin(PIO_PORTA,  19,  0,  0);

	pio_set_pin( PIO_PORTC,  13,  HIGH);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTC,  17,  HIGH);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTC,  15,  HIGH);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTC,  8,  HIGH);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTC,  19,  HIGH);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTA,  19,  HIGH);
//	timer_delay_software_ms(10000);

	pio_set_pin( PIO_PORTC,  13,  LOW);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTC,  17,  LOW);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTC,  15,  LOW);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTC,  8,  LOW);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTC,  19,  LOW);
//	timer_delay_software_ms(10000);
//	pio_set_pin( PIO_PORTA,  19,  LOW);
//	timer_delay_software_ms(10000);








	while(1){}

	volatile uint32_t j,i;
	while(1){

		timer_delay_software_ms(10000);
		pio_set_pin( PIO_PORTC,  13,  LOW);
		pio_set_pin( PIO_PORTC,  17,  HIGH);

		for(i = 0 ; i < 50000 ; i++){
			j++;
		}

		timer_delay_software_ms(10000);
		pio_set_pin( PIO_PORTC,  13,  HIGH);
		pio_set_pin( PIO_PORTC,  17,  LOW);

		for(i = 0 ; i < 10000 ; i++){
			j++;
		}

	}
	return 0;
}
