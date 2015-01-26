/*
 * delay.c
 *
 * Author: Mattias Nilsson
 * Date: 21 October 2014
 */

#include "delay.h"

void delay_micros(uint32_t us){
	uint32_t i;
	for(i = 0; i < us; i++){
		wait();
	}
}

void delay_ms(uint32_t ms){
	delay_micros(ms * 1000);
}
