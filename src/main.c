#include "main.h"
#include "unity/unity_hw_setup.h"
#include "test_runner.h"
#include "sam3x8e/arduino_due.h"
#include "sam3x8e/pmc.h"
#include "sam3x8e/pio.h"
#include "sam3x8e/delay.h"
#include "sam3x8e/uart.h"
#include "sam3x8e/rtos/FreeRTOS.h"
#include "sam3x8e/rtos/task.h"

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

unsigned int led_num;


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	//run_tests();

	pmc_enable_peripheral_clock(ID_PIOB);
	pio_enable_pin(D13_PORT, D13);
	pio_conf_pin(D13_PORT, D13, 0, 0);

	uart_write_str("\r\nMain: Pre-task create \r\n");

	xTaskCreate(Thread1, NULL, configMINIMAL_STACK_SIZE, NULL, 4, NULL);
	//xTaskCreate(Thread2, NULL, configMINIMAL_STACK_SIZE, NULL, 4, NULL);

	uart_write_str("Main: Post-task create \r\n");

	vTaskStartScheduler();

	uart_write_str("Main: Post vTaskStartScheduler \r\n");

	while(1);

	return 0;
}

static void Thread2(void *arg) {

	for (;;) {

		led_num++;
		char test = (char) led_num;
		//uart_write_str(test);
		vTaskDelay((50L * configTICK_RATE_HZ) / 1000L); //50ms delay
	}


}

static void Thread1(void *arg) {

	for (;;) {
		pio_set_pin(D13_PORT, D13, 0);

		vTaskDelay((500L * configTICK_RATE_HZ) / 1000L); //50ms delay(100);

		pio_set_pin(D13_PORT, D13, 1);

		vTaskDelay((500L * configTICK_RATE_HZ) / 1000L); //50ms delay(100);
	}



}


void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	uart_write_str("vApplicationMallocFailedHook \r\n");
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
	uart_write_str("vApplicationIdleHook \r\n");
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	uart_write_str("vApplicationStackOverflowHook \r\n");
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This function will be called by each tick interrupt if
	configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
	added here, but the tick hook is called from an interrupt context, so
	code must not attempt to block, and only the interrupt safe FreeRTOS API
	functions can be used (those that end in FromISR()). */
	uart_write_str("vApplicationTickHook \r\n");
}
