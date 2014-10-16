/**
 * pmc.c
 *
 * Authors:
 * 		Theodor Lindquist
 * 		Soded Alatia
 * 		Jonathan Bjarnarsson
 *
 * Date: 29 sep 2014
 */

#include "spi.h"

uint8_t spi_init(spi_reg_t *spi, const spi_settings_t *settings) {
	spi->SPI_CR |= (1<<7); //reset the SPI
	spi->SPI_CR |= 0b1; //same as (1<<0); //enabling SPI
	spi->SPI_MR |= settings->master;
	spi->SPI_WPMR |= 0b10100110101000000100100100000000;
	//spi->SPI_MR |= (1<<5);	//Wait Data Read Before Transfer - prevents overrun of SPI_RDR
	spi->SPI_MR &= ~(1<<1);	//Clear bit one in MR to set fied peripheral select
	spi->SPI_CSR0 = settings->CPOL | (settings->NCPHA<<1) | (settings->bits[0]<<4)
					| (settings->baud[0]<<8) | (settings->DLYBS<<16) | (settings->DLYBCT<<24);
	spi->SPI_CSR1 = settings->CPOL | (settings->NCPHA<<1) | (settings->bits[1]<<4)
						| (settings->baud[1]<<8) | (settings->DLYBS<<16) | (settings->DLYBCT<<24);
	spi->SPI_CSR2 = settings->CPOL | (settings->NCPHA<<1) | (settings->bits[2]<<4)
						| (settings->baud[2]<<8) | (settings->DLYBS<<16) | (settings->DLYBCT<<24);
	spi->SPI_CSR3 = settings->CPOL | (settings->NCPHA<<1) | (settings->bits[3]<<4)
						| (settings->baud[3]<<8) | (settings->DLYBS<<16) | (settings->DLYBCT<<24);
}

void spi_select_slave(spi_reg_t *spi, uint8_t slave) {
	spi->SPI_MR &= ~(0b1111 << 16);	//clear bit 16 to 19 in SPI_MR
	spi->SPI_MR |= (0b111 >> (3-slave)) << 16; //set bit 16 to 18 in SPI_MR
}

void spi_write(spi_reg_t *spi, uint16_t data) {
	// transfer begins when processor writes to spi->SPI_TDR
	// before writing SPI_TDR, PCS field in SPI_MR must be set in order to select slave

	//if SPI_RDR has not been read OVRES in SPI_SR is set
	//user has to read SPI_SR to clear OVRES

	spi->SPI_TDR = data;
}

uint16_t spi_read(spi_reg_t *spi) {
	// SPI_RDR holds received data, this register is full when RDRF bit in SPI_SR is set
	//When data is read, this bit is cleared
	return spi->SPI_RDR;
}

uint32_t spi_write_ready(spi_reg_t *spi) {
	// transfer of data to shift register is indicated by TDRE bit in SPI_SR
	// transmission completion is indicated by TXEMPTY bit in SPI_SR
	return (spi->SPI_SR & (0x1u << 9));
}

uint8_t spi_read_ready(spi_reg_t *spi) {
	return (spi->SPI_SR & (0x1u<<0));
}
