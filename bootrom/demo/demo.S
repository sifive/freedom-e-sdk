#define UART_BASE	0x48000000
#define SPI_BASE	0x48001000
#define GPIO_BASE	0x48002000

#ifndef CFG_STRING
#error Must define CFG_STRING
#endif	
        
	.globl _start
_start:
	j uart_init
	nop
	nop
	.word cfgstr

uart_init:
        // a1 = UART_TX
        // a2 = hello_msg_end
        // for (a0 = hello_msg_start; a0 != a2; ++ a0){
        //   while (a3 = TX_READY == 0);
        //   a3 = *a0
        //   *a1 = a3
        // }

        la a0, hello_msg_start
        la a2, hello_msg_end
        li a1, UART_BASE
                
uart_loop:      
        lw a3, 4(a1) // Wait until non-zero (uart can send data).
        beqz a3, uart_loop

        lb a3, 0(a0) // read the next character in hello_msg
        sw a3, 0(a1) // Write the current character.
        addi a0, a0, 1 // increment the pointer.
        bne  a0, a2, uart_loop

gpio_init:   
	li a0, GPIO_BASE
        li t0, 0xFFFF0000
        sw t0, 4(a0)
        
gpio_loop:
        // For Red LEDs, increment manually.
	li t0, 0x1
	sw t0, (a0)
	li t0, 0x2
	sw t0, (a0)
	li t0, 0x4
	sw t0, (a0)
	li t0, 0x8
	sw t0, (a0)

        // For Blue and Green LEDs, sample the switches & buttons

        lw   t0, (a0)
        srli t0, t0, 16
	andi t0, t0, 0xFF
        slli t0, t0, 4
        sw   t0, (a0)

        j gpio_loop

	.section .rodata

hello_msg_start:
        .incbin "hello_msg.txt"
hello_msg_end:  
                
cfgstr:
	.incbin CFG_STRING
