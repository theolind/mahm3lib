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

#include "unity.h"
#include "test_pmc.h"

#include "pmc.h"

void test_pmc_setup(){


}

void test_pmc_tear_down(){

	int8_t status = pmc_status_peripheral_clock(PMC_PERIPHERAL_ADC);

	if(status == 1)
		pmc_stop_peripheral_clock(PMC_PERIPHERAL_ADC);
}

void test_pmc_reset(){
	test_pmc_setup();
	test_pmc_tear_down();
}


void test_pmc(void){
	test_pmc_start_peripheral_clock_when_successful();
	test_pmc_status_peripheral_clock_when_inactive();
	test_pmc_status_peripheral_clock_when_active();
	test_pmc_stop_peripheral_clock_when_successful();
}


void test_pmc_status_peripheral_clock_when_inactive(void){
	test_pmc_reset();

	uint8_t status = pmc_status_peripheral_clock(PMC_PERIPHERAL_ADC);

	TEST_ASSERT_FALSE(status);

}

void test_pmc_status_peripheral_clock_when_active(void){
	test_pmc_reset();

	pmc_start_peripheral_clock(PMC_PERIPHERAL_ADC);

	uint8_t status = pmc_status_peripheral_clock(PMC_PERIPHERAL_ADC);

	TEST_ASSERT_TRUE(status);

}

void test_pmc_stop_peripheral_clock_when_successful(void){
	test_pmc_reset();

	pmc_start_peripheral_clock(PMC_PERIPHERAL_ADC);

	pmc_stop_peripheral_clock(PMC_PERIPHERAL_ADC);

	uint8_t status = pmc_status_peripheral_clock(PMC_PERIPHERAL_ADC);

	TEST_ASSERT_FALSE(status);
}

void test_pmc_start_peripheral_clock_when_successful(void){
	test_pmc_reset();

	pmc_start_peripheral_clock(PMC_PERIPHERAL_ADC);

	if((*p_PMC_PCSR1 & (0x01 << 5)) == (0x01 << 5))
	{
		TEST_ASSERT_TRUE(1);
	}
	else{
		TEST_FAIL();
	}
}
