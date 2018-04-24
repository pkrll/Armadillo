#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl __exception
.extern exception_handler
.extern context_switch

.set noreorder
#.set noat

.section .ktext
.org 0x184 # Offset for the general exception vector in RAM
__exception:

	mfc0	$k0, C0_CAUSE
	li		$k1, MASK_CAUSE
	and		$k1, $k1, $k0
	srl		$k1, 2	# exception code

	beq	$k1, 8, __syscall

	addiu $t1, $zero, 1
	beq $a0, $t1, __reset_led
	nop
	jal exception_handler
	nop
	b __jump_back
	nop

__reset_led:
	jal reset_led
	nop

__jump_back:
	mfc0	$k0, $14
	addi	$k0, $k0, 4
	mtc0	$k0, $14

	eret

__syscall:

	jal context_switch
	nop
