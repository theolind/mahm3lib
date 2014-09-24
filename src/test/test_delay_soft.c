/**
 * \class test_runner_delay_soft
 * \brief Test runner for the software delay routines
 * \details This class starts the tests for the delay routines in delay_soft API
 * \author Saeed Ghasemi
 * \version 0.1
 * \date 22 sep 2014
 * \pre These test are waiting for the Hardware timer API to be released in order to make a automated test
 * \bug
 */


//#include "global_definitions.h"
//#include "delay_soft.h"
//#include "pio.h"



/*--------------------------

// Descriptive names for TIMING-pins
#define Arduino_Pin_24_Front_Reg    PIO_PA15_IDX		//Arduino Due pin 24 used to measure work load
#define Arduino_Pin_25_LineAnalizer	PIO_PD0_IDX		//Arduino Due pin 25 used to measure work load


int main (void)
{
	pio_init_param *param;

	(*param).porta = OFF;
	(*param).portb = OFF;
	(*param).portc = OFF;
	(*param).portd = ON;
	(*param).porte = OFF;
	(*param).portf = OFF;


	board_init();

	pio_init(param);



	// Insert application code here, after the board has been initialized.
	ioport_set_pin_dir(Arduino_Pin_25_LineAnalizer, IOPORT_DIR_OUTPUT);

	void pio_conf_pin(uint32_t port, uint8_t pin_number, uint8_t input, uint8_t pullup);

	ioport_set_pin_dir(Arduino_Pin_24_Front_Reg, IOPORT_DIR_OUTPUT);
	while (1){
		ioport_set_pin_level(Arduino_Pin_24_Front_Reg, HIGH);
		//ioport_set_pin_level(Arduino_Pin_25_LineAnalizer, LOW);

		timer_delaySoftware_1us(1000);

		ioport_set_pin_level(Arduino_Pin_24_Front_Reg, LOW);
		//ioport_set_pin_level(Arduino_Pin_25_LineAnalizer, HIGH);



		volatile int j = 100;
		while (j != 0){
			j--;
		}

	}
}

-------------------------*/
