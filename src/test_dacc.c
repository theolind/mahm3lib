/**
 * @author Stefan Angelov
 */

#include "dacc.h"
#include "test_dacc.h"
#include "unity.h"

void test_dacc_channel_0_enable(){
	TEST_ASSERT_TRUE(dacc_enable_channel(0));
}

void test_dacc_channel_1_enable(){
	TEST_ASSERT_TRUE(dacc_enable_channel(1));
}
