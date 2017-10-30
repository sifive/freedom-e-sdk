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

/* Kernel includes. */
#include "FreeRTOS.h" /* Must come first. */
#include "task.h"     /* RTOS task related API prototypes. */
#include "queue.h"    /* RTOS queue related API prototypes. */
#include "timers.h"   /* Software timer related API prototypes. */
#include "semphr.h"   /* Semaphore related API prototypes. */

/* TODO Add any manufacture supplied header files can be included
here. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "platform.h"
#include "encoding.h"
#include "plic/plic_driver.h"


/* Priorities at which the tasks are created.  The event semaphore task is
given the maximum priority of ( configMAX_PRIORITIES - 1 ) to ensure it runs as
soon as the semaphore is given. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2 )
#define mainQUEUE_SEND_TASK_PRIORITY        ( tskIDLE_PRIORITY + 1 )
#define mainEVENT_SEMAPHORE_TASK_PRIORITY   ( configMAX_PRIORITIES - 1 )

/* The rate at which data is sent to the queue, specified in milliseconds, and
converted to ticks using the pdMS_TO_TICKS() macro. */
#define mainQUEUE_SEND_PERIOD_MS            pdMS_TO_TICKS( 200 )

/* The period of the example software timer, specified in milliseconds, and
converted to ticks using the pdMS_TO_TICKS() macro. */
#define mainSOFTWARE_TIMER_PERIOD_MS        pdMS_TO_TICKS( 1000 )

/* The number of items the queue can hold.  This is 1 as the receive task
has a higher priority than the send task, so will remove items as they are added,
meaning the send task should always find the queue empty. */
#define mainQUEUE_LENGTH                    ( 1 )

/*-----------------------------------------------------------*/

/*
 * TODO: Implement this function for any hardware specific clock configuration
 * that was not already performed before main() was called.
 */
static void prvSetupHardware( void );

/*
 * The queue send and receive tasks as described in the comments at the top of
 * this file.
 */
static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );

/*
 * The callback function assigned to the example software timer as described at
 * the top of this file.
 */
static void vExampleTimerCallback( TimerHandle_t xTimer );

/*
 * The event semaphore task as described at the top of this file.
 */
static void prvEventSemaphoreTask( void *pvParameters );

/*-----------------------------------------------------------*/

/* The queue used by the queue send and queue receive tasks. */
static QueueHandle_t xQueue = NULL;

/* The semaphore (in this case binary) that is used by the FreeRTOS tick hook
 * function and the event semaphore task.
 */
static SemaphoreHandle_t xEventSemaphore = NULL;

/* The counters used by the various examples.  The usage is described in the
 * comments at the top of this file.
 */
static volatile uint32_t ulCountOfTimerCallbackExecutions = 0;
static volatile uint32_t ulCountOfItemsReceivedOnQueue = 0;
static volatile uint32_t ulCountOfReceivedSemaphores = 0;

/*-----------------------------------------------------------*/

// Structures for registering different interrupt handlers
// for different parts of the application.
typedef void (*function_ptr_t) (void);
void no_interrupt_handler (void) {};
function_ptr_t g_ext_interrupt_handlers[PLIC_NUM_INTERRUPTS];
function_ptr_t localISR[32]; 

// Instance data for the PLIC.
plic_instance_t g_plic;

