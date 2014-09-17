/*
 * test_pcm.c
 *
 *  Created on: 17 sep 2014
 *      Author: felix
 */

#include "unity.h"
#include "test_pmc.h"

#include "pmc.h"


void test_pmc(void){
	test_pmc_start_peripheral_clock();
}

void test_pmc_start_peripheral_clock(){

	pmc_start_peripheral_clock(PMC_PERIPHERAL_ADC);

	uint8_t status = 0;

	if((*p_PMC_PCSR1 & (0x01 << 5)) == (0x01 << 5))
	{
		status = 1;
		TEST_ASSERT_TRUE(1);
	}
	else{
		TEST_FAIL();
	}
}
