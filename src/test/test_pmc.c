/*
 * PMC unit tests
 *
 * Author:	Mathias Beckius
 *
 * Date:	29 September 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "test/test_pmc.h"

/*
 * Initial test: PIOB should be disabled.
 * Assuming no one other tests has fiddled with PIOB,
 * the peripheral should be disabled!
 */
void test_pmc_PIOB_disabled1(void) {
	TEST_ASSERT_FALSE(PMC->PMC_PCSR0 & (0x1u << ID_PIOB));
}

/*
 * Tests if 'pmc_enable_peripheral_clock()' is working.
 */
void test_pmc_enable_PIOB(void) {
	// enable clock for PIOB
	pmc_enable_peripheral_clock(ID_PIOB);
	// The peripheral should be enabled by now!
	TEST_ASSERT_TRUE(PMC->PMC_PCSR0 & (0x1u << ID_PIOB));
}

/*
 * Tests if 'pmc_peripheral_clock_enabled()' is working.
 */
void test_pmc_PIOB_enabled(void) {
	// The peripheral should be enabled by now!
	TEST_ASSERT_TRUE(pmc_peripheral_clock_enabled(ID_PIOB));
}

/*
 * Tests if 'pmc_disable_peripheral_clock()' is working.
 */
void test_pmc_disable_PIOB(void) {
	// disable clock for PIOB
	pmc_disable_peripheral_clock(ID_PIOB);
	// this should be false!
	TEST_ASSERT_FALSE((PMC->PMC_PCSR0 & (0x1u << ID_PIOB)));
}

/*
 * Tests if 'pmc_peripheral_clock_enabled()' is working, once more.
 */
void test_pmc_PIOB_disabled2(void) {
	// The peripheral should be disabled by now!
	TEST_ASSERT_FALSE(pmc_peripheral_clock_enabled(ID_PIOB));
}
