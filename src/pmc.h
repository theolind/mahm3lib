/*
 * pmc.h
 *
 *  Created on: 17 sep 2014
 *      Author: felix
 */

#ifndef PMC_H_
#define PMC_H_



typedef uint8_t error;

error pcm_start_peripheral_clk();

error pcm_stop_peripheral_clk();

error pcm_status_peripheral_clk();

error pcm_set_peripheral_prescaler();

error pcm_sleep();

error pcm_choose_master_clk();

#endif /* PMC_H_ */
