/**
 * @file info.h
 * @brief An API for returning system information
 * @details This function allows implementation for easy setup of returning
 * system information and mainly the kernel version or the API version.
 *
 * @pre The user must initialize and configure the UART.
 * @author Saeed Ghasemi
 * @date 23 Oktober 2014
 */

#ifndef INFO_H_
#define INFO_H_

#include "sam3x8e/uart.h"

/// The version output can be changed here
#define KERNEL_INFO		"Kernel name: mahm3lib\n\rKernel version: release4"

/**
 * This function will return the kernel name and version by means of the uart.
 */
void info_send_kernel_version(void);

#endif
