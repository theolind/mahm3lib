/**
 * @file eefc.h
 * @brief EEFC - Enhanced Embedded Flash Controller
 * @details This API is used to set the EEFC.
 * @details The API is very limited by the moment. Only functionality to
 * make a standard system initialization is implemented.
 * @post Initialize system clock
 *
 * @author Mathias Beckius
 * @date 15 October 2014
 */

#ifndef EEFC_H_
#define EEFC_H_

#include <inttypes.h>

/// @brief Pointer to registers EEFC0
#define EEFC0 ((eefc_reg_t *) 0x400E0A00U)
/// @brief Pointer to registers EEFC1
#define EEFC1 ((eefc_reg_t *) 0x400E0C00U)

///@cond

/*
 * Set specified bit levels in a register at specified position.
 * The bit mask should consist of a number of high bits.
 * This macro function could be of common use.....
 */
#define __SET_BIT_LEVELS(reg, levels, bit_mask, pos)	\
	((reg & ~((bit_mask) << (pos))) | ((levels) << (pos)))

#define EEFC_FMR_SET_FWS(reg, bits)	\
	__SET_BIT_LEVELS(reg, bits, 0xFu, 8)

/*
 * Mapping of EEFC registers
 */
typedef struct eefc_reg {
	// Flash Mode Register, offset 0x0000
	uint32_t EEFC_FMR;
	// Flash Command Register, offset 0x0004
	uint32_t EEFC_FCR;
	// Flash Status Register, offset 0x0008
	uint32_t EEFC_FSR;
	// Flash Result Register, offset 0x000C
	uint32_t EEFC_FRR;
} eefc_reg_t;

///@endcond

/**
 * Set Flash Wait State, by defining the number of cycles
 * for read and write operations: FWS + 1
 * @param eefc Pointer to EEFC peripheral (EEFC0 or EEFC1)
 * @param fsw Flash Wait State (FSW)
 * @post Initialize system clock
 */
void eefc_set_flash_wait_state(eefc_reg_t *eefc, uint32_t fsw);

#endif
