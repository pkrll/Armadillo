.globl excp
.extern exception_handler

.set noreorder
.set noat

.section .ktext
.org 0x184
excp:
	jal exception_handler
	nop
	jr $ra # How do we return?
	nop
	b .
	nop
