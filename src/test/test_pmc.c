/*
 * PMC unit tests
 *
 * Author:	Felix Ruponen
 * 			Mattias Nilsson
 * 			Saeed Ghasemi
 * 			Mathias Beckius
 *
 * Date:	29 September 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "test/test_pmc.h"

/*
void test_pmc_setup() {
}

void test_pmc_tear_down(){

	uint8_t status = pmc_peripheral_clock_enabled(ID_ADC);

	if(status == 1)
		pmc_disable_peripheral_clock(ID_ADC);
}

void test_pmc_reset(){
	test_pmc_tear_down();
	test_pmc_setup();
}

void test_pmc(){
	test_pmc_start_peripheral_clock_when_successful();
	test_pmc_status_peripheral_clock_when_inactive();
	test_pmc_status_peripheral_clock_when_active();
	test_pmc_stop_peripheral_clock_when_successful();
}
*/

void test_pmc_status_peripheral_clock_when_inactive(void){
	test_pmc_reset();

	uint8_t status = pmc_peripheral_clock_enabled(ID_ADC);

	TEST_ASSERT_FALSE(status);

}

void test_pmc_status_peripheral_clock_when_active(void){
	uint8_t status;
	test_pmc_reset();

	status = pmc_peripheral_clock_enabled(ID_ADC);
	TEST_ASSERT_FALSE(status);

	pmc_enable_peripheral_clock(ID_ADC);

	status = pmc_peripheral_clock_enabled(ID_ADC);
	TEST_ASSERT_TRUE(status);
}

void test_pmc_stop_peripheral_clock_when_successful(void){
	uint8_t status;
	test_pmc_reset();

	pmc_enable_peripheral_clock(ID_ADC);

	status = pmc_peripheral_clock_enabled(ID_ADC);
	TEST_ASSERT_TRUE(status);

	pmc_disable_peripheral_clock(ID_ADC);

	status = pmc_peripheral_clock_enabled(ID_ADC);
	TEST_ASSERT_FALSE(status);
}

void test_pmc_start_peripheral_clock_when_successful(void){
	uint8_t status;
	test_pmc_reset();

	status = pmc_peripheral_clock_enabled(ID_ADC);
	TEST_ASSERT_FALSE(status);

	pmc_enable_peripheral_clock(ID_ADC);

	status = pmc_peripheral_clock_enabled(ID_ADC);
	TEST_ASSERT_TRUE(status);

	pmc_disable_peripheral_clock(ID_ADC);
}

void test_pmc_set_master_clock_when_successful(void) {
	test_pmc_reset();

	//uint8_t status = pmc_set_master_clock(PMC_CSS_SLOW_CLK);

	TEST_ASSERT(1);
}

/*
 * Initial test: PIOB should be disabled.
 * Assuming no one other tests has fiddled with PIOB,
 * the peripheral should be disabled!
 */
void test_pmc_PIOB_disabled(void) {
	TEST_ASSERT_FALSE(pmc_peripheral_clock_enabled(ID_PIOB));
}

/*
 * Tests if:
 * 	- 'pmc_peripheral_clock_enabled()' is reliable
 * 	- 'pmc_enable_peripheral_clock()' does work (BONUS!)
 *
 * The test will be successful if the following conditions are satisfied:
 * 		1) 	compare register value with function output, should be equivalent!
 * 		2) 	enable clock, compare old register value with function output,
 * 			should not be equivalent!
 * 		3) 	compare current register value with function output,
 * 			should be equivalent!
 */
void test_pmc_enabled_function_OK(void) {
	// for storing register values
	uint8_t reg;

	// read register
	reg = (uint8_t) (PMC->PMC_PCSR0 & (0x1u << ID_PIOB));
	// This should be true!
	TEST_ASSERT_TRUE(reg == pmc_peripheral_clock_enabled(ID_PIOB));

	// enable clock for PIOB
	//pmc_enable_peripheral_clock(ID_PIOB);
	PMC->PMC_PCER0 = (0x1u << ID_PIOB);
	// Comparing with old register value, this should be false!
	TEST_ASSERT_FALSE(reg == pmc_peripheral_clock_enabled(ID_PIOB));

	// read register
	reg = (uint8_t) (PMC->PMC_PCSR0 & (0x1u << ID_PIOB));
	// This should be true!
	TEST_ASSERT_TRUE(reg == pmc_peripheral_clock_enabled(ID_PIOB));
}

/*
 * Tests if 'pmc_disable_peripheral_clock()' is working.
 */
void test_pmc_disable_function_OK(void) {
	// disable clock for PIOB
	pmc_disable_peripheral_clock(ID_PIOB);
	// this should be false!
	TEST_ASSERT_FALSE(pmc_peripheral_clock_enabled(ID_PIOB));
}
