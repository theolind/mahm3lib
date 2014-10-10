/**
 * @author Jonathan Bjarnason
 * @version 0.1
 * @date 10 October 2014
 *
 * @brief First draft of the TWI interface
 */

#ifndef TWI_H_
#define TWI_H_

#include <inttypes.h>

// Base addresses to TWI registers
#define TWI0 ((spi_reg_t *) 0x4008C000U)
#define TWI1 ((spi_reg_t *) 0x40090000U)

// Mapping of TWI registers
typedef struct twi_reg_t {
	uint32_t TWI_CR;		//0x00, control register
	uint32_t TWI_MMR;		//0x04, master mode register
	uint32_t TWI_SMR;		//0x08, slave mode register
	uint32_t TWI_IADR;		//0x0C, internal address register
	uint32_t TWI_CWGR;		//0x10, waveform generator register
	uint32_t reserved[2];	//0x14-0x1C, reserved
	uint32_t TWI_SR;		//0x20, status register
	uint32_t TWI_IER;		//0x24, interrupt enable register
	uint32_t TWI_IDR;		//0x28, interrupt disable register
	uint32_t TWI_IMR;		//0x2C, interrupt mask register
	uint32_t TWI_RHR;		//0x30, receive holding register
	uint32_t TWI_THR;		//0x34, transmit holding register
} spi_reg_t;

#endif
