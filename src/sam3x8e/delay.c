/*
 * delay.c
 *
 * Author: Mattias Nilsson
 * Date: 2 October 2014
 */

#include "delay.h"

void delay_micros(uint32_t us){
	volatile uint32_t i;
	volatile uint32_t j;
		for (i = 0; i < us; i++){
			// For 1 microsecond
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n");

			// For 2 microseconds
			if(us > 1){
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n");

			}

			// For 3 microseconds
			if(us > 2){
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			}

			// For 4-10 microseconds
			if(us > 3){
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n");
			}

			// Used only to make delay accurate
			if(us > 100){
				__asm__ volatile("NOP\n");
			}

			// Used only to make delay accurate
			if(us > 200 ){
				__asm__ volatile("NOP\n");
			}

		}
}



void delay_ms(uint32_t ms){
	delay_micros(ms * 1000);
}
