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
	srl		$k1, 2	#exception code?

	beq		$k1, 8, __syscall

__default:
	#jal exception_handler
	nop
	b .
	nop

__syscall:

	jal context_switch
	nop
