/**
 * @file
 * @brief Adresses
 */

#ifndef __ADRESSES_H_
#define __ADRESSES_H_

// -----------------------------------
// Adresses
// -----------------------------------

#define EBASE_ADDR 		0x80100000 // Ebase adress
#define UART16550BASE 0xb80003f8
#define DISPLAYREGIST 0xbf000400 // Boot mode: 0x1F000400 ?
#define ASDCIIDISPLAY	DISPLAYREGIST + 0x00000018
#define LEDDISPLAY 		DISPLAYREGIST + 0x00000008

#endif
