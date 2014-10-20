/**
 * @file info.h
 * @brief An API for returning system information
 * @details This function allows implementation for easy setup of returning
 * system information and mainly the kernel version or the API version.
 * For easy use of this function, it is recommended to use a pin to generate an
 * interrupt to run this API-functions.
 * This API consists of a single header-file with an inline function that can
 * be used to output the kernel-version.
 * @pre The API will not handle its own dependencies. The user must initialize
 * and configure the UART.
 * @author Saeed Ghasemi
 * @date 11 okt 2014
 * @bug Tested and bugfree.
 */

/////////// MAKE YOUR CHANGES HERE ////////////
#define KERNEL_INFO		"Kernel name: mahm3lib\n\rKernel version: release3"
///////////////////////////////////////////////

#ifndef INFO_H_
#define INFO_H_

/**
 * This function will return the kernel name and version by means of the uart.
 */
inline void info_send_kernel_version(void);
inline void info_send_kernel_version(void){
	uart_write_str("\n\r");
	uart_write_str(KERNEL_INFO);
	uart_write_str("\n\r");
}

#endif /* INFO_H_ */
