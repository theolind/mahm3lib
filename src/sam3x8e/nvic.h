/**
 * @file
 * @brief NVIC - Nested Vectored Interrupt Controller
 * @details This is a simplistic implementation of NVIC just to be able to
 * enable and disable interrupts for various controllers.
 * @author Saeed Ghasemi
 * @date 29 September 2014
 *
 */

#ifndef NVIC_H_
#define NVIC_H_

#include <inttypes.h>

/**
 * The registers for the NVIC are placed far from each other. This is the
 * address for the first register. The rest are defined as offsets to this one.
 */
#define NVIC		((nvic_reg_t *) 0xE000E100U)

///@cond
/**
 * Mapping of NVIC registers
 * NVIC is not a typical peripheral and does not have a typical register
 * mapping. However, in the following I have tried to create the conventional
 * register mapping with huge reserved register-ranges.
 * (See page 157 in datasheet)
 */
typedef struct {
	uint32_t NVIC_ISER0;///< NVIC Set-Enable Register 0, (Read/Write)
	uint32_t NVIC_ISER1;///< NVIC Set-Enable Register 1, (Read/Write)
	uint32_t reserved1[31];

	uint32_t NVIC_ICER0;///< NVIC Clear-Enable Register 0, (Read/Write)
	uint32_t NVIC_ICER1;///< NVIC Clear-Enable Register 1, (Read/Write)
	uint32_t reserved2[31];

	uint32_t NVIC_ISPR0;///< NVIC Set-pending Register 0, (Read/Write)
	uint32_t NVIC_ISPR1;///< NVIC Set-pending Register 1, (Read/Write)
	uint32_t reserved3[31];

	uint32_t NVIC_ICPR0;///< NVIC Clear-pending Register 0, (Read/Write)
	uint32_t NVIC_ICPR1;///< NVIC Clear-pending Register 1, (Read/Write)
	uint32_t reserved4[31];

	uint32_t NVIC_IABR0;///< NVIC Active Bit Registers Register 0, (Read only)
	uint32_t NVIC_IABR1;///< NVIC Active Bit Registers Register 1, (Read only)
	uint32_t reserved5[63];

	uint32_t NVIC_IPR0;///< NVIC Priority Register 0, (Read/Write)
	uint32_t NVIC_IPR1;///< NVIC Priority Register 1, (Read/Write)
	uint32_t reserved6[697];

	uint32_t NVIC_STIR;///< NVIC Software Trigger Interrupt Register, (Read only)
} nvic_reg_t;
///@endcond

///@{
/**
 * This function will enable the interrupt-line to the NVIC for the given
 * peripheral indicated by peripheral id.
 *
 * @param peripheral_id The id of the peripheral.
 * (Use prefix: ID_ to choose between predefined values)
 * @return error, 1 = SUCCESS, 0 = FAIL
 */
uint8_t nvic_enable_interrupt(uint8_t peripheral_id);
/**
 * This function will disable the interrupt-line to the NVIC for the given
 * peripheral indicated by peripheral id.
 *
 * @param peripheral_id The id of the peripheral.
 * (Use prefix: ID_ to choose between predefined values)
 * @return error, 1 = SUCCESS, 0 = FAIL
 */
uint8_t nvic_disable_interrupt(uint8_t peripheral_id);
///@}


#endif /* NVIC_H_ */
