/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the ARM CM3 port.
 *----------------------------------------------------------*/

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "portmacro.h"

/*SiFive Includes */
#include "platform.h"

/* Standard Includes */
#include <stdlib.h>
#include <unistd.h>


/* Each task maintains its own interrupt status in the critical nesting
variable. */
UBaseType_t uxCriticalNesting = 0xaaaaaaaa;

#if USER_MODE_TASKS
	MSTATUS_INIT = (MSTATUS_MPIE);
#else
	MSTATUS_INIT = (MSTATUS_MPP | MSTATUS_MPIE);
#endif


/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
static void prvTaskExitError( void );

void vPortEnterCritical( void )
{
	portDISABLE_INTERRUPTS();
	uxCriticalNesting++;
}
/*-----------------------------------------------------------*/

void vPortExitCritical( void )
{
	configASSERT( uxCriticalNesting );
	uxCriticalNesting--;
	if( uxCriticalNesting == 0 )
	{
		portENABLE_INTERRUPTS();
	}
}
/*-----------------------------------------------------------*/


/*-----------------------------------------------------------*/

/* Clear current interrupt mask and set given mask */
void vPortClearInterruptMask(int mask)
{
	write_csr(mie,mask);
}
/*-----------------------------------------------------------*/

/* Set interrupt mask and return current interrupt enable register */
int xPortSetInterruptMask()
{
	uint32_t ret;
	ret = read_csr(mie);
	write_csr(mie,0);
	return ret;
}

/*-----------------------------------------------------------*/
/*
 * See header file for description.
 */
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
	/* Simulate the stack frame as it would be created by a context switch
	interrupt. */

	register int *tp asm("x3");
	pxTopOfStack--;
	*pxTopOfStack = (portSTACK_TYPE)pxCode;			/* Start address */

	//set the initial mstatus value
	pxTopOfStack--;
	*pxTopOfStack = MSTATUS_INIT;

	pxTopOfStack -= 22;
	*pxTopOfStack = (portSTACK_TYPE)pvParameters;	/* Register a0 */
	pxTopOfStack -= 6;
	*pxTopOfStack = (portSTACK_TYPE)tp; /* Register thread pointer */
	pxTopOfStack -= 3;
	*pxTopOfStack = (portSTACK_TYPE)prvTaskExitError; /* Register ra */

	return pxTopOfStack;
}
/*-----------------------------------------------------------*/


void prvTaskExitError( void )
{
	/* A function that implements a task must not exit or attempt to return to
	its caller as there is nothing to return to.  If a task wants to exit it
	should instead call vTaskDelete( NULL ).
	Artificially force an assert() to be triggered if configASSERT() is
	defined, then stop here so application writers can catch the error. */
	configASSERT( uxCriticalNesting == ~0UL );
	portDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/


/*Entry Point for Machine Timer Interrupt Handler*/
void vPortSysTickHandler(){

	clear_csr(mie, MIP_MTIP);

	volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
	volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
	uint64_t now = *mtime;
	uint64_t then = now + (configRTC_CLOCK_HZ / configTICK_RATE_HZ);
	*mtimecmp = then;

	/* Increment the RTOS tick. */
	if( xTaskIncrementTick() != pdFALSE )
	{
		vTaskSwitchContext();

	}
	set_csr(mie, MIP_MTIP);
}
/*-----------------------------------------------------------*/


void vPortSetupTimer()	{

    // Set the machine timer to go off in 3 seconds.
    // The
    volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
    uint64_t now = *mtime;
    uint64_t then = now + (configRTC_CLOCK_HZ / configTICK_RATE_HZ);
    *mtimecmp = then;

    // Enable the Machine-Timer bit in MIE
    set_csr(mie, MIP_MTIP);
}
/*-----------------------------------------------------------*/


void vPortSetup()	{
	vPortSetupTimer();
	uxCriticalNesting = 0;
	//set_csr(mstatus,MSTATUS_MPIE);
}
/*-----------------------------------------------------------*/