int main(void)
{
	TimerHandle_t xExampleSoftwareTimer = NULL;


    /* Configure the system ready to run the demo.  The clock configuration
    can be done here if it was not done before main() was called. */
    prvSetupHardware();


    /* Create the queue used by the queue send and queue receive tasks. */
    xQueue = xQueueCreate(     /* The number of items the queue can hold. */
                            mainQUEUE_LENGTH,
                            /* The size of each item the queue holds. */
                            sizeof( uint32_t ) );

    if(xQueue == NULL)	{
    	for(;;);
    }

    /* Create the queue receive task as described in the comments at the top
    of this file. */
    xTaskCreate(     /* The function that implements the task. */
                    prvQueueReceiveTask,
                    /* Text name for the task, just to help debugging. */
                    ( const char * ) "Rx",
                    /* The size (in words) of the stack that should be created
                    for the task. */
					600, /* printf requires a much deeper stack*/
                    /* A parameter that can be passed into the task.  Not used
                    in this simple demo. */
                    NULL,
                    /* The priority to assign to the task.  tskIDLE_PRIORITY
                    (which is 0) is the lowest priority.  configMAX_PRIORITIES - 1
                    is the highest priority. */
                    mainQUEUE_RECEIVE_TASK_PRIORITY,
                    /* Used to obtain a handle to the created task.  Not used in
                    this simple demo, so set to NULL. */
                    NULL );

    /* Create the queue send task in exactly the same way.  Again, this is
    described in the comments at the top of the file. */
    xTaskCreate(     prvQueueSendTask,
                    ( const char * ) "TX",
					configMINIMAL_STACK_SIZE,
                    NULL,
                    mainQUEUE_SEND_TASK_PRIORITY,
                    NULL );

    /* Create the semaphore used by the FreeRTOS tick hook function and the
    event semaphore task.  NOTE: A semaphore is used for example purposes,
    using a direct to task notification will be faster! */
    xEventSemaphore = xSemaphoreCreateBinary();
    if(xEventSemaphore == NULL)	{
    	for(;;);
    }

    /* Create the task that is synchronised with an interrupt using the
    xEventSemaphore semaphore. */
    xTaskCreate(     prvEventSemaphoreTask,
                    ( const char * ) "Sem",
					500,
                    NULL,
                    mainEVENT_SEMAPHORE_TASK_PRIORITY,
                    NULL );


    /* Create the software timer as described in the comments at the top of
    this file. */
    xExampleSoftwareTimer = xTimerCreate(     /* A text name, purely to help
                                            debugging. */
                                            ( const char * ) "LEDTimer",
                                            /* The timer period, in this case
                                            1000ms (1s). */
                                            mainSOFTWARE_TIMER_PERIOD_MS,
                                            /* This is a periodic timer, so
                                            xAutoReload is set to pdTRUE. */
                                            pdTRUE,
                                            /* The ID is not used, so can be set
                                            to anything. */
                                            ( void * ) 0,
                                            /* The callback function that switches
                                            the LED off. */
                                            vExampleTimerCallback
                                        );

    /* Start the created timer.  A block time of zero is used as the timer
    command queue cannot possibly be full here (this is the first timer to
    be created, and it is not yet running). */
    xTimerStart( xExampleSoftwareTimer, 0 );



    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details.  */
    for( ;; );
}
/*-----------------------------------------------------------*/

static void vExampleTimerCallback( TimerHandle_t xTimer )
{
    /* The timer has expired.  Count the number of times this happens.  The
    timer that calls this function is an auto re-load timer, so it will
    execute periodically. */
    ulCountOfTimerCallbackExecutions++;

    GPIO_REG(GPIO_OUTPUT_VAL)  ^=   (0x1 << BLUE_LED_OFFSET) ;
    write(1,"RTOS Timer Callback\n", 20);

}
/*-----------------------------------------------------------*/



static void prvQueueSendTask( void *pvParameters )
{
TickType_t xNextWakeTime;
const uint32_t ulValueToSend = 100UL;

    /* Initialise xNextWakeTime - this only needs to be done once. */
    xNextWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        /* Place this task in the blocked state until it is time to run again.
        The block time is specified in ticks, the constant used converts ticks
        to ms.  The task will not consume any CPU time while it is in the
        Blocked state. */
         vTaskDelayUntil( &xNextWakeTime, mainQUEUE_SEND_PERIOD_MS );

        write(1, "Sending to queue\n", 17);
        /* Send to the queue - causing the queue receive task to unblock and
        increment its counter.  0 is used as the block time so the sending
        operation will not block - it shouldn't need to block as the queue
        should always be empty at this point in the code. */
        xQueueSend( xQueue, &ulValueToSend, 0 );
    }
}
/*-----------------------------------------------------------*/

static void prvQueueReceiveTask( void *pvParameters )
{
	uint32_t ulReceivedValue;
	char stringValue[10];

    for( ;; )
    {

        /* Wait until something arrives in the queue - this task will block
        indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
        FreeRTOSConfig.h. */
        xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );
        itoa(ulReceivedValue,stringValue, 10);
        write(1,"Recieved: ", 10);
        write(1,stringValue, 3);
        write(1,"\n",1);


        /*  To get here something must have been received from the queue, but
        is it the expected value?  If it is, increment the counter. */
        if( ulReceivedValue == 100UL )
        {
            /* Count the number of items that have been received correctly. */
            ulCountOfItemsReceivedOnQueue++;
        }
    }
}
/*-----------------------------------------------------------*/

