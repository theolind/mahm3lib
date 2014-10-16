/*
 * PMC unit tests
 *
 * Author:	Mathias Beckius
 *
 * Date:	12 October 2014
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

/*
 * Initial test: PWM should be disabled.
 * Assuming no one other tests has fiddled with PWM,
 * the peripheral should be disabled!
 */
void test_pmc_PWM_disabled1(void) {
	TEST_ASSERT_FALSE(PMC->PMC_PCSR1 & (0x1u << (ID_PWM - 32)));
}

/*
 * Tests if 'pmc_enable_peripheral_clock()' is working.
 */
void test_pmc_enable_PWM(void) {
	// enable clock for PWM
	pmc_enable_peripheral_clock(ID_PWM);
	// The peripheral should be enabled by now!
	TEST_ASSERT_TRUE(PMC->PMC_PCSR1 & (0x1u << (ID_PWM - 32)));
}

/*
 * Tests if 'pmc_peripheral_clock_enabled()' is working.
 */
void test_pmc_PWM_enabled(void) {
	// The peripheral should be enabled by now!
	TEST_ASSERT_TRUE(pmc_peripheral_clock_enabled(ID_PWM));
}

/*
 * Tests if 'pmc_disable_peripheral_clock()' is working.
 */
void test_pmc_disable_PWM(void) {
	// disable clock for PWM
	pmc_disable_peripheral_clock(ID_PWM);
	// this should be false!
	TEST_ASSERT_FALSE((PMC->PMC_PCSR1 & (0x1u << (ID_PWM - 32))));
}

/*
 * Tests if 'pmc_peripheral_clock_enabled()' is working, once more.
 */
void test_pmc_PWM_disabled2(void) {
	// The peripheral should be disabled by now!
	TEST_ASSERT_FALSE(pmc_peripheral_clock_enabled(ID_PWM));
}
