#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl init_timer
.globl reset_timer
.extern interupt_handler

.set noreorder
.set noat


.text
# Initialize timer interrupts
init_timer:
	#mfc0  $t3, C0_COUNT
	mfc0 	$t3, C0_STATUS 	#	Load contents of Status register
	ori		$t3, ENABLE_INTR
	ori		$t3, ENABLE_TIMINTR
	mtc0	$t3, C0_STATUS	# Store the contents in Status register
	li		$t2, 100000000
	mtc0	$t2, C0_COMPARE	# Set compare register to 0x1
	j			$ra				# jump to $ra

reset_timer:
	addi 	SP, -4
	sw  	RA, 0(SP)
	mfc0  $t3, C0_COUNT

	li   	$t2, 0x0
	mtc0  $t2, C0_COUNT
	li		$t2, 100000000
	mtc0	$t2, C0_COMPARE	# Set compare register to 0x1

	nop
	jal 	interupt_handler
	nop
	lw    RA, 0(SP)
	addi 	SP, 4
	j 		$ra
