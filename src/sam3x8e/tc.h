/**
 * @file tc.h
 * @brief TC - Timer Counter
 * @details This API is used to control the three independent hardware timers.
 * @pre Timer clocks must be enabled through PMC and their appropriate
 * channels must be configured to peripheral use with PIO.
 *
 * @author Andreas Drotth
 * @author Mattias Nilsson
 * @date 13 Oktober 2014
 */

#ifndef TC_H_
#define TC_H_

#include <inttypes.h>

// pointer to registers of TC, base address: 0x40080000
#define TC0 ((tc_reg_t *) 0x40080000U)
#define TC1 ((tc_reg_t *) 0x40084000U)
#define TC2 ((tc_reg_t *) 0x40088000U)

#define TC0_TCLK0	(0x00)
#define TC0_TCLK1	(0x40)
#define TC0_TCLK2	(0x80)
#define TC1_TCLK3	(0x00)
#define TC1_TCLK4	(0x40)
#define TC1_TCLK5	(0x80)
#define TC2_TCLK6	(0x00)
#define TC2_TCLK7	(0x40)
#define TC2_TCLK8	(0x80)

typedef struct {
	// Channel Control Register, offset 0x0000
	uint32_t TC_CCR;
	// Channel Mode Register, offset 0x0004
	uint32_t TC_CMR;
	// Stepper Motor Mode Register, offset 0x0008
	uint32_t TC_SMMR;
	// Reserved, offset 0x000C
	uint32_t reserved1;
	// Counter Value, offset 0x0010
	uint32_t TC_CV;
	// Register A, offset 0x0014
	uint32_t TC_RA;
	// Register B, offset 0x0018
	uint32_t TC_RB;
	// Register C, offset 0x001C
	uint32_t TC_RC;
	// Status Register, offset 0x0020
	uint32_t TC_SR;
	// Interrupt Enable Register, offset 0x0024
	uint32_t TC_IER;
	// Interrupt Disable Register, offset 0x0028
	uint32_t TC_IDR;
	// Interrupt Mask Register, offset 0x002C
	uint32_t TC_IMR;
	// Skip, offset 0x0030 - 0x00BC
	uint32_t skip[35];
	// Block Control Register, offset 0x00C0
	uint32_t TC_BCR;
	// Block Mode Register, offset 0x00C4
	uint32_t TC_BMR;
	// QDEC Interrupt Enable Register, offset 0x00C8
	uint32_t TC_QIER;
	// QDEC Interrupt Disable Register, offset 0x00CC
	uint32_t TC_QIDR;
	// QDEC Interrupt Mask Register, offset 0x00D0
	uint32_t TC_QIMR;
	// QDEC Interrupt Status Register, offset 0x00D4
	uint32_t TC_QISR;
	// Fault Mode Register, offset 0x00D8
	uint32_t TC_FM;
	// Reserved, offset 0x00DC - 0x00E0
	uint32_t reserved2[2];
	// Write Protection Mode Register, offset 0x00E4
	uint32_t TC_WPMR;
} tc_reg_t;

typedef struct {
	uint32_t example_setting;
	// ...
} tc_settings_t;

/**
 * Configures a specified counter with provided settings.
 * @param settings Settings for timer counter.
 * should be a struct of type tc_settings_t.
 */
void tc_set(tc_settings_t* tc_settings);

void tc_enable_clock(tc_reg_t *tc, uint32_t channel);

void tc_disable_clock(tc_reg_t *tc, uint32_t channel);

void tc_start_clock(tc_reg_t *tc, uint32_t channel);

void tc_stop_clock(tc_reg_t *tc, uint32_t channel);

uint32_t tc_read_counter_value(tc_reg_t * tc, uint32_t channel);

#endif
