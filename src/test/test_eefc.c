/*
 * EEFC unit tests
 *
 * Author:	Mathias Beckius
 *
 * Date:	12 October 2014
 */

#include "unity/unity.h"
#include "test_eefc.h"
#include "sam3x8e/eefc.h"

/*
 * This test is just checking if the right value was written to the registers.
 * Expected value for Flash Wait State is 4.
 */
void test_eefc_set_flash_wait_state(void) {
	uint32_t bit_mask = 0xFu << 8;
	uint32_t expected_value = 0x4u << 8;
	TEST_ASSERT_TRUE(((EEFC0->EEFC_FMR) & bit_mask) == expected_value);
	TEST_ASSERT_TRUE(((EEFC1->EEFC_FMR) & bit_mask) == expected_value);
}
