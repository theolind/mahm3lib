/*
 * @file test_spi.h
 * @brief Serial Peripheral Interface (SPI) unit tests
 * @details This class is used to test the capabilities of the SPI API
 * These test use the internal loopback function of the SPI peripheral.
 * There are test for all functions.
 *
 * @author Jonathan Bjarnason
 * @author Soded Alatia
 * @author Saeed Ghasemi
 *
 * @date 1 november 2014
 */
#ifndef TEST_SPI_H_
#define TEST_SPI_H_

// Setup
void spi_setup(void);
void spi_selector_init(void);
// Initial test
void test_spi_initial_state(void);
void test_spi_after_init(void);
// Incremental tests
void test_spi_select_slave(void);
void test_spi_write_ready(void);
void test_spi_write(void);
void test_spi_read_ready(void);
void test_spi_transmission_complete(void);
void test_spi_correct_transmission(void);
void test_spi_variable_bit_lenght_transmission(void);
void test_spi_polarity_phase_change(void);
void test_spi_baud_rate_change(void);

#endif
