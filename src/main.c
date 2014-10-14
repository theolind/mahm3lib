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
#include "sam3x8e/rtos/semphr.h"

void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationTickHook( void );

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue.  The 200ms value is converted
to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS			( 200 / portTICK_PERIOD_MS )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH					( 1 )

/* Values passed to the two tasks just to check the task parameter
functionality. */
#define mainQUEUE_SEND_PARAMETER			( 0x1111UL )
#define mainQUEUE_RECEIVE_PARAMETER			( 0x22UL )

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	/* Create the queue. */
	xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( unsigned long ) );

		if( xQueue != NULL )
		{
			/* Start the two tasks as described in the comments at the top of this
			file. */
			xTaskCreate( Thread1,					/* The function that implements the task. */
			"Rx", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
			configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
			( void * ) mainQUEUE_RECEIVE_PARAMETER, /* The parameter passed to the task - just to check the functionality. */
			mainQUEUE_RECEIVE_TASK_PRIORITY, 		/* The priority assigned to the task. */
			NULL );									/* The task handle is not required, so NULL is passed. */


			xTaskCreate( Thread2,					/* The function that implements the task. */
			"Rx", 									/* The text name assigned to the task - for debug only as it is not used by the kernel. */
			configMINIMAL_STACK_SIZE, 				/* The size of the stack to allocate to the task. */
			( void * ) mainQUEUE_SEND_PARAMETER, /* The parameter passed to the task - just to check the functionality. */
			mainQUEUE_SEND_TASK_PRIORITY, 		/* The priority assigned to the task. */
			NULL );
			/* Start the tasks and timer running. */
			print_pmc_status();

			vTaskStartScheduler();
		}

		/* If all is well, the scheduler will now be running, and the following
		line will never be reached.  If the following line does execute, then
		there was insufficient FreeRTOS heap memory available for the idle and/or
		timer tasks	to be created.  See the memory management section on the
		FreeRTOS web site for more details. */
		for( ;; );

		return 0;

	return 0;
}

static void Thread1(void *arg) {

	pmc_enable_peripheral_clock(ID_PIOD);
	pio_enable_pin(D12_PORT, D12);
	pio_conf_pin(D12_PORT, D12, 0, 0);

	for (;;) {
		pio_set_pin(D12_PORT, D12, 0);
		vTaskDelay(400 / portTICK_PERIOD_MS);
		pio_set_pin(D12_PORT, D12, 1);
		vTaskDelay(400 / portTICK_PERIOD_MS);
	}
}

static void Thread2(void *arg) {

	pmc_enable_peripheral_clock(ID_PIOB);
	pio_enable_pin(D13_PORT, D13);
	pio_conf_pin(D13_PORT, D13, 0, 0);

	for( ;; ) {
		vTaskDelay(100 / portTICK_PERIOD_MS);
		pio_set_pin(D13_PORT, D13, 0);
		vTaskDelay(100 / portTICK_PERIOD_MS);
		pio_set_pin(D13_PORT, D13, 1);
	}
}

void print_pmc_status(void){

	for(char i = 0; i<45; i++){

		uart_write_str("ID");
		uart_write_char(i+48);
		uart_write_str(" : ");
		if(pmc_peripheral_clock_enabled(i)){
			uart_write_str("SUCCESS");
			uart_write_str("\r\n");
			}else{
			uart_write_str("FAIL");
			uart_write_str("\r\n");
		}
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
