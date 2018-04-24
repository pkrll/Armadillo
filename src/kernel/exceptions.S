.globl __exception
.extern exception_handler
.extern context_switch

.set noreorder
.set noat

.section .ktext
.org 0x184 # Offset for the general exception vector in RAM
__exception:
	jal context_switch
	nop
	#jal exception_handler
	nop
	b .
	nop
