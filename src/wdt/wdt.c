/*
 * wdt.c
 *
 * API for the Watchdog Timer.
 *
 * Author: Mathias Beckius
 * Date: September 21, 2014
 */

#include <inttypes.h>
#include "wdt.h"

// Watchdog Timer Mode Register
uint32_t *const p_WDT_MR = (uint32_t *) 0x400E1A54U;

void wdt_disable(void) {
	WDT_MR = WDDIS;
}
