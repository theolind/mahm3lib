/*
 * wdt.c
 * API for the Watchdog Timer.
 *
 * Author: Mathias Beckius
 * Date: September 21, 2014
 */

#include "wdt.h"

void wdt_disable(void) {
	WDT->WDT_MR = WDT_MR_WDDIS;
}
