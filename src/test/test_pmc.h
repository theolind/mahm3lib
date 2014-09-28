/**
 * @brief Power Managment Test Class (PMC)
 * @details This class is used to test the PMC using Unity
 * @author Felix Ruponen
 * @author Mattias Nilsson
 * @author Saeed Ghasemi
 * @version 0.5
 * @date 17 sep 2014
 */

#ifndef TEST_PMC_H_
#define TEST_PMC_H_



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

#endif /* TEST_PMC_H_ */
