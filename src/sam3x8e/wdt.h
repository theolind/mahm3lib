/**
* @file wdt.h
* @brief With the Watchdog API you can configure the Watchdog Timer
* @details Important! The API is currently very limited. There's only
* @details a function for disabling the Watchdog at the moment.
*
* @author Mathias Beckius
* @author Felix Ruponen
* @date 29 September, 2014
*
* @pre Initialize system clock.
*/

#ifndef WDT_H
#define WDT_H

#include <inttypes.h>

/// Watchdog Timer Base register
#define WDT	 ((wdt_reg_t *) 0x400E1A50U)

///\cond

// WDT_MR: Watchdog disable
#define WDT_MR_WDDIS (1 << 15)

typedef struct wdt_reg {
	// Control register, offset 0x0000
	uint32_t WDT_CR;
	// Mode Register, offset 0x0004
	uint32_t WDT_MR;
	// Status Register, offset 0x0008
	uint32_t WDT_SR;
} wdt_reg_t;

///\endcond

/**
 * Disables the Watchdog Timer.
 */
void wdt_disable(void);

#endif
