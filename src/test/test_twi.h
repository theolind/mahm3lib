/*
 * Two Wire Interface (TWI) unit tests
 *
 * Authors:	Jonathan Bjarnason
 * 			Mathias Beckius
 *
 * Date:	20 October 2014
 */

#ifndef TEST_TWI_H_
#define TEST_TWI_H_

void test_twi_set_device_address(void);
void test_twi_set_internal_address(void);
void test_twi_set_clock_invalid_parameters(void);
void test_twi_set_clock_valid_parameters(void);
void test_twi_init_slave(void);
void test_twi_send_receive_SEMI_AUTOMATIC(void);

#endif
