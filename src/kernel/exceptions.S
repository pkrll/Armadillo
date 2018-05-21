#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl __exception
.globl __terminate
.globl __pause

.extern context_switch
.extern exception_handler
.extern interrupt_handler
.extern unhandled_interrupt
.extern save_context
.extern load_context
.extern terminate_process
.extern pause_process

.set noreorder
#.set noat

.section .ktext
.org 0x184 # Offset for the general exception vector in RAM
__exception:

	mfc0  $k0, C0_STATUS
	li    $k1, 1
	not   $k1, $k1
	and   $k0, $k0, $k1
	mtc0  $k0, C0_STATUS #disable interrupts

	mfc0	$k0, C0_CAUSE
	li		$k1, MASK_CAUSE
	and		$k1, $k1, $k0
	srl		$k1, 2	# exception code

	beq 	$k1, 0, __interrupt_handler #If interupt, jump to interrupt_handler
	nop

__exception_handler:
	beq  $k1, 8, __syscall #syscall exception
	nop

	addi SP, -4
	sw 	 A0, 0(SP)
	add  A0, ZERO, K1

	jal  exception_handler
	nop

	lw 	 A0, 0(SP)
	addi SP, 4

	nop
	b    __jump_back
	nop

__interrupt_handler:
	mfc0 $k0, C0_CAUSE     #Get cause register
	beqz $k0, __jump_back  #All interrupts has been handled
	nop

	and  $k1, $k0, 0x8000  #Check if $k0 have the timer interrupt bit on, in other words is there a timer interrupt?
	bne  $k1, 0, __timer_interrupt #If there is a timer interrupt, jump to __timer_interrupt
	nop

	b  __unhandled_interrupt
	nop

__timer_interrupt:
	addi SP,  -20
	sw   RA,  0(SP)
	sw   $t2, 4(SP)
	sw   $t3, 8(SP)
	sw   $v0, 12(SP)
	sw   $v1, 16(SP)#Store registers used in reset_timer

	jal  reset_timer
	nop

	lw   $v1, 16(SP)
	lw   $v0, 12(SP)
	lw   $t3, 8(SP)
	lw 	 $t2, 4(SP)
	lw   RA,  0(SP)
	addi SP,  20

	b    context_switch
	nop

#--------------------Exceptions-------------------#
__syscall:
	beq A0, 0, __context_switch
	nop
	beq A0, 1, __terminate
	nop
	beq A0, 2, __pause
	nop

__terminate:
	jal terminate_process
	nop

__pause:
	jal pause_process
	nop

__context_switch:
	b context_switch
	nop

#----------------------Interrupts--------------------#

__unhandled_interrupt:
	jal unhandled_interrupt
	nop
	b   __jump_back
	nop

__jump_back:
	mfc0	$k0, $14
	addi	$k0, $k0, 4
	mtc0	$k0, $14

	mfc0 	$t3, C0_STATUS
	ori		$t3, ENABLE_INTR
	mtc0	$t3, C0_STATUS	# Enable interrupts

	eret
