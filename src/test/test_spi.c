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
			.CPOL = 0,
			.baud = 128,
			.NCPHA = 0
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
			.CPOL = 0,
			.baud = 128,
			.NCPHA = 0
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
	spi_select_slave(ID_SPI1, slave);
}

void test_spi_0_write(void){
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Write new data
	spi_write(SPI0, CHAR_TEST_VALUE);
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI0->SPI_SR & (0x1u << SPI_SR_RDRF));
	// TDRE should give out 0
}

void test_spi_1_read(void){
	// Check if new data has been received since last read
	TEST_ASSERT_TRUE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Read data
	TEST_ASSERT_TRUE(spi_read(ID_SPI1) == CHAR_TEST_VALUE);
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
}

void test_spi_1_write(void){
	// Check if new data has been received since last read
	TEST_ASSERT_FALSE(SPI1->SPI_SR & (0x1u << SPI_SR_RDRF));
	// Write new data
	spi_write(SPI1, CHAR_TEST_VALUE);
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
}
