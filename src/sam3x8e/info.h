/**
 * @file info.h
 * @brief An API for returning system information
 * @details This function allows implementation for easy setup of returning
 * system information and mainly the kernel version or the API version.
 * For easy use of this function, it is recommended to use a pin to generate an
 * interrupt to run this API.
 * @author Saeed Ghasemi
 * @date 11 okt 2014
 * @bug
 */

#ifndef INFO_H_
#define INFO_H_
/////////// MAKE YOUR CHANGES HERE ///////////////
#define KERNEL_INFO		"Kernel name: mahm3lib\n\rKernel version: release3"
//////////////////////////////////////////////////

#ifndef UART_H_
#define UART_H_
#include "uart.h"
#endif

inline void info_get_kernel_version(void){
	uart_write_str("\n\r");
	uart_write_str(KERNEL_INFO);
}



#endif /* INFO_H_ */
