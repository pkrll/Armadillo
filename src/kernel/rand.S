#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl __rand

.set noreorder
.set noat

.section .text

__rand:
	mfc0  $t3, C0_COUNT
	addi  $v0, $t3, 0
	jr    $ra
	nop
