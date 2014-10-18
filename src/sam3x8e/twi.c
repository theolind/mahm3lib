/**
 * @brief TWI, Two Wire Interface
 *
 * @author Jonathan Bjarnason
 * @date 10 October 2014
 */

#include "twi.h"

void twi_master_init(twi_reg_t *twi, twi_settings_t *settings){

	twi_reset(twi);

	twi_set_clocks(twi, settings);

	// Set Master Disable bit
	twi->TWI_CR = TWI_CR_MSDIS(SET_BIT);

	// Set Slave Disable bit
	twi->TWI_CR = TWI_CR_SVDIS(SET_BIT);

	// Set Master Enable bit
	twi->TWI_CR = TWI_CR_MSEN(SET_BIT);
}

void twi_master_read(twi_reg_t *twi, twi_packet_t *packet){
	uint32_t counter = packet->address_length;

}

void twi_master_write(twi_reg_t *twi, twi_packet_t *packet){

}

void twi_slave_init(twi_reg_t *twi, uint8_t slave_adress){

	twi_reset(twi);

	// Set Slave Address
	twi->TWI_SMR = TWI_SMR_SADR(slave_adress);

	// Set Master Disable bit
	twi->TWI_CR = TWI_CR_MSDIS(SET_BIT);

	// Set Slave Disable bit
	twi->TWI_CR = TWI_CR_SVDIS(SET_BIT);

	// Set Slave Enable bit
	twi->TWI_CR = TWI_CR_SVEN(SET_BIT);
}

void twi_slave_read(twi_reg_t *twi, uint8_t *data){

}

void twi_slave_write(twi_reg_t *twi, uint8_t *data){

}

void twi_write_byte(twi_reg_t *twi, uint8_t data){
	twi->TWI_THR = (data << 0);
}

uint8_t twi_read_byte(twi_reg_t *twi){
	return(twi->TWI_RHR & (0x11111111u << 0));
}

void twi_set_clocks(twi_reg_t *twi, const twi_settings_t *settings){
	uint32_t ckdiv = 0;
	uint32_t c_lh_div;

	if (settings->baudrate > 400000) {
		// return 0;
	}

	c_lh_div = settings->master_clk / (settings->baudrate * 2) - 4;

	// cldiv must fit in 8 bits, ckdiv must fit in 3 bits
	while ((c_lh_div > 0xFF) && (ckdiv < 7)) {
		// Increase clock divider
		ckdiv++;
		// Divide cldiv value
		c_lh_div /= 2;
	}

	/* set clock waveform generator register */
	twi->TWI_CWGR = (c_lh_div >> 7);
	twi->TWI_CWGR = (c_lh_div >> 15);
	twi->TWI_CWGR = (ckdiv >> 18);

	// return 1;
}

void twi_reset(twi_reg_t *twi){
	twi->TWI_CR = TWI_CR_SWRST(SET_BIT);
	// twi->TWI_RHR;
}
