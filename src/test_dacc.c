#include "test_dacc.h"

void test_dacc_channel_0_enable(){
	TEST_ASSERT_TRUE(dacc_enable_channel(DACC_CHANNEL_0));
}

void test_dacc_channel_1_enable(){
	TEST_ASSERT_TRUE(dacc_enable_channel(DACC_CHANNEL_1));
}
