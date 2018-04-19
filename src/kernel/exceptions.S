.globl excp
.extern exception_handler

.set noreorder
#.set noat

.section .ktext
.org 0x184
excp:

	mfc0 		$k0, $13 					#Get the cause value
	andi 		$k1, $k0, 124			#Set all bits to 0 except 2-6
	srl 		$k1, $k1, 2				#Shift 2 steps to the right to get the value

	beqz 		$k1, interrupt		#Checks if the cause is an interrupt
	nop
	nop

exception:

	beq 		$k1, 12, overflow #Overflow exception
	nop
	nop
	beq			$k1, 13, trap			#Trap exception
	nop
	nop

overflow:
	jal 		exception_handler
	j 			resume_from_exception

trap:

interrupt:


resume_from_exception:

	mfc0 		$k0, $14 				#Move the exception address to the next instruction
	addi		$k0, $k0, 4
	mtc0 		$k0, $14
	eret
