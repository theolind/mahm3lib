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
/*
static void test_twi_init(void){
	pmc_enable_peripheral_clock(ID_TWI0);

	pio_conf_pin_to_peripheral(PIOA, PHERIPHERAL_A, 17);	//TWCK
	pio_conf_pin_to_peripheral(PIOA, PHERIPHERAL_A, 18);	//TWD

	pmc_enable_peripheral_clock(ID_TWI1);

	pio_conf_pin_to_peripheral(PIOB, PHERIPHERAL_A, 12);	//TWCK
	pio_conf_pin_to_peripheral(PIOB, PHERIPHERAL_A, 13);	//TWD

	twi_init();
}
*/

/*
 * This test performs a control of:
 * 	1) is current Master Read Direction modified?
 * 	2) is Device Address set?
 * 	3) is a 8-bit Device Address ignored?
 * 	4) is Internal Address Size set?
 * 	5) can the setting for the Internal Address Size be larger than 2 bits?
 */
void test_twi_set_device_address(void) {
	// Set Master Read Direction
	TWI0->TWI_MMR = (1 << 12);
	TWI1->TWI_MMR = (1 << 12);
	// Set Device Address and Internal Address Size
	twi_set_device_address(TWI0, 0xFF, 7);
	twi_set_device_address(TWI1, 0xFF, 7);
	// Master Read Direction shouldn't be modified
	TEST_ASSERT_TRUE(TWI0->TWI_MMR & (1 << 12));
	TEST_ASSERT_TRUE(TWI1->TWI_MMR & (1 << 12));
	// Device Address should be set
	TEST_ASSERT_TRUE(TWI0->TWI_MMR & (0xFF << 16));
	TEST_ASSERT_TRUE(TWI1->TWI_MMR & (0xFF << 16));
	// a 8-bit address should be ignored
	TEST_ASSERT_TRUE((TWI0->TWI_MMR >> 16) == 0x7F);
	TEST_ASSERT_TRUE((TWI1->TWI_MMR >> 16) == 0x7F);
	// Internal Address Size should be set
	TEST_ASSERT_TRUE(TWI0->TWI_MMR & (7 << 8));
	TEST_ASSERT_TRUE(TWI1->TWI_MMR & (7 << 8));
	// Internal Address Size larger than 2 bits should be ignored
	TEST_ASSERT_TRUE(((TWI0->TWI_MMR >> 8) & 0xF) == 3);
	TEST_ASSERT_TRUE(((TWI1->TWI_MMR >> 8) & 0xF) == 3);
}

/*
 * This test performs a control of:
 * 	1) can the TWI_IADR register be set for TWI0 and TWI1?
 * 	2) if an address is larger than 3 bytes, will the rest be ignored?
 */
void test_twi_set_internal_address(void) {
	// set 4-byte address
	twi_set_internal_address(TWI0, 0xFFFFFFFF);
	// address shouldn't be larger than 3 bytes
	TEST_ASSERT_FALSE(TWI0->TWI_IADR > 0xFFFFFF);
	// set 4-byte address
	twi_set_internal_address(TWI1, 0xFFFFFFFF);
	// address shouldn't be larger than 3 bytes
	TEST_ASSERT_FALSE(TWI1->TWI_IADR > 0xFFFFFF);
}

/*
 * Will invalid parameters be denied?
 */
void test_twi_set_clock_invalid_parameters(void) {
	uint8_t error;
	// too large bus speed...
	error = twi_set_clock(TWI0, 400001, 84000000);
	// ...shouldn't be accepted!
	TEST_ASSERT_TRUE(error == 1);
	// too small MCK in relation to bus speed...
	error = twi_set_clock(TWI0, 400000, 800000);
	// ...shouldn't be accepted!
	TEST_ASSERT_TRUE(error == 1);
	// too small bus speed...
	error = twi_set_clock(TWI0, 0, 84000000);
	// ...shouldn't be accepted!
	TEST_ASSERT_TRUE(error == 1);
}

/*
 * This test performs a control of:
 * 	1) will valid parameters be accepted?
 * 	2) will this render in a correct register setting?
 */
void test_twi_set_clock_valid_parameters(void) {
	uint32_t reg0, reg1;
	uint8_t error;
	// too large bus speed...
	error = twi_set_clock(TWI0, TWI_FAST_MODE_SPEED, 84000000) |
			twi_set_clock(TWI1, TWI_FAST_MODE_SPEED, 84000000);
	// ...should be accepted!
	TEST_ASSERT_TRUE(error == 0);

	// store register values
	reg0 = TWI0->TWI_CWGR;
	reg1 = TWI1->TWI_CWGR;
	/*
	 * According to the given formula (see datasheet),
	 * divider for Clock Low and Clock High should be 101,
	 * Clock Divider should be zero.
	 */
	TEST_ASSERT_TRUE((reg0 & 0xFFu) == 101);		// check Clock Low Divider
	TEST_ASSERT_TRUE((reg1 & 0xFFu) == 101);
	TEST_ASSERT_TRUE(((reg0 >> 8) & 0xFFu) == 101);	// check Clock High Divider
	TEST_ASSERT_TRUE(((reg1 >> 8) & 0xFFu) == 101);
	TEST_ASSERT_TRUE((reg0 & (7u << 16)) == 0);		// check Clock Divider
	TEST_ASSERT_TRUE((reg1 & (7u << 16)) == 0);
}

void test_twi_send_receive_SEMI_AUTOMATIC(void) {

}
/*

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

	const twi_packet_t packet = {
		.address[3] = {0x40u, 0x80u, 0x120u},
		.address_length = 3,
		.buffer = data_array[0],
		.data_length = 3,
		.chip
	};


	//TEST_ASSERT_TRUE(twi_master_write(twi, packet));
}

void test_twi_master_read(twi_reg_t *twi){

}

void test_twi_slave_init(twi_reg_t *twi){
	//twi_master_init(twi, );

}

void test_twi_slave_write(twi_reg_t *twi){

}

void test_twi_slave_read(twi_reg_t *twi){

}
*/
