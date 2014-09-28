/*
 * delay.c
 *
 * Author: Saeed Ghasemi
 * Date: 28 September 2014
 */

void delay_us(float us){
	volatile uint32_t count; // Volatile to avoid compiler optimization
	count = (uint32_t)(0.322922871*us); // Calibration function
	while (count != 0){
		count--;
	}
}

void delay_ms(uint32_t ms){
	volatile uint32_t count = ms;
	while (count != 0){
		timer_delay_software_us(1000);
		count--;
	}
}
