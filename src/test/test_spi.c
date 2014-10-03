/*
 * @file test_spi.c
 * @brief Serial Peripheral Interface (SPI) unit tests
 * @details This class is used to test SPI capabilities of this API
 *
 * @author Jonathan Bjarnason
 * @date 2 October 2014
 */

#include "unity/unity.h"
#include "sam3x8e/id.h"
#include "sam3x8e/spi.h"
#include "test/test_spi.h"

/*
 * Initialize SPI0 as master and other necessary settings.
 * Enable SPI0 peripheral clock.
 * Test if SPI0 is enabled before and after spi_init() is run
 */
void test_spi_0_init(void){
	// Needs to be updated with relevant data
	const spi_settings_t spi_settings_t = {
			.master = 1,
			.mode = 0,
			.baud = 0,
			.start_delay = 0,
			.end_delay = 0
	};

	pmc_enable_peripheral_clock(ID_SPI0);

	TEST_ASSERT_FALSE(SPI0->SPI_SR & (0x1u << SPI_SR_SPIENS));
	TEST_ASSERT_TRUE(spi_init(SPI0, &spi_settings_t));
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_SPIENS));
}

/*
 * Initialize SPI1 as slave and other necessary settings.
 * Enable SPI1 peripheral clock.
 * Test if SPI1 is enabled before and after spi_init() is run
 */
void test_spi_1_init(void){
	// Needs to be updated with relevant data
	const spi_settings_t spi_settings_t = {
			.master = 0,
			.mode = 0,
			.baud = 0,
			.start_delay = 0,
			.end_delay = 0
	};

	pmc_enable_peripheral_clock(ID_SPI1);

	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_SPIENS));
	TEST_ASSERT_TRUE(spi_init(SPI1, &spi_settings_t));
	TEST_ASSERT_TRUE(SPI1->SPI_SR & (0x1u << (SPI_SR_SPIENS)));
}

/*
 * Select SPI1 as slave, SPI0 is master.
 * Not sure if this needs testing but the initialization is necessary for the
 * tests that follow. Values need updating with relevant data.
 */
void test_spi_select_slave(void){
	uint8_t slave = 0;
	uint8_t baud = 0;
	spi_select_slave(ID_SPI1, slave, baud);
}

void test_spi_0_write_char(void){
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Write new data
	spi_write_char(SPI0, CHAR_TEST_VALUE);
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_RDRF));
	// TDRE should give out 0
}

void test_spi_1_read_char(void){
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Read data
	TEST_ASSERT_TRUE(spi_read_char(ID_SPI1) == CHAR_TEST_VALUE);
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
}

void test_spi_1_write_char(void){
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Write new data
	spi_write_char(SPI1, CHAR_TEST_VALUE);
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_RDRF));
	// TDRE should give out 0
}

void test_spi_0_read_char(void){
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Read data
	TEST_ASSERT_TRUE(spi_read_char(ID_SPI0) == CHAR_TEST_VALUE);
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
}

void test_spi_0_write_16_bit(void){
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Write new data
	spi_write_16_bits(SPI0, TEST_VALUE_16_BIT);
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_RDRF));
	// TDRE should give out 0
}

void test_spi_1_read_16_bit(void){
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Read data
	TEST_ASSERT_TRUE(spi_read_16_bits(SPI1) == TEST_VALUE_16_BIT);
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
}

void test_spi_1_write_16_bit(void){
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Write new data
	spi_write_16_bits(SPI0, TEST_VALUE_16_BIT);
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_RDRF));
	// TDRE should give out 0
}

void test_spi_0_read_16_bit(void){
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Read data
	TEST_ASSERT_TRUE(spi_read_16_bits(SPI0) == TEST_VALUE_16_BIT);
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));

	pmc_disable_peripheral_clock(ID_SPI0);
	pmc_disable_peripheral_clock(ID_SPI1);
}
