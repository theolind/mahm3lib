/*
 * @file test_twi.c
 * @brief Two Wire Interface (TWI) unit tests
 * @details This class is used to test the capabilities of the TWI API
 *
 * @author Jonathan Bjarnason
 * @date 12 October 2014
 */

#ifndef TEST_TWI_H_
#define TEST_TWI_H_

//#define PHERIPHERAL_A 0

void test_twi_set_device_address(void);
void test_twi_set_internal_address(void);
void test_twi_set_clock_invalid_parameters(void);
void test_twi_set_clock_valid_parameters(void);
void test_twi_send_receive_SEMI_AUTOMATIC(void);

//void test_twi_init(void);

#endif
