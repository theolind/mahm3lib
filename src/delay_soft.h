/**
 * \class delay_soft
 * \brief Delay functions based on software and no hardware
 * \details Thisclass is used to make delays in the microsecond and millisecond range
 * \author Saeed Ghasemi
 * \version 0.1
 * \date 22 sep 2014
 * \pre There are two functions only and they are placed in the headerfile because they are inline-functions
 * \bug Caution: These functions are tested but not after integrating the PIO-API. Tests will follow.
 */


#ifndef DELAY_SOFT_H_
#define DELAY_SOFT_H_


//////////////////////////////////////////////////////////////////////////
// Function prototypes
volatile inline void timer_delay_Software_1us(float us); // changed from int32_t
volatile inline void timer_delay_Software_1us(float us){
	volatile uint32_t count; // changed from int32_t
	//count = (int32_t) (0.0 + 1.0*((float)us));
	//count = (uint32_t)(1.933199443 + 3.087132653*us); //replaced ((float)us) with us and changed final cast from int32_t
	count = (uint32_t)(1.416199443 + 3.087132653*us); //replaced ((float)us) with us and changed final cast from int32_t

	while (count != 0){
		count--;
	}
}



volatile inline void timer_delay_Software_1ms(uint32_t ms);
volatile inline void timer_delay_Software_1ms(uint32_t ms){
	volatile uint32_t count; // changed from int32_t

	while (count != 0){
		timer_delaySoftware_1us(1000);
		count--;
	}
}


#endif /* DELAY_SOFT_H_ */
