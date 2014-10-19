/*
 * spi_hardcoded.c
 *
 *  Created on: 19 okt 2014
 *      Author: Soddi
 */
#include <inttypes.h>
#include "spi_hardcoded.h"

//#define SPI0 ((spi_reg_t *) 0x40008000U)
uint32_t *const p_SPI0_CR  = (uint32_t *) 0x40008000u;
uint32_t *const p_SPI0_MR  = (uint32_t *) 0x40008004u;
uint32_t *const p_SPI0_RDR  = (uint32_t *) 0x40008008u;
uint32_t *const p_SPI0_TDR  = (uint32_t *) 0x4000800Cu;
uint32_t *const p_SPI0_SR  = (uint32_t *) 0x40008010u;
uint32_t *const p_SPI0_IER  = (uint32_t *) 0x40008014u;
uint32_t *const p_SPI0_IDR  = (uint32_t *) 0x40008018u;
uint32_t *const p_SPI0_IMR  = (uint32_t *) 0x4000801Cu;
uint32_t *const p_SPI0_CSR  = (uint32_t *) 0x40008030u;
uint32_t *const p_SPI0_WPMR  = (uint32_t *) 0x400080E4u;
uint32_t *const p_SPI0_WPSR  = (uint32_t *) 0x400080E8u;

void spi_init_hardcoded(void) {
	*p_SPI0_CR = 0x1u; //enable SPI
	//*p_SPI0_WPMR &= (0x535049<<8); //if a value is written in WPEN, the WPKEY has to be "SPI" in hex.
	//*p_SPI0_WPMR &= 0x0u; //clear WPEN bit to be able to write to Mode Register

	*p_SPI0_MR = 0x1u; //master
	*p_SPI0_MR |= (0x0u<<1); //fixed PS
	*p_SPI0_MR |= (0x0u<<2); // chip select direct connect to peripheral device
	*p_SPI0_MR |= (0x1u<<4); // mode fault detection disabled
	*p_SPI0_MR |= (0x1u<<5); // wait until RDR is empty

	*p_SPI0_CSR = 0x0u; //CPOL = 0
	*p_SPI0_CSR |= (0x0u<<1); //NCPHA = 0
	*p_SPI0_CSR |= (0x0u<<2); //CSNAAT = 0
	*p_SPI0_CSR |= (0x0u<<3); //CSAAT = 0

	*p_SPI0_CSR |= (0x0u<<4); //BITS = 0 (8-bit transfer)
	*p_SPI0_CSR |= (0x4u<<8); //SCBRR = 4 (MCK/4 baud rate div) (change to mask later)
}

void spi_select_slave_hardcoded(void) {
	*p_SPI0_MR &= ~(0b1111 << 16); //clear bit 16-19 in MR
	*p_SPI0_MR |= (0b111 >> (3)) << 16; //set bit 16 to 18 in SPI_MR. In this example Slave = 0
}

//read
uint32_t spi_rx(void) {
	uint32_t data = *p_SPI0_RDR;
	return data;
}

//write
void spi_tx(uint32_t data) {
	*p_SPI0_TDR = data;
}

uint32_t spi_rx_ready(void) {
	uint32_t RDRF = (*p_SPI0_SR & (0x1u<<0));
	return RDRF;
}

uint32_t spi_tx_ready(void) {
	uint32_t TXEMPTY = ~(*p_SPI0_SR & (0x1u << 9)); //inverted to make tx_ready when it's 0 (data in TDR)
	return TXEMPTY;
}
