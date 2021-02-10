	.syntax unified
	.arch armv7e-m
    .section .text
	.thumb_func
	.align 2

    .global calc_sum_x2

/* ================================== */
/*  r0-r3 Caller save registers       */
/*  r0-r3 Arguments                   */
/*                                    */
/*  r4-r11 Calle save Registers       */
/*  r4-r11 Subroutine "variables"     */
/*                                    */
/*  r0-r3 Return Value                */
/*  r0 for 32-bit; r0-r1 for 64-bit;  */
/*  r0-r3 for 128-bit                 */
/* ================================== */

calc_sum_x2:
    push {r4,lr}

    mov r4, #0
    add r4, r4, r0
    add r4, r4, r1
    add r4, r4, r2
    add r4, r4, r3

    bl x2

    mov r0, r4

    pop {r4,lr}

    bx lr

x2:
    LSL r4, r4, #1
    bx lr
