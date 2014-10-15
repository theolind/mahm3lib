/*
 * stackoverflow.h
 *
 *  Created on: Oct 15, 2014
 *      Author: Prince
 */

#ifndef STACKOVERFLOW_H_
#define STACKOVERFLOW_H_

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

void vApplicationMallocFailedHook(void);
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName);
void vApplicationTickHook(void);

#endif /* STACKOVERFLOW_H_ */
