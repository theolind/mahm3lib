/**
 * @file

 * @author Felix Ruponen
 * @author Mattias Nilsson
 * @author Saeed Ghasemi
 * @version 0.2
 * @date 17 sep 2014
 */

#ifndef PMC_H_
#define PMC_H_

#include "global_entities.h"


// Start peripheral clock
uint8_t pmc_start_peripheral_clock(uint8_t ID_);

// Stop peripheral clock
uint8_t pmc_stop_peripheral_clock(uint8_t ID_);

// Get peripheral clock status
uint8_t pmc_status_peripheral_clock(uint8_t ID_);



#endif /* PMC_H_ */
