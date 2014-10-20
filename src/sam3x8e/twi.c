/*
 * twi.c
 *
 * TWI, Two Wire Interface
 *
 * Authors:	Jonathan Bjarnason
 * 			Mathias Beckius
 *
 * Date:	20 October 2014
 *
 * Only a part of the API is tested and also working!
 */

#include "twi.h"

void twi_set_device_address(twi_reg_t *twi, uint32_t dadr, uint32_t iadrsz) {
	twi->TWI_MMR = 0;
	// set device address of slave
	twi->TWI_MMR = 	TWI_MMR_DADR(dadr) |
	// specify size of the slave's internal addresses
					TWI_MMR_IADRSZ(iadrsz);
}

void twi_set_internal_address(twi_reg_t *twi, uint32_t iadr) {
	twi->TWI_IADR = 0;
	twi->TWI_IADR = TWI_IADR(iadr);
}

uint8_t twi_set_clock(twi_reg_t *twi, uint32_t bus_speed, uint32_t mck) {
	uint32_t freq_ratio = TWI_CWGR_FREQ_RATIO(bus_speed, mck);
	// Clock Low Divider (half of the bus clock period)
	uint32_t cldiv;
	// Clock Divider
	uint32_t ckdiv = 0;

	/*
	 * Invalid parameters?
	 * 	- desired bus speed to high?
	 * 	- Master Clock to small in relation to Bus Speed?
	 */
	if ((bus_speed > TWI_FAST_MODE_SPEED) ||
		(freq_ratio < TWI_CWGR_MIN_FREQ_RATIO)) {
		return 1;	// indicate "failure" !
	}

	/*
	 * Calculate Clock Low Divider, which must fit within 8 bits.
	 * If the value doesn't fit, then the Clock Divider is increased.
	 * Important! Clock Divider can't be larger than 3 bits!
	 */
	while (1) {
		cldiv = (freq_ratio - TWI_CWGR_MIN_FREQ_RATIO) >> ckdiv;
		// does Clock Low Divider fit within 8 bits?
		if (cldiv <= TWI_CWGR_CLDIV_MAX_VALUE) {
			break;		// cancel further calculation!
		}

		ckdiv++;
		// Clock Divider to large? (invalid parameters)
		if (ckdiv > TWI_CWGR_CKDIV_MAX_VALUE) {
			return 1;	// indicate "failure" !
		}
	}

	// Set clock waveform generator register
	twi->TWI_CWGR = TWI_CWGR_CLDIV(cldiv) | TWI_CWGR_CHDIV(cldiv) |
					TWI_CWGR_CKDIV(ckdiv);

	// indicate "success" !
	return 0;
}

void twi_init_master(twi_reg_t *twi) {
	// disable Slave Mode
	twi->TWI_CR = TWI_CR_SVDIS;
	// enable Master Mode
	twi->TWI_CR = TWI_CR_MSEN;
}
/*
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
*/
uint8_t twi_write_master(twi_reg_t *twi, uint8_t *buffer, uint32_t length) {
	uint32_t status;
	uint32_t i;

	// set Master Write Direction
	twi->TWI_MMR |= TWI_MMR_MASTER_WRITE;
	// write bytes
	for (i = 0; i < length; i++) {
		status = twi->TWI_SR;
		// If last byte has not been acknowledged
		if (status & TWI_SR_NACK) {
			return 1; // indicate "failure"
		}
		// ready to send data?
		if (status & TWI_SR_TXRDY) {
			twi->TWI_THR = *(buffer + i);
		}
	}

	// Wait for last acknowledge
	while (1) {
		status = twi->TWI_SR;
		// If last byte has not been acknowledged
		if (status & TWI_SR_NACK) {
			return 1; // indicate "failure"
		}
		// ready to send data?
		if (status & TWI_SR_TXRDY) {
			break;
		}
	}
	// send STOP command
	twi->TWI_CR = TWI_CR_STOP;
	// Wait for Transmission Completed flag to set
	while (!(twi->TWI_SR & TWI_SR_TXCOMP));

	// indicate "success"
	return 0;
}

void twi_init_slave(twi_reg_t *twi, uint8_t slave_address) {
	twi->TWI_SMR = 0;
	// set Slave Address
	twi->TWI_SMR = TWI_SMR_SADR(slave_address);
	// disable Master Mode
	twi->TWI_CR = TWI_CR_MSDIS;
	// enable Slave Mode
	twi->TWI_CR = TWI_CR_SVEN;
}

void twi_read_slave(twi_reg_t *twi, uint8_t *buffer, uint32_t *length) {
	uint32_t status;
	*length = 0;
	while (1) {
		status = twi->TWI_SR;
		// If the slave address on the TWI line matches this slave device
		if (status & TWI_SR_SVACC) {
			// If general calls have been made (Not yet implemented!)
			if (status & TWI_SR_GACC) {
			} else { // no general call....
				/*
				 * If slave is supposed to do a read and if TWI_RHR has
				 * received a character since last read.
				 */
				if ((status & TWI_SR_SVREAD) && (status & TWI_SR_RXRDY)) {
					// read character
					*buffer = (uint8_t) twi->TWI_RHR;
					buffer++;
					(*length)++;
				}
			}
		}
		// If transmission is completed or slave access is finished
		else if ((status & TWI_SR_EOSACC) || (status & TWI_SR_TXCOMP)) {
			break;
		}
	}
}
/*
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
*/
void twi_reset(twi_reg_t *twi) {
	twi->TWI_CR = TWI_CR_SWRST;
}
