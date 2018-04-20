.globl init_timer

.set noreorder
.set noat

.text
# Initialize timer interrupts
init_timer:
	mfc0 	$t3, $12 	#	Load contents of Status register
	ori		$t4, 0x8001
	mtc0	$t4, $12	# Store the contents in Status register
	li		$t2, 0x1
	mtc0	$t2, $11	# Set compare register to 0x1
	j			$ra				# jump to $ra
