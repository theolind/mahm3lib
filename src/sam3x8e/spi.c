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

}

void spi_select_slave(spi_reg_t *spi, uint8_t slave, uint8_t baud);

void spi_write_char(spi_reg_t *spi, uint8_t data);
uint8_t spi_read_char(spi_reg_t *spi);

uint16_t spi_write_16_bits(spi_reg_t *spi, uint16_t data);
uint16_t spi_read_16_bits(spi_reg_t *spi);

uint8_t spi_write_ready(spi_reg_t *spi);

uint8_t spi_read_ready(spi_reg_t *spi);
