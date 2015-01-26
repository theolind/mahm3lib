/*
 * wdt.c
 *
 * API for the Watchdog Timer.
 *
 * Author: 	Mathias Beckius
 * 			Felix Ruponen
 * Date: 	29 September, 2014
 */

#include "wdt.h"

void wdt_disable(void) {
	WDT->WDT_MR = WDT_MR_WDDIS;
}
