#ifndef __REGISTERS_H__
#define __REGISTERS_H__

#define ZERO $0 // Constant zero

#define AT $1		// Assembler temp

#define V0 $2 	// Function return 0
#define V1 $3 	// Function return 1

#define A0 $4		// Function argument 0
#define A1 $5		// Function argument 1
#define A2 $6		// Function argument 2
#define A3 $7		// Function argument 3

#define T0 $8		// Temporary register 0
#define T1 $9		// Temporary register 1
#define T2 $10	// Temporary register 2
#define T3 $11	// Temporary register 3
#define T4 $12	// Temporary register 4
#define T5 $13	// Temporary register 5
#define T6 $14	// Temporary register 6
#define T7 $15	// Temporary register 7

#define S0 $16	// Saved register 0
#define S1 $17	// Saved register 1
#define S2 $18	// Saved register 2
#define S3 $19	// Saved register 3
#define S4 $20	// Saved register 4
#define S5 $21	// Saved register 5
#define S6 $22	// Saved register 6
#define S7 $23	// Saved register 7

#define T8 $24	// Temporary register 8
#define T9 $25	// Temporary register 9

#define K0 $26	// Kernel register 0
#define K1 $27	// Kernel register 1

#define GP $gp	// Global pointer
#define SP $sp	// Stack pointer
#define FP $fp	// Frame pointer

#define RA $ra	// Return address

// -----------------------------------
// Coprocessor 0 registers
// -----------------------------------

#define C0_INDEX 		$0 	// Select TLB entry for read / write
#define C0_RANDOM 	$2
#define C0_ENTRYLO0 $3
#define C0_ENTRYLO1 $4
#define C0_CONTEXT 	$5
#define C0_PAGEMASK	$6
#define C0_BADVADDR	$8	// Bad virtual address
#define CO_ENTRYHI	$10

#define C0_COUNT 		$9 	// Timer count
#define C0_COMPARE	$11 // Timer compare

#define C0_STATUS		$12 // Status register
#define C0_CAUSE		$13 // Cause register

#define C0_ECP			$14	// Exception Program Counter

#define C0_EBASE		$15,1	// Exception entry point base address

// -----------------------------------
// Adresses
// -----------------------------------

#define EBASE_ADDR 0x80100000 // Ebase adress

// -----------------------------------
// Bitmasks
// -----------------------------------

#define ENABLE_TIMINTR  0x8000
#define ENABLE_INTR     0x1

#endif
