/*
 * delay.c
 *
 * Author: Saeed Ghasemi, Andreas Drotth
 * Date: 28 September 2014
 */

#include "delay.h"

void delay_micros(uint32_t us){
	for (uint32_t i = 0; i < us; i++){
		uint8_t j = 0;
		while (j < 6){
			__asm__ volatile("NOP\n\t" "NOP\n\t" "NOP\n\t" "NOP\n\t");
			j++;
		}
	}

}

void delay_ms(uint32_t ms){
	delay_micros(ms * 1000);
}

/*
void delay_us(float us) {
	volatile uint32_t count; // Volatile to avoid compiler optimization
	count = (uint32_t)(0.322922871*us); // Calibration function
	while (count != 0){
		count--;
	}
}

void delay_ms(uint32_t ms) {
	volatile uint32_t count = ms;
	while (count != 0){
		delay_us(1000);
		count--;
	}
}
*/
