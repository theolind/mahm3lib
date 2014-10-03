/**
 * @file

 * @author Theodor Lindquist
 * @author Jonathan Bjarnarsson
 * @author Soded Alatia
 * @version 0.1
 * @date 28 sep 2014
 *
 * @brief First draft of the SPI interface
 */

#ifndef SPI_H_
#define SPI_H_

#include <inttypes.h>

//base addresses to SPI registers
#define SPI0 ((spi_reg_t *) 0x40008000U)
#define SPI1 ((spi_reg_t *) 0x4000C000U)

///\cond
/*
 * Mapping of SPI registers
 */
typedef struct spi_reg_t {
	uint32_t SPI_CR;		//0x00, control register
	uint32_t SPI_MR;		//0x04, mode register
	uint32_t SPI_RDR;		//0x08, receive data register
	uint32_t SPI_TDR;		//0x0c, transmit data register
	uint32_t SPI_SR;		//0x10, status register
	uint32_t SPI_IER;		//0x14, interrupt enable register
	uint32_t SPI_IDR;		//0x18, interrupt disable register
	uint32_t SPI_IMR;		//0x1c, interrupt mask register
	uint32_t reserved0[3];	//0x20-0x2c, reserved
	uint32_t SPI_CSR0;		//0x30, chip select register 0
	uint32_t SPI_CSR1;		//0X34, chip select register 1
	uint32_t SPI_CSR2;		//0X38, chip select register 2
	uint32_t SPI_CSR3;		//0X3C, chip select register 3
	uint32_t reserved1[40];	//0x40 - 0xe0, reserved
	uint32_t SPI_WPCR;		//0xE4, write protection control register
	uint32_t SPI_WPSR;		//0xE8, write protection status register
	//registers 0xec - 0xfc reserved
} spi_reg_t;
///\endcond

typedef struct {
	uint32_t master;
	uint32_t mode;	//1-4
	uint32_t baud;
	uint32_t start_delay;
	uint32_t end_delay;
} spi_settings_t;

//this would start configure the pins etc.
//return 0 (1 as error code in the future)

/**
 * Initialize SPI
 * @param spi
 */
uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings);

// deselects the current slave then selects a new slave
// this either requires a global variable,
// or it requires another function spi_deselect_periphial(uint8_t periphial)
// or the two functions could be in one: spi_select_periphial(uint8_t old, uint8_t new)
void spi_select_slave(spi_reg_t *spi, uint8_t slave, uint8_t baud);

//since spi cannot transmit without receiving, it makes sense to combine
//transmission and reception in the same function
//alternate names: transact, execute, step, work, network, act, operate, perform, do
void spi_write_char(spi_reg_t *spi, uint8_t data);
uint8_t spi_read_char(spi_reg_t *spi);

//spi also seems to be able to send and receive 16 bit data chunks
uint16_t spi_write_16_bits(spi_reg_t *spi, uint16_t data);
uint16_t spi_read_16_bits(spi_reg_t *spi);

//we want to be able to test if we have sent our data
uint8_t spi_write_ready(spi_reg_t *spi);

//we want to test if we have any data received but not read yet
uint8_t spi_read_ready(spi_reg_t *spi);



#endif /* SPI_H_ */
