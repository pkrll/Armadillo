#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl __exception
.extern ibus_handler
.extern dbus_handler
.extern addrs_handler
.extern addrl_handler
.extern bkpt_handler
.extern ri_handler
.extern ovf_handler
.extern unkown_exception
.extern context_switch
.extern interupt_handler
.extern unhandled_interrupt
.extern save_context
.extern load_context
.extern _random_number
.extern terminate_process

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

	beq 	$k1, 0, __interupt_handler #If interupt, jump to interupt_handler
	nop

__exception_handler:
	beq  $k1, 8, __syscall #syscall exception
	nop

	beq  $k1, 4, __addrl   #load from illegal address exception
	nop

	beq  $k1, 5, __addrs   #store to illegal address exception
	nop

	#bus error occur when our processor cannot attempt the memory access requested
	beq  $k1, 6, __ibus    #bus error on instruction fetch
	nop

	beq  $k1, 7, __dbus    #bus error on data reference
	nop

	beq  $k1, 9, __bkpt    #break instruction executed
	nop

	beq  $k1, 10, __ri     #reserved instruction
	nop

	beq  $k1, 12, __ovf    #arithmetic overflow
	nop

	jal  unkown_exception  #Exception which we do not cover
	nop
	b    __jump_back
	nop

__interupt_handler:
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
	addi SP,  12

	b    context_switch
	nop

#--------------------Exceptions-------------------#
__syscall:
	#move $k0, $a0
	#beq  $k0, 99, __terminated

	jal terminate_process
	nop
	b context_switch
	nop

#addrl exception, jump to addrl_handler and then jump back
__addrl:
	jal  addrl_handler
	nop
	b    __jump_back
	nop

#addrs exception, jump to addrs_handler and then jump back
__addrs:
	jal  addrs_handler
	nop
	b    __jump_back
	nop

#ibus exception, jump to ibus_handler and then jump back
__ibus:
	jal  ibus_handler
	nop
	b    __jump_back
	nop

#dbus exception, jump to dbus_handler and then jump back
__dbus:
	jal  dbus_handler
	nop
	b    __jump_back
	nop

#bkpt exception, jump to bkpt_handler and then jump back
__bkpt:
	jal  bkpt_handler
	nop
	b    __jump_back
	nop

#ri exception, jump to ri_handler and then jump back
__ri:
	jal  ri_handler
	nop
	b 	 __jump_back
	nop

#ovf exception, jump to ovf_handler and then jump back
__ovf:
  jal  ovf_handler
	nop
	b    __jump_back
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
