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

#ifndef TEST_PMC_H_
#define TEST_PMC_H_

void test_pmc_PIOB_disabled(void);
void test_pmc_enabled_function_OK(void);
void test_pmc_disable_function_OK(void);


void test_pmc_start_peripheral_clock_when_successful(void);
void test_pmc_status_peripheral_clock_when_inactive(void);
void test_pmc_status_peripheral_clock_when_active(void);
void test_pmc_stop_peripheral_clock_when_successful(void);

void test_pmc_set_master_clock_when_successful(void);

void test_pmc_setup(void);
void test_pmc_tear_down(void);
void test_pmc_reset(void);
void test_pmc(void);
void test_pmc_status_peripheral_clock_when_inactive(void);
void test_pmc_status_peripheral_clock_when_active(void);

void test_pmc_enable_peripheral_clock(void);

#endif
