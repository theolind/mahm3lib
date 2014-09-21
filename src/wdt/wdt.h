/**
* @file wdt.h
*
* @brief Watchdog Timer
* @details With the Watchdog API you can setup the Watchdog Timer.<br>
* @details Important! The API is currently very limited. There's only a
* @details a function for disabling the Watchdog.
*
* @author Mathias Beckius
* @date September 21, 2014
*
* @pre Initialize system clock.
*/

#ifndef WDT_H
#define WDT_H

// Watchdog Timer Mode Register
#define WDT_MR	(*p_WDT_MR)

// WDT_MR: Watchdog disable
#define WDDIS	(1 << 15)

/**
 * @fn Disables the Watchdog Timer.
 */
void wdt_disable(void);

#endif
