#include "main.h"
#include "unity/unity_hw_setup.h"
#include "test_runner.h"
#include "sam3x8e/chibios/ch.h"
#include "chconf.h"
#include "halconf.h"
#include "stdio.h"


/*
 * This is a periodic thread that does absolutely nothing except increasing
 * the seconds counter.
 */
static WORKING_AREA(waThread1, 128);
static WORKING_AREA(waThread2, 128);
static WORKING_AREA(waThread3, 128);

static msg_t Thread1(void *arg) {
	(void)arg;

	while (TRUE) {
		chThdSleepMilliseconds(1000);
	}
	return 0;
}

static msg_t Thread2(void *arg) {
	(void)arg;

	while (TRUE) {
		chThdSleepMilliseconds(1000);
	}
	return 0;
}

static msg_t Thread3(void *arg) {
	(void)arg;

	while (TRUE) {
		chThdSleepMilliseconds(500);
	}
	return 0;
}


int main(void) {
	// basic initialization of hardware and UART communication.
	unity_hw_setup();

	//run_tests();


  /*
   * System initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */

  chSysInit();

  /*
   * Creates the example thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);
  chThdCreateStatic(waThread3, sizeof(waThread3), NORMALPRIO, Thread3, NULL);

  while (1);

	return 0;
}
