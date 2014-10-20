/*
 * test_spi_hardcoded.c
 *
 *  Created on: Oct 20, 2014
 *      Author: th
 */

#include "sam3x8e/spi_hardcoded.h"
#include "test/test_spi_hardcoded.h"
#include <inttypes.h>

uint32_t *const p_SPI0_SR;
uint32_t *const p_SPI0_MR;

void test_spi_init_hardcoded(void) {
	spi_init_hardcoded();

	TEST_ASSERT_TRUE(*p_SPI0_SR & (0x1u << 16));	//spi enabled?
	TEST_ASSERT_TRUE(*p_SPI0_MR & (0x1u << 0));	//spi is master?
}

void test_spi_select_slave_hardcoded(void) {
	spi_select_slave_hardcoded();
}

void test_spi_tx_ready_hardcoded(void) {
	TEST_ASSERT_TRUE( spi_tx_ready_hardcoded() );
}

void test_spi_tx_hardcoded(void) {
	while(!spi_tx_ready_hardcoded());	//wait for tx ready
	spi_tx_hardcoded(0b11011010);
}

void test_spi_rx_ready_hardcoded(void) {
	TEST_ASSERT_FALSE( spi_rx_ready_hardcoded() );
}

void test_spi_rx_hardcoded(void) {
	while(!spi_rx_ready_hardcoded());
	TEST_ASSERT_EQUAL( spi_rx_hardcoded(), 0b11011010 );
}
