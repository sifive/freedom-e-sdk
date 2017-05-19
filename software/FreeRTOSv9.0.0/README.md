Demos
-----
Each supported platform has a demo derived from official FreeRTOS hardware independent [example](http://www.freertos.org/Hardware-independent-RTOS-example.html). This demo creates a number of tasks at different priority levels along with a timer and Idle and Tick hook functions. Queues and Semaphores are used to communicate between tasks.

SiFive specific functionality was also added to the demo and differs slightly by platform. UART communication is used to help understand the status of the application, along with led control, and an button interrupt to send a message to a task via the queue.

**Building and Running**
 There is a demo for each supported platform in the Demo directory. The demo applications are setup to use the Freedom-E-SDK toolchain and bsp directory by default. Each demo has a make file in it's directory which can be used to compile the demo and program the platform by running the following commands :
 
 - make - builds the application
 - make upload - programs application into the platform

To target a different environment, edit the *Makefile.inc* file.

We have also included Freedom Studio examples. After opening Freedom Studio and selecting a workspace, click *File  -- Import -- Existing Project -- Select Root Directory* and then select the *Freedom-E-SDK/FreedomStudio/FreeRTOS* folder. Do NOT copy the projects into your worksapce as the paths are dependent on the project location.
 
**RISC-V Port Files**

The FreeRTOS source files are located in the Source folder. In keeping with the FreeRTOS naming scheme, the RISC-V specific files are located in the _Source/portable/GCC/RISCV_ directory. Normal FreeRTOS applications will not need to directly edit these files though it will be required to include this directory in your application.

As the port is still immature, however, there may be bugs in these files. If you run across something which may be a bug with these files, please raise an issue in this repo.

Credit for original port goes to:
https://github.com/illustris/FreeRTOS-RISCV