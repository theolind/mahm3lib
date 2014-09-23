/**
 * \class test_pmc
 * \brief Power Managment Test Class (PMC)
 * \details This class is used to test the PMC using Unity
 * \author Felix Ruponen
 * \author Mattias Nilsson
 * \author Saeed Ghasemi
 * \version 0.1
 * \date 17 sep 2014
 */

#include "sam3x8e/global_definitions.h"
#include "unity/unity.h"
#include "test/test_pmc.h"

#include "sam3x8e/pmc.h"

void test_pmc_setup(){


}

void test_pmc_tear_down(){

	uint8_t status = pmc_status_peripheral_clock(ID_ADC);

	if(status == 1)
		pmc_stop_peripheral_clock(ID_ADC);
}

void test_pmc_reset(){
	test_pmc_setup();
	test_pmc_tear_down();
}

void test_pmc_status_peripheral_clock_when_inactive(void){
	test_pmc_reset();

	uint8_t status = pmc_status_peripheral_clock(ID_ADC);

	TEST_ASSERT_FALSE(status);

}

void test_pmc_status_peripheral_clock_when_active(void){
	test_pmc_reset();

	pmc_start_peripheral_clock(ID_ADC);

	uint8_t status = pmc_status_peripheral_clock(ID_ADC);

	TEST_ASSERT_TRUE(status);

}

void test_pmc_stop_peripheral_clock_when_successful(void){
	test_pmc_reset();

	pmc_start_peripheral_clock(ID_ADC);

	pmc_stop_peripheral_clock(ID_ADC);

	uint8_t status = pmc_status_peripheral_clock(ID_ADC);

	TEST_ASSERT_FALSE(status);
}

void test_pmc_start_peripheral_clock_when_successful(void){
	test_pmc_reset();

	pmc_start_peripheral_clock(ID_ADC);

	uint8_t status = pmc_status_peripheral_clock(ID_ADC);

	TEST_ASSERT(status);
}


