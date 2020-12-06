
	.syntax unified
	.arch armv7e-m
    .section .text
	.thumb_func
	.align 2
	.global main

main:
	.equ SYSCTL_RCGCGPIO, 	0x400FE608
	.equ GPIO_F_DEN,		0x4002551C
	.equ GPIO_F_DIR,		0x40025400
	.equ GPIO_F_DATA,		0x400253FC
	.equ GPIO_F_AFSEL,		0x40025420
	.equ GPIO_F_PUR,		0x40025510


    // Set Bit 5 of SYSCTL_RCGCGPIO
	// enabling systemclock for GPIO_F
    LDR R0, =SYSCTL_RCGCGPIO
	LDR R1, [R0]				
	ORR R1, R1, #(1<<5)
	STR R1, [R0]


	/* initiating RGB LEDs
	****************************************
	/ correesponding GPIO Pin for each LED /
	/ red:   PF1                           /
	/ blue:  PF2                           / 
	/ green: PF3                           /
	/**************************************/
 
    mov r0, #0xE			//bit mask for manipulating GPIO registers
 
    ldr r1, =GPIO_F_AFSEL	//RGB pins fuction as GPIO and are controlled by the GPIO registers
    ldr r2, [r1]
    mvn r0, r0
	and r2, r2, r0
	str r2, [r1]

	mov r0, #0xE

	ldr r1, =GPIO_F_DEN		//enabling RGB pins
	ldr r2, [r1]
	orr r2, r2, r0
	str r2, [r1]

	ldr r1, =GPIO_F_DIR		//setting RGB pins as output
	ldr r2, [r1]
	orr r2, r2, r0
	str r2, [r1]


	/* this part integrates the crazy RGB LEDs */
	mov r0, #0b1
	ldr r3, =#0xAFFFF		//long loop

	ldr r1, =GPIO_F_DATA	//red LED ON
	ldr r2, [r1]
do_it_again:
	orr r2, r2, r0, lsl #1
	str r2, [r1]
	
wait0:	
	sub r3, r3, #0b1
	cmp r3, #0x0
	bne wait0
	bl reset_loop

	and r2, r2, #~(1<<3)	//green LED OFF
	str r2, [r1]

wait:	
	sub r3, r3, #0b1
	cmp r3, #0x0
	bne wait
	bl reset_loop

	orr r2, r2, r0, lsl #2	//blue  LED ON
	str r2, [r1]

wait2:	
	sub r3, r3, #0b1
	cmp r3, #0x0
	bne wait2
	bl reset_loop

	and r2, r2, #~(1<<1)	//red LED OFF
	str r2, [r1]

wait3:
    sub r3, r3, #0b1
	cmp r3, #0x0
	bne wait3
	bl reset_loop

	orr r2, r2, #(1<<3)		//green LED ON
	str r2, [r1]

wait4:	
	sub r3, r3, #0b1
	cmp r3, #0x0
	bne wait4
	bl reset_loop

    and r2, r2, #~(1<<2)	//blue LED OFF
	str r2, [r1]
	
wait5:
    sub r3, r3, #0b1
	cmp r3, #0x0
	bne wait5
	bl reset_loop

	b do_it_again

reset_loop:
	ldr r3, =0xAFFFF
	bx lr
	