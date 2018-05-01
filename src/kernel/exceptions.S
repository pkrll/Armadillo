.globl __exception
.extern exception_handler
.extern reset_led

.set noreorder
.set noat

.section .ktext
.org 0x184 # Offset for the general exception vector in RAM
__exception:
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
