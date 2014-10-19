/**
 * @brief TWI, Two Wire Interface
 *
 * @author Jonathan Bjarnason
 * @date 10 October 2014
 */

#include "twi.h"

uint8_t twi_master_init(twi_reg_t *twi, twi_settings_t *settings){

	twi_reset(twi);

	if(!(twi_set_clocks(twi, settings))){
		return 0;
	}

	// Set Master Disable bit
	twi->TWI_CR = TWI_CR_MSDIS;

	// Set Slave Disable bit
	twi->TWI_CR = TWI_CR_SVDIS;

	// Set Master Enable bit
	twi->TWI_CR = TWI_CR_MSEN;

	return 1;
}

uint8_t twi_master_read(twi_reg_t *twi, twi_packet_t *packet){
	uint32_t counter = 0;

	// Check for illegal values
	if(packet->data_length==0){
		return 0;
	}

	// Set read mode, slave address and internal address
	twi->TWI_MMR = 0;
	twi->TWI_MMR = TWI_MMR_MREAD(0x1u) | TWI_MMR_DADR(packet->chip) |
			((TWI_MMR_IADRSZ(packet->address_length)) & TWI_MMR_IADRSZ(0x3u));

	// Set internal address for remote chip
	twi->TWI_IADR = 0;
	twi->TWI_IADR = twi_convert_address(packet->address,
			packet->address_length);

	// Signal start of transfer
	twi->TWI_CR = TWI_CR_START;

	while (counter < packet->data_length) {
		if (twi->TWI_SR & TWI_SR_NACK) {
			return 0;
		}

		// If this is the last byte.
		if ((counter + 1) == packet->data_length) {
			// Signal end of transfer
			twi->TWI_CR = TWI_CR_STOP;
		}

		// If a new byte has been received since last read.
		if (twi->TWI_SR & TWI_SR_RXRDY) {
			// Put data from TWI_RHR in buffer variable and increment the
			// pointers address.
			*packet->buffer++ = twi->TWI_RHR;
			counter ++;
		}
	}

	// Wait for Transmission Completed flag to be set
	while (!(twi->TWI_SR & TWI_SR_TXCOMP));

	return 1;
}

uint8_t twi_master_write(twi_reg_t *twi, twi_packet_t *packet){
	uint32_t counter = 0;

	// Set write mode, slave address and internal address
	twi->TWI_MMR = 0;
	twi->TWI_MMR = TWI_MMR_MREAD(0x0u) | TWI_MMR_DADR(packet->chip) |
			(TWI_MMR_IADRSZ(packet->address_length) & TWI_MMR_IADRSZ(0x3u));

	/* Set internal address for remote chip */
	twi->TWI_IADR = 0;
	twi->TWI_IADR = twi_mk_addr(packet->address, packet->address_length);

	// Write bytes
	while(counter<(packet->data_length)){
		// If last byte has not been acknowledged
		if(twi->TWI_SR & TWI_SR_NACK){
			return 0;
		}

		// If data has been acknowledged
		if(twi->TWI_SR & TWI_SR_TXRDY){
			twi->TWI_THR = *packet->buffer++;
			counter ++;
		}
	}

	// Wait for last acknowledge
	while (1) {
		if (twi->TWI_SR & TWI_SR_NACK) {
			return 0;
		}

		if (twi->TWI_SR & TWI_SR_TXRDY) {
			break;
		}
	}

	// Signal end of transfer
	twi->TWI_CR = TWI_CR_STOP;

	// Wait for Transmission Completed flag to set
	while (!(twi->TWI_SR & TWI_SR_TXCOMP));

	return 1;
}

void twi_slave_init(twi_reg_t *twi, uint8_t slave_adress){

	twi_reset(twi);

	// Set Slave Address
	twi->TWI_SMR = TWI_SMR_SADR(slave_adress);

	// Set Master Disable bit
	twi->TWI_CR = TWI_CR_MSDIS;

	// Set Slave Disable bit
	twi->TWI_CR = TWI_CR_SVDIS;

	// Set Slave Enable bit
	twi->TWI_CR = TWI_CR_SVEN;
}

