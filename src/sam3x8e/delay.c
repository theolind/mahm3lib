/*
 * delay.c
 *
 * Author: Mattias Nilsson
 * Date: 2 October 2014
 */

#include "delay.h"

void delay_micros(uint32_t us){
	volatile uint32_t i;
		for (i = 0; i < us; i++){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n");

			if(us >1 && us <= 5){
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			} else{
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
				__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			}
		}
}


void delay_ms(uint32_t ms){
	delay_micros(ms * 1000);
}