static void prvEventSemaphoreTask( void *pvParameters )
{
    for( ;; )
    {
        /* Block until the semaphore is 'given'.  NOTE:
        A semaphore is used for example purposes.  In a real application it might
        be preferable to use a direct to task notification, which will be faster
        and use less RAM. */
        xSemaphoreTake( xEventSemaphore, portMAX_DELAY );

        /* Count the number of times the semaphore is received. */
        ulCountOfReceivedSemaphores++;

        write(1, "Semaphore taken\n", 16);
    }
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
BaseType_t xHigherPriorityTaskWoken = pdFALSE;
static uint32_t ulCount = 0;

    /* The RTOS tick hook function is enabled by setting configUSE_TICK_HOOK to
    1 in FreeRTOSConfig.h.

    "Give" the semaphore on every 500th tick interrupt. */
    ulCount++;

    if( ulCount >= 500UL )
    {
        //re-enable the b1 interrupt
        set_csr(mie, MIP_MLIP(LOCAL_INT_BTN_1));

    	/* This function is called from an interrupt context (the RTOS tick
        interrupt),    so only ISR safe API functions can be used (those that end
        in "FromISR()".


        xHigherPriorityTaskWoken was initialised to pdFALSE, and will be set to
        pdTRUE by xSemaphoreGiveFromISR() if giving the semaphore unblocked a
        task that has equal or higher priority than the interrupted task.
        NOTE: A semaphore is used for example purposes.  In a real application it
        might be preferable to use a direct to task notification,
        which will be faster and use less RAM. */
        xSemaphoreGiveFromISR( xEventSemaphore, &xHigherPriorityTaskWoken );
        ulCount = 0UL;

    	GPIO_REG(GPIO_OUTPUT_VAL)  ^=   (0x1 << GREEN_LED_OFFSET) ;
    	write(1, "Giving Semaphore\n", 17);
    }

    /* If xHigherPriorityTaskWoken is pdTRUE then a context switch should
    normally be performed before leaving the interrupt (because during the
    execution of the interrupt a task of equal or higher priority than the
    running task was unblocked).  The syntax required to context switch from
    an interrupt is port dependent, so check the documentation of the port you
    are using.

    In this case, the function is running in the context of the tick interrupt,
    which will automatically check for the higher priority task to run anyway,
    so no further action is required. */
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
    /* The malloc failed hook is enabled by setting
    configUSE_MALLOC_FAILED_HOOK to 1 in FreeRTOSConfig.h.

    Called if a call to pvPortMalloc() fails because there is insufficient
    free memory available in the FreeRTOS heap.  pvPortMalloc() is called
    internally by FreeRTOS API functions that create tasks, queues, software
    timers, and semaphores.  The size of the FreeRTOS heap is set by the
    configTOTAL_HEAP_SIZE configuration constant in FreeRTOSConfig.h. */
	write(1,"malloc failed\n", 14);
    for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t xTask, signed char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) xTask;

    /* Run time stack overflow checking is performed if
    configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
    function is called if a stack overflow is detected.  pxCurrentTCB can be
    inspected in the debugger if the task name passed into this function is
    corrupt. */
    write(1, "Stack Overflow\n", 15);
    for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
volatile size_t xFreeStackSpace;

    /* The idle task hook is enabled by setting configUSE_IDLE_HOOK to 1 in
    FreeRTOSConfig.h.

    This function is called on each cycle of the idle task.  In this case it
    does nothing useful, other than report the amount of FreeRTOS heap that
    remains unallocated. */
    xFreeStackSpace = xPortGetFreeHeapSize();

    if( xFreeStackSpace > 100 )
    {
        /* By now, the kernel has allocated everything it is going to, so
        if there is a lot of heap remaining unallocated then
        the value of configTOTAL_HEAP_SIZE in FreeRTOSConfig.h can be
        reduced accordingly. */
    }
}

/*ISR triggered by Button 0 */
void b0_ISR( )    {
    const uint32_t ulValueToSend = 555UL;
    
    GPIO_REG(GPIO_OUTPUT_VAL)  ^=   (0x1 << RED_LED_OFFSET) ;
    write(1,"---------->\n",13);
    xQueueSendFromISR( xQueue, &ulValueToSend, 0 );
    //clear irq - interrupt pending register is write 1 to clear
    GPIO_REG(GPIO_FALL_IP) |= (1<<BUTTON_0_OFFSET);
}
/*-----------------------------------------------------------*/


