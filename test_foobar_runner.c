/*
 * Unity - adapted for programming of the Atmel SAM3X8E (ARM Cortex-M3).
 *
 * Created by: Mathias Beckius
 * Date: 2014-09-07
 */

#include "unity.h"
#include "test_foobar.h"

// void runTest(UnityTestFunction test) {
// 	if (TEST_PROTECT()) {
// 		setUp();
// 		test();
// 	}
// 	if (TEST_PROTECT() && !TEST_IS_IGNORED) {
// 		tearDown();
// 	}
// }

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();
	
    Unity.TestFile = "test/test_foobar.c";
    UnityBegin();
    RUN_TEST(test_foobar, 10);
    
    UnityEnd();
	while (1);
    return 0;
}