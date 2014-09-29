
/**
 * \class delay_soft
 * \brief Software delay API
 * \details Delay functions based on software and no hardware.
 * \details This class is used to make delays in the microsecond and millisecond
 * \details range.
 *
 * \author Saeed Ghasemi
 *
 * \version 0.2
 *
 * \date 25 sep 2014
 *
 * \pre The API contains two functions for delaying. One for microseconds and
 * \pre one for milliseconds.
 * \pre This library introduces a software implementation of two delay functions
 * \pre that do not rely on any hardware peripheral or internal clocks to
 * \pre operate. The solution implements a loop written in C code and it only
 * \pre needs the processor clock speed to be exactly 84MHz such as the one
 * \pre running the ARM Cortex-M3 MCU that this API is developed for. There are
 * \pre two functions included in the API. There is one for microseconds and
 * \pre one for milliseconds as shown below. Both functions must be invoked
 * \pre with integers or float without any fractional part.
 * \pre
 * \pre Word of caution: There are disadvantages and shortcomings to a software
 * \pre delay. Such delay use CPU-time and make the code inefficient, at the
 * \pre same time interrupts will interfere with the length of the delay and
 * \pre their use should therefore be avoided in timing critical applications.
 * \pre This is however not entirely avoided using hardware timers either.
 *
 * \bug Version 0.1 had 3 bugs that are fixed in this version. This version is bug free.
 */


#ifndef DELAY_SOFT_H_
#define DELAY_SOFT_H_


//////////////////////////////////////////////////////////////////////////
// Function prototypes

inline void timer_delay_software_us(float us);
inline void timer_delay_software_ms(uint32_t ms);

//////////////////////////////////////////////////////////////////////////

/**
 * This function will delay in microseconds.
 * This function is tested to perform fairly accurate within 15 to 20000 us.
 * It can be used perfectly down to 15 us. Below this value there
 * may be fluctuation around the specified value. The maximum fluctuation is
 * close to 1.5us. The lowest delay achievable is 2.6 us with inputs in the
 * range 0-3.
 *
 * @param us Amount of time in us to delay
 */
inline void timer_delay_software_us(float us){
	volatile uint32_t count; // Volatile to avoid compiler optimization
//	count = (uint32_t)(0.322922871*us); // Calibration function
//	count = (uint32_t)(3.22922871*us); // Calibration function
	count = (uint32_t)(7.99618534*us); // Calibration function

	while (count != 0){
		count--;
	}
}


/**
 * This function will delay in milliseconds.
 * The function is tested to perform fairly accurate within 1 to 100 ms with an
 * accuracy of maximum 300 us in this range which yields 0.3% deviation at
 * 100ms delay.
 *
 * @param ms Amount of time in ms to delay
 */
inline void timer_delay_software_ms(uint32_t ms){
	volatile uint32_t count = ms;
	while (count != 0){
		timer_delay_software_us(1000);
		count--;
	}
}


#endif /* DELAY_SOFT_H_ */
