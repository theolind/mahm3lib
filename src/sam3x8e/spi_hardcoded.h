/*
 * spi_hardcoded.h
 *
 *  Created on: 19 okt 2014
 *      Author: Soddi
 */

#ifndef SAM3X8E_SPI_HARDCODED_H_
#define SAM3X8E_SPI_HARDCODED_H_

#include <inttypes.h>

void spi_init_hardcoded(void);
void spi_select_slave_hardcoded(void);
uint32_t spi_rx(void);
void spi_tx(uint16_t data);
uint32_t spi_rx_ready(void);
uint32_t spi_tx_ready(void);


#endif /* SAM3X8E_SPI_HARDCODED_H_ */
