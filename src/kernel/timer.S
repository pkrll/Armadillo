#include <mips/registers.h>
#include <mips/adresses.h>
#include <mips/bitmasks.h>

.globl init_timer

.set noreorder
.set noat

.text
# Initialize timer interrupts
init_timer:
	mfc0 	$t3, C0_STATUS 	#	Load contents of Status register
	ori		$t3, ENABLE_INTR
	ori		$t3, ENABLE_TIMINTR
	mtc0	$t3, C0_STATUS	# Store the contents in Status register
	li		$t2, 0x1
	mtc0	$t2, C0_COMPARE	# Set compare register to 0x1
	j			$ra				# jump to $ra
