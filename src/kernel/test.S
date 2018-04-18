.globl excp
.extern exception_handler

.set noreorder

.section .ktext

excp:
	addi $s2, $s0, 1
	sb $s2, 0x1F000408
	nop
	jal exception_handler
	nop
	b .
	nop
