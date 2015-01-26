/*
 * eefc.c
 *
 * Author: 	Mathias Beckius
 *
 * Date:	12 October 2014
 */

#include "eefc.h"

void eefc_set_flash_wait_state(eefc_reg_t *eefc, uint32_t fsw) {
	eefc->EEFC_FMR = EEFC_FMR_SET_FWS(eefc->EEFC_FMR, fsw);
}
