/*
 * delay.c
 *
 * Author: Mattias Nilsson
 * Date: 2 October 2014
 */

#include "delay.h"


void delay_micros(uint32_t us){
	// Print value through serial communication
	uint32_t us_1000, us_100, us_10, us_1;

	if(us < 10){
		delay_1(us);
	} else{
		us_1000 = (us - (us % 1000)) / 1000;
		us = (us - us_1000 * 1000);
		us_100 = (us - (us % 100)) / 100;
		us = (us - us_100 * 100);
		us_10 = (us - (us % 10)) / 10;
		us = (us - us_10 * 10);
		us_1 = us % 10;

		delay_1000(us_1000);
		delay_100(us_100);
		delay_10(us_10);
		delay_1(us_1);
	}




}



void delay_1000(uint32_t us_1000){
	volatile uint32_t i, j;

	for(i = 0; i < us_1000; i++){
		j = 0;
		while (j < 6000){
			__asm__ volatile("NOP\n" "NOP\n");
			j++;
		}
	}

}
void delay_100(uint32_t us_100){
	volatile uint32_t i, j;

	for(i = 0; i < us_100; i++){
		j = 0;
		while (j < 460){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n"
					"NOP\n"	"NOP\n" "NOP\n");
			j++;
		}
	}

}
void delay_10(uint32_t us_10){
	volatile uint32_t i, j;

	for(i = 0; i < us_10; i++){
		j = 0;
		while (j < 30){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n"
					"NOP\n" "NOP\n" "NOP\n"
					"NOP\n");
			j++;
		}
	}

}
void delay_1(uint32_t us_1){
	volatile uint32_t i, j;

	for (i = 0; i < us_1; i++){

		// For 2 microsecond
		if(us_1 > 1){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
		}

		// For 3 microseconds
		if(us_1 > 2){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n");
		}

		// For 4 microseconds
		if(us_1 > 3){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
			__asm__ volatile("NOP\n");
		}

		// For 5 microseconds
		if(us_1 > 4){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
		}

		// For 6 microseconds
		if(us_1 > 5){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
		}

		// For 7 microseconds
		if(us_1 > 6){
			__asm__ volatile("NOP\n" "NOP\n");
		}

		// For 8 microseconds
		if(us_1 > 7){
			__asm__ volatile("NOP\n" "NOP\n");
		}

		// For 9 microseconds
		if(us_1 > 8){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n");
		}
/*
				// Used only to make delay accurate
				if(us_1 > 100){
					__asm__ volatile("NOP\n");
				}

				// Used only to make delay accurate
				if(us_1 > 200 ){
					__asm__ volatile("NOP\n");
				}
				*/
	}

	/*for(i = 0; i < us_1; i++){
			__asm__ volatile("NOP\n" "NOP\n" "NOP\n"
					"NOP\n" "NOP\n" "NOP\n"
					"NOP\n" "NOP\n" "NOP\n");

	}*/

}



/*
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
*/


void delay_ms(uint32_t ms){
	delay_micros(ms * 1000);
}
