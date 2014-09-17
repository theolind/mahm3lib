/*
 * pmc.h
 *
 *  Created on: 17 sep 2014
 *      Author: felix
 */

#ifndef PMC_H_
#define PMC_H_



typedef uint8_t error;

// Start peripheral clock
error pcm_start_peripheral_clk();

// Stop peripheral clock
error pcm_stop_peripheral_clk();

// Get peripheral clock status
error pcm_status_peripheral_clk();

// Set peripheral prescaler
error pcm_set_peripheral_prescaler();

// Set to sleep mode, provide wakeup method
error pcm_sleep();

// Set master clock
error pcm_set_master_clk();

#endif /* PMC_H_ */
