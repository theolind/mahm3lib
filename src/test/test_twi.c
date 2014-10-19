/*
 * @file test_twi.c
 * @brief Two Wire Interface (TWI) unit tests
 * @details This class is used to test the capabilities of the TWI API
 *
 * @author Jonathan Bjarnason
 * @date 12 October 2014
 */

#include "unity/unity.h"
#include "sam3x8e/id.h"
#include "sam3x8e/twi.h"
#include "sam3x8e/pio.h"
#include "test/test_twi.h"

static void test_twi_init(void){
	pmc_enable_peripheral_clock(ID_TWI0);

	pio_conf_pin_to_peripheral(PIOA, PHERIPHERAL_A, 17);	//TWCK
	pio_conf_pin_to_peripheral(PIOA, PHERIPHERAL_A, 18);	//TWD

	pmc_enable_peripheral_clock(ID_TWI1);

	pio_conf_pin_to_peripheral(PIOB, PHERIPHERAL_A, 12);	//TWCK
	pio_conf_pin_to_peripheral(PIOB, PHERIPHERAL_A, 13);	//TWD

	twi_init();
}

void test_twi_master_init(twi_reg_t *twi){
	test_twi_init();

	const twi_settings_t settings = {
		.baudrate = 9200,
		.master_clk = 30
	};

	TEST_ASSERT_TRUE(twi_master_init(twi, settings));

}

void test_twi_master_write(twi_reg_t *twi){
	// Spells 'twi' in ASCII code
	uint8_t data_array[3] = { 0x74, 0x77, 0x69 };
/*
	const twi_packet_t packet = {
		.address[3] = {0x40u, 0x80u, 0x120u},
		.address_length = 3,
		.buffer = data_array[0],
		.data_length = 3,
		.chip
	};
*/

	//TEST_ASSERT_TRUE(twi_master_write(twi, packet));
}

void test_twi_master_read(twi_reg_t *twi){

}

void test_twi_slave_init(twi_reg_t *twi){
	twi_master_init(twi, );

}

void test_twi_slave_write(twi_reg_t *twi){

}

void test_twi_slave_read(twi_reg_t *twi){

}
