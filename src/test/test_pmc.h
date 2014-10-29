/*
 * PMC unit tests
 *
 * Author:	Mathias Beckius
 *
 * Date:	12 October 2014
 */

#ifndef TEST_PMC_H_
#define TEST_PMC_H_

void test_pmc_PIOB_disabled1(void);
void test_pmc_enable_PIOB(void);
void test_pmc_PIOB_enabled(void);
void test_pmc_disable_PIOB(void);
void test_pmc_PIOB_disabled2(void);

void test_pmc_PWM_disabled1(void);
void test_pmc_enable_PWM(void);
void test_pmc_PWM_enabled(void);
void test_pmc_disable_PWM(void);
void test_pmc_PWM_disabled2(void);

#endif
