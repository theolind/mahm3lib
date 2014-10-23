/*
 * Timer Counter (TC) unit tests
 *
 * Author: Andreas Drotth, Mattias Nilsson
 * Date: 20 Oktober 2014
 */

#include "sam3x8e/tc.h"

void test_tc_conf_channel(void);
void test_tc_conf_block(void);
void test_tc_enable_clock(void);
void test_tc_disable_clock(void);
void test_tc_start_clock(void);
void test_tc_counter_stopped(void);
void test_tc_read_counter_value(void);
void test_tc_sync(void);
void test_register(void);
