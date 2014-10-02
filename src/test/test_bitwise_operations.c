/*
 * bitwise_operations unit tests
 *
 * Author:	Saeed Ghasemi
 *
 * Date:	01 October 2014
 */

#include "unity/unity.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/bitwise_operations.h"
#include "test_bitwise_operations.h"

void test_set_register(void) {
	uint32_t reg = 0;
	set_register(&reg);
	TEST_ASSERT_TRUE(reg == 0x00000000);
}

void test_get_register(void) {
	uint32_t reg = 0;
	get_register(&reg);
	TEST_ASSERT_TRUE(reg == 0x00000000);
	get_value_of_register();
	//get_section_in_register();

}
