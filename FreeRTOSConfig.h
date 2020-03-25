/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 *
 *   1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "Bridge_Freedom-metal_FreeRTOS.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/
#define configCLINT_BASE_ADDRESS		MTIME_CTRL_ADDR
#define configUSE_PREEMPTION			1
#define configUSE_IDLE_HOOK			0
#define configUSE_TICK_HOOK			0
#define configCPU_CLOCK_HZ			( MTIME_RATE_HZ ) 
/* 
 * configTICK_RATE_HZ indicate the frequency in HZ of the Tick.
 * On some CPU having a configTICK_RATE_HZ too high could induce scheduling time consuption
 * to high, then the task will not have time to run.
 * 
 * configTICK_RATE_HZ = 100 means a Tick every 10ms.
 */
#define configTICK_RATE_HZ			( ( TickType_t ) 100 )
#define configMAX_PRIORITIES			( 7 )
/*
 * configMINIMAL_STACK_SIZE must be a value greater than the stack use by 
 * the minimal task + the sizeof the register saved.
 * The size of the register is differrent from a core to another, e.g. on RiscV
 * it could be 32 base register + 32 register for FPU and some other for the
 * specific extensions.
 */
//#define configMINIMAL_STACK_SIZE		( ( size_t ) 164 )
#define configMINIMAL_STACK_SIZE		( ( size_t ) 256 )

/*
 * ucHeap buffer is defined by the application and store into section .heap with freedom metal
 * so configAPPLICATION_ALLOCATED_HEAP must be set to 1
 */
#define configAPPLICATION_ALLOCATED_HEAP 	1

#define configTOTAL_HEAP_SIZE          		( ( size_t ) 2048 * sizeof( size_t ) )

#define configMAX_TASK_NAME_LEN			( 16 )
#define configUSE_TRACE_FACILITY		1
#define configUSE_16_BIT_TICKS			0
#define configIDLE_SHOULD_YIELD			0
#define configUSE_MUTEXES			1
#define configQUEUE_REGISTRY_SIZE		8
#define configCHECK_FOR_STACK_OVERFLOW		2
#define configUSE_RECURSIVE_MUTEXES		1
#define configUSE_MALLOC_FAILED_HOOK		1
#define configUSE_APPLICATION_TASK_TAG		0
#define configUSE_COUNTING_SEMAPHORES		1
#define configGENERATE_RUN_TIME_STATS		0
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

/**************************************************************
 * Required for thread-safety of newlib sprintf, strtok, etc...
 * Newlib usage into FreeRTOS could induce some unexpected issue
 * For more information please read: 
 * http://www.nadler.com/embedded/newlibAndFreeRTOS.html
 * in order to mitigate it the following define must be set to 1
 **************************************************************/ 
#define configUSE_NEWLIB_REENTRANT 		1 

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 			0
#define configMAX_CO_ROUTINE_PRIORITIES 	( 2 )

/* Software timer definitions. SwitchC */
#define configUSE_TIMERS			1
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH		4
/*
 * configTIMER_TASK_STACK_DEPTH must be a value greater than 80 + the sizeof the register saved.
 * The size of the register is differrent from a core to another, e.g. on RiscV
 * it could be 32 base register + 32 register for FPU and some other for the
 * specific extensions.
 */
//#define configTIMER_TASK_STACK_DEPTH		( 114 )
#define configTIMER_TASK_STACK_DEPTH		( 256 )

/* Task priorities.  Allow these to be overridden. */
#ifndef uartPRIMARY_PRIORITY
	#define uartPRIMARY_PRIORITY		( configMAX_PRIORITIES - 3 )
#endif

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete			1
#define INCLUDE_vTaskCleanUpResources		1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay			1
#define INCLUDE_eTaskGetState			1
#define INCLUDE_xTimerPendFunctionCall		1


/* Overwrite some of the stack sizes allocated to various test and demo tasks.
Like all task stack sizes, the value is the number of words, not bytes. */
#define bktBLOCK_TIME_TASK_STACK_SIZE 			100
#define notifyNOTIFIED_TASK_STACK_SIZE 			120
#define priSUSPENDED_RX_TASK_STACK_SIZE 		90
#define tmrTIMER_TEST_TASK_STACK_SIZE 			100
#define ebRENDESVOUS_TEST_TASK_STACK_SIZE 		100
#define ebEVENT_GROUP_SET_BITS_TEST_TASK_STACK_SIZE 	115
#define genqMUTEX_TEST_TASK_STACK_SIZE 			90
#define genqGENERIC_QUEUE_TEST_TASK_STACK_SIZE 		100
#define recmuRECURSIVE_MUTEX_TEST_TASK_STACK_SIZE 	90

/* Just in case it was not defined above force to not use it */
#ifndef configUSE_SEGGER_SYSTEMVIEW
#define configUSE_SEGGER_SYSTEMVIEW	0
#endif

#if( configUSE_SEGGER_SYSTEMVIEW == 1 )
# include <SEGGER_SYSVIEW_FreeRTOS.h>
# if (INCLUDE_xTaskGetIdleTaskHandle != 1)
#  define INCLUDE_xTaskGetIdleTaskHandle  1
# endif
#endif

#endif /* FREERTOS_CONFIG_H */
