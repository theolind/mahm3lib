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

#include "inttypes.h"

//base addresses to SPI registers
#define SPI0 ((spi_reg_t *) 0x40008000U)
#define SPI1 ((spi_reg_t *) 0x4000C000U)

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
	uint32_t SPI_RES0[3];	//0x20-0x2c, reserved
	uint32_t SPI_CSR0;		//0x30, chip select register 0
	uint32_t SPI_CSR1;		//0X34, chip select register 1
	uint32_t SPI_CSR2;		//0X38, chip select register 2
	uint32_t SPI_CSR3;		//0X3C, chip select register 3
	//registers 0x40 - 0xe0 are reserved
	//Write Protection Control Register is at 0xE4
	//Write Protection Status Register is at 0xE8
	//registers 0xec - 0xfc reserved
} spi_reg_t;

typedef struct {
	uint32_t master;
	uint32_t mode;	//1-4
	uint32_t baud;
	uint32_t start_delay;
	uint32_t end_delay;
} spi_settings_t;

//this would start configure the pins etc.
void spi_init(spi_reg_t *spi, const spi_settings_t *settings);

//sets the baud on the fly, as this can be done without reconfiguring the whole SPI interface
void spi_set_baud(spi_reg_t *spi, uint8_t baud);

// deselects the current slave then selects a new slave
// this either requires a global variable,
// or it requires another function spi_deselect_periphial(uint8_t periphial)
// or the two functions could be in one: spi_select_periphial(uint8_t old, uint8_t new)
void spi_select_slave(spi_reg_t *spi, uint8_t periphial);

//since spi cannot transmit without receiving, it makes sense to combine
//transmission and reception in the same function
//alternate names: transact, execute, step, work, network, act, operate, perform, do
uint8_t spi_write_char(spi_reg_t *spi, uint8_t data);

//spi also seems to be able to send and receive 16 bit data chunks
uint16_t spi_write_word(spi_reg_t *spi, uint16_t data);



#endif /* SPI_H_ */
