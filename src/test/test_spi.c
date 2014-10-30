/*
 * @file test_spi.c
 * @brief Serial Peripheral Interface (SPI) unit tests
 * @details This class is used to test SPI capabilities of this API
 *
 * @author Jonathan Bjarnason
 * @author Soded Alatia
 * @date 2 October 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/id.h"
#include "sam3x8e/spi_2.h"
#include "sam3x8e/pio.h"
#include "test/test_spi.h"
#include "sam3x8e/delay.h"

// TODO We will be needing a test for all functions.
// and tests for functionality that are largely done so far.

void test_spi_setup(void) {
	pmc_enable_peripheral_clock(ID_SPI0);
	pmc_enable_peripheral_clock(ID_PIOA);

	pio_conf_pin_to_peripheral(PIOA, 0, 25);	//MISO
	pio_conf_pin_to_peripheral(PIOA, 0, 26);	//MOSI
	pio_conf_pin_to_peripheral(PIOA, 0, 27);	//SPCK
	pio_conf_pin_to_peripheral(PIOA, 0, 28);	//NPCS0
	pio_conf_pin_to_peripheral(PIOA, 0, 29);	//NPCS1
	pio_conf_pin_to_peripheral(PIOA, 0, 30);	//NPSC2
	pio_conf_pin_to_peripheral(PIOA, 0, 31);	//NPSC3

	const spi_settings_t setting = { .delay_between_cs = 12, };

	// initialize selector 0
	spi_selector_settings_t selector_0;
	selector_0.selector = SPI_SELECTOR_0;
	selector_0.CPOL = SPI_POLARITY_LOW;
	selector_0.NCPHA = SPI_PHASE_LOW;
	selector_0.baud_rate = 255;
	selector_0.bits_pr_transfer = SPI_BITS_8;
	selector_0.delay_clk = 492; // 41*12ns = 492 ns
	selector_0.delay_transfers = 381;

	// initialize selector 1
	spi_selector_settings_t selector_1;
	selector_0.selector = SPI_SELECTOR_1;
	selector_0.CPOL = SPI_POLARITY_HIGH;
	selector_0.NCPHA = SPI_PHASE_LOW;
	selector_0.baud_rate = 128;
	selector_0.bits_pr_transfer = SPI_BITS_8;
	selector_0.delay_clk = 1000; // 41*12ns = 492 ns
	selector_0.delay_transfers = 1000;

	spi_init(SPI0, &setting);
	spi_init_selector(SPI0, &selector_0);
	spi_init_selector(SPI0, &selector_1);

	spi_loopback_enable(SPI0);

	spi_select_slave(SPI0, SPI_SELECTOR_0); // Slave 0

}

void test_spi_init(void) {
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_SPIENS));
}

void test_spi_select_slave(void) {
	spi_select_slave(SPI0, SPI_SELECTOR_0);
	//TODO write a test for this
}

void test_spi_write_ready() {
	TEST_ASSERT_TRUE(spi_tx_ready(SPI0));
}

void test_spi_write() {
	spi_write(SPI0, 0b01011010);
	TEST_ASSERT_FALSE(SPI0->SPI_SR & (0x1u << 1));
	delay_ms(1);
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << 1));
}

void test_spi_transmission_complete() {
	delay_ms(1);
	spi_write(SPI0, 0b01011010);
	spi_write(SPI0, 0b01011011);
	TEST_ASSERT_FALSE(SPI0->SPI_SR & (0x1u << 1));
	delay_ms(1);
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << 1));
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << 9));
}

void test_spi_read_ready() {
	spi_read(SPI0);
	spi_write(SPI0, 0b00000000);
	delay_ms(1);
	TEST_ASSERT_TRUE(spi_rx_ready(SPI0));
}

void test_spi_correct_transmission(void) {
	while (!spi_tx_ready(SPI0))
		;
	// We wish to see if the byte transmitted is the same as the one received.
	uint16_t data1 = 0b10101010;
	uint16_t data2 = 0b10101011;
	spi_write(SPI0, data1);
	delay_ms(1);
	TEST_ASSERT_FALSE(spi_read(SPI0) == ~data1);
	TEST_ASSERT_TRUE(spi_read(SPI0) == data1);
	// We also want to see the behavior when an overrun is occurred.
	spi_write(SPI0, data1);
	spi_write(SPI0, data2);
	delay_ms(1);
	TEST_ASSERT_FALSE(spi_read(SPI0) == ~data2);
	TEST_ASSERT_TRUE(spi_read(SPI0) == data2);
}
/*
 void test_spi_0_write(void){
 // Check if new data has been received since last read
 TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
 // Write new data
 spi_write(SPI0, CHAR_TEST_VALUE);
 // Check if new data has been received since last read
 TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_RDRF));
 // TDRE should give out 0
 }

 void test_spi_0_read(void){
 // Check if new data has been received since last read
 TEST_ASSERT_TRUE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
 // Read data
 TEST_ASSERT_TRUE(spi_read(ID_SPI0) == CHAR_TEST_VALUE);
 // Check if new data has been received since last read
 TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
 }*/
