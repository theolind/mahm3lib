/*
 * info.c
 *
 * Author: Saeed Ghasami
 * Date: 23 Oktober 2014
 */

#include "info.h"

void info_send_kernel_version(void){
	uart_write_str("\n\r");
	uart_write_str(KERNEL_INFO);
	uart_write_str("\n\r");
}
