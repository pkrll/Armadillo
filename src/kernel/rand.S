#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl _random_number

.set noreorder
.set noat

.section .text

_random_number:
	mfc0  $t3, C0_COUNT
	addi  $v0, $t3, 0
	jr    $ra
	nop