/*Local Interrupt triggered by Button 1  */
void b1_ISR( )    {
    const uint32_t ulValueToSend = 888UL;
    
    write(1,"~~~~~~~~~~~>\n",13);
    xQueueSendFromISR( xQueue, &ulValueToSend, 0 );

    //clear irq - interrupt pending register is write 1 to clear
    clear_csr(mie, MIP_MLIP(LOCAL_INT_BTN_0));

    //to debounce, and prevent multiple interrupts occuring
    //disable the interrupt here, and re-enable later in the
    //vApplicationTickHook callback
    clear_csr(mie, MIP_MLIP(LOCAL_INT_BTN_1));
}
/*-----------------------------------------------------------*/


/*Entry Point for Interrupt Handler*/
void handle_interrupt(unsigned long mcause){

  /* check if global*/
  if(!((mcause & MCAUSE_CAUSE) == IRQ_M_EXT))   {
    localISR[mcause & MCAUSE_CAUSE] ();
  } else {
      //global interrupt
    plic_source int_num  = PLIC_claim_interrupt(&g_plic);
    g_ext_interrupt_handlers[int_num]();
    PLIC_complete_interrupt(&g_plic, int_num);
  }

}

/*-----------------------------------------------------------*/


//enables interrupt and assigns handler
void enable_interrupt(uint32_t int_num, uint32_t int_priority, function_ptr_t handler) {
    g_ext_interrupt_handlers[int_num] = handler;
    PLIC_set_priority(&g_plic, int_num, int_priority);
    PLIC_enable_interrupt (&g_plic, int_num);
}
/*-----------------------------------------------------------*/

/*
 *enables the plic and programs handlers
**/
void interrupts_init(  ) {

    // Disable the machine & timer interrupts until setup is done.
    clear_csr(mie, MIP_MEIP);
    clear_csr(mie, MIP_MTIP);


  //setup PLIC
  PLIC_init(&g_plic,
	    PLIC_CTRL_ADDR,
	    PLIC_NUM_INTERRUPTS,
	    PLIC_NUM_PRIORITIES);

  //assign interrupts to default handler
  for (int ii = 0; ii < PLIC_NUM_INTERRUPTS; ii ++){
    g_ext_interrupt_handlers[ii] = no_interrupt_handler;
  }

  for (int isr = 0; isr < 32; isr++){
    localISR[isr] = no_interrupt_handler;
  }
    // Enable the Machine-External bit in MIE
    set_csr(mie, MIP_MEIP);
}
/*-----------------------------------------------------------*/

void led_init()  {
    GPIO_REG(GPIO_INPUT_EN)    &= ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
    GPIO_REG(GPIO_OUTPUT_EN)   |=  ((0x1<< RED_LED_OFFSET)| (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
    GPIO_REG(GPIO_OUTPUT_VAL)  &= ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;

    //turn down the light!
    PWM0_REG(PWM_CMP1)  = 0xFFFF;
    PWM0_REG(PWM_CMP2)  = 0xFFFF;
    PWM0_REG(PWM_CMP3)  = 0xFFFF;
}
/*-----------------------------------------------------------*/

/*
**configures Button0 as a global gpio irq
*/
void b0_irq_init()  {

    //dissable hw io function
    GPIO_REG(GPIO_IOF_EN )    &=  ~(1 << BUTTON_0_OFFSET);

    //set to input
    GPIO_REG(GPIO_INPUT_EN)   |= (1<<BUTTON_0_OFFSET);
    GPIO_REG(GPIO_PULLUP_EN)  |= (1<<BUTTON_0_OFFSET);

    //set to interrupt on falling edge
    GPIO_REG(GPIO_FALL_IE)    |= (1<<BUTTON_0_OFFSET);

    enable_interrupt(INT_DEVICE_BUTTON_0, 2, &b0_ISR);

}
/*-----------------------------------------------------------*/

/*
**configures Button1 as a local interrupt
*/
void b1_irq_init()  {

    //install the handler
    localISR[IRQ_M_LOCAL + LOCAL_INT_BTN_1] = b1_ISR;

    //enable the interrupt
    set_csr(mie, MIP_MLIP(LOCAL_INT_BTN_1));

}
/*-----------------------------------------------------------*/

//always runs in Machine Mode
static void prvSetupHardware( void )
{
	//enable User Mode to RWX entire address map
	set_csr(pmpcfg0, 0xF);
	set_csr(pmpaddr0, 0xFFFFFFFF);

    interrupts_init();
    led_init();
    b0_irq_init();
    b1_irq_init();
}
/*-----------------------------------------------------------*/
