/*
 * test_spi_hardcoded.c
 *
 *  Created on: Oct 20, 2014
 *      Author: th
 */

#include "unity/unity.h"
#include "sam3x8e/spi_hardcoded.h"
#include "sam3x8e/pio.h"
#include "test/test_spi_hardcoded.h"
#include <inttypes.h>

uint32_t *const p_SPI0_SR;
uint32_t *const p_SPI0_MR;

void test_spi_init_hardcoded(void) {
	pmc_enable_peripheral_clock(24);

	spi_init_hardcoded();

	pio_conf_pin_to_peripheral(PIOA, 0, 25);	//MISO
	pio_conf_pin_to_peripheral(PIOA, 0, 26);	//MOSI
	pio_conf_pin_to_peripheral(PIOA, 0, 27);	//SPCK
	pio_conf_pin_to_peripheral(PIOA, 0, 28);	//NPCS0
	pio_conf_pin_to_peripheral(PIOA, 0, 29);	//NPCS1
	pio_conf_pin_to_peripheral(PIOA, 0, 30);	//NPSC2
	pio_conf_pin_to_peripheral(PIOA, 0, 31);	//NPSC3

	TEST_ASSERT_TRUE(*p_SPI0_SR & (0x1u << 16));	//spi enabled?
	TEST_ASSERT_TRUE(*p_SPI0_MR & (0x1u << 0));	//spi is master?
}

void test_spi_select_slave_hardcoded(void) {
	spi_select_slave_hardcoded();
}

void test_spi_tx_ready_hardcoded(void) {
	TEST_ASSERT_TRUE( spi_tx_ready() );
}

void test_spi_tx_hardcoded(void) {
	while(!spi_tx_ready());	//wait for tx ready
	spi_tx(0b11011010);
}

void test_spi_rx_ready_hardcoded(void) {
	TEST_ASSERT_FALSE( spi_rx_ready() );
}

void test_spi_rx_hardcoded(void) {
	while(!spi_rx());
	TEST_ASSERT_EQUAL( spi_rx(), 0b11011010 );
}
