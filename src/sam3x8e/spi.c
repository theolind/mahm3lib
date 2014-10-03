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
	spi->SPI_CR = 1; //same as (1<<0); //enabling SPI
	spi->SPI_MR = settings->master;
}

void spi_select_slave(spi_reg_t *spi, uint8_t slave, uint8_t baud) {

}

void spi_write(spi_reg_t *spi, uint8_t data) {
	// transfer begins when processor writes to spi->SPI_TDR
	// before writing SPI_TDR, PCS field in SPI_MR must be set in order to select slave

	//if SPI_RDR has not been read OVRES in SPI_SR is set
	//user has to read SPI_SR to clear OVRES

	spi->SPI_TDR = data;
}

uint8_t spi_read(spi_reg_t *spi) {
	// SPI_RDR holds received data, this register is full when RDRF bit in SPI_SR is set
	//When data is read, this bit is cleared
	return spi->SPI_RDR;
}

uint8_t spi_write_ready(spi_reg_t *spi) {
	// transfer of data to shift register is indicated by TDRE bit in SPI_SR
	// transmission completion is indicated by TXEMPTY bit in SPI_SR
	return ((spi->SPI_SR & (1<<9)) >> 9);
}

uint8_t spi_read_ready(spi_reg_t *spi) {
	return ((spi->SPI_SR & (1<<3)) >> 3);
}
