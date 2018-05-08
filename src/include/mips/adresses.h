/**
 * @file
 * @brief Adresses
 */

#ifndef __ADRESSES_H_
#define __ADRESSES_H_

// -----------------------------------
// Adresses
// -----------------------------------
/*
 * Initial virtual address space is partitioned into four segments:
 *
 *   kuseg   0x00000000 - 0x7fffffff  User virtual memory, TLB mapped
 *   kseg0   0x80000000 - 0x9fffffff  Physical memory, cached, unmapped
 *   kseg1   0xa0000000 - 0xbfffffff  Physical memory, uncached, unmapped
 *   kseg2   0xc0000000 - 0xffffffff  Kernel virtual memory, TLB mapped
 */

#define MIPS_KSEG0_START 0x80000000
#define MIPS_KSEG1_START 0xa0000000
#define MIPS_KSEG2_START 0xc0000000

#define EBASE_ADDR 		0x80100000 // Ebase adress
#define UART16550BASE 0xb80003f8
#define DISPLAYREGIST 0xbf000400 // Boot mode: 0x1F000400 ?
#define ASDCIIDISPLAY	DISPLAYREGIST + 0x00000018
#define LEDDISPLAY 		DISPLAYREGIST + 0x00000008


#define KBD_DATA_PORT 0x60
#define KBD_STATUS_PORT 0x64
#define KBD_COMMAND_PORT 0x64

#endif