void twi_slave_read(twi_reg_t *twi, uint8_t *data){

	while(1){
		// If the slave address on the TWI line matches this slave device
		if(twi->TWI_SR & TWI_SR_SVACC){
			// If no general calls have been made. (Not yet implemented)
			if(!(twi->TWI_SR & TWI_SR_GACC)){
				// If slave is supposed to do a read and if TWI_RHR has
				// received a character since last read
				if((twi->TWI_SR & TWI_SR_SVREAD) &&
						(twi->TWI_SR & TWI_SR_RXRDY)){
					*data++ = (uint8_t) twi->TWI_RHR;
				}
			}
		}
		// If transmission is completed or slave access is finished
		else if((twi->TWI_SR & TWI_SR_EOSACC)||(twi->TWI_SR & TWI_SR_TXCOMP)){
			break;
		}
	}
}

void twi_slave_write(twi_reg_t *twi, uint8_t *data){

	while(1){
		// If the slave address on the TWI line matches this slave device
		if(twi->TWI_SR & TWI_SR_SVACC){
			// If no general calls have been made. (Not yet implemented)
			if(!(twi->TWI_SR & TWI_SR_GACC)){
				// If slave is supposed to do a write, TWI_THR is empty
				// and the last data has been sent and acknowledged
				if(!(twi->TWI_SR & TWI_SR_SVREAD) &&
						(twi->TWI_SR & TWI_SR_TXRDY)){
					twi->TWI_THR = *data++;
				}
			}
		}
		// If transmission is completed or slave access is finished
		else if((twi->TWI_SR & TWI_SR_EOSACC)||(twi->TWI_SR & TWI_SR_TXCOMP)){
			break;
		}
	}
}

uint32_t twi_convert_address(uint8_t *address, uint8_t address_length){
	uint32_t result = 0;

	if(address_length == 0){
		return result;
	}

	result = address[0];
	if(address_length == 1){
		return result;
	}

	result <<= 8;
	result |= address[1];
	if(address_length == 2){
		return result;
	}

	result <<= 8;
	result |= address[2];

	return result;
}

uint8_t twi_set_clocks(twi_reg_t *twi, twi_settings_t *settings){
	uint32_t clock_divider = 0;
	uint32_t clock_low_high_divider;

	if (settings->baudrate > TWI_FAST_MODE_SPEED) {
		return 0;
	}

	// Calculate clock low devider and clock high devider
	clock_low_high_divider = settings->baudrate / (settings->master_clk *
			raise_to_the_power_of(2 ,clock_divider)) -
			(4/raise_to_the_power_of(2 ,clock_divider));

	// clock_low_high_divider must fit in 8 bits,
	// clock_divider must fit in 3 bits
	while ((clock_low_high_divider > 0xFF) && (clock_divider < 7)) {
		clock_divider++;
		// Calculate clock low devider and clock high devider
		clock_low_high_divider = settings->baudrate / (settings->master_clk *
				raise_to_the_power_of(2 ,clock_divider)) -
				(4/raise_to_the_power_of(2 ,clock_divider));
	}

	// If clock_low_high_divider does not fit in 8 bits
	if(clock_low_high_divider > 0xFF){
		return 0;
	}

	// Set clock waveform generator register
	twi->TWI_CWGR = TWI_CWGR_CLDIV(clock_low_high_divider);
	twi->TWI_CWGR = TWI_CWGR_CHDIV(clock_low_high_divider);
	twi->TWI_CWGR = TWI_CWGR_CKDIV(clock_divider);

	return 1;
}

int raise_to_the_power_of(int base, int exponent){
	int result=1;
	for(int i=0; i<exponent; i++){
		result = result * base;
	}
	return result;
}

void twi_reset(twi_reg_t *twi){
	twi->TWI_CR = TWI_CR_SWRST;
	// twi->TWI_RHR;
}
